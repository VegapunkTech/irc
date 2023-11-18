/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_client_infos.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssefboughanmi <youssefboughanmi@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:31:56 by youssefboug       #+#    #+#             */
/*   Updated: 2023/11/07 15:24:38 by youssefboug      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"utils.hpp"
#include"../include/server.hpp"

bool Server::Nick_exist(std::string new_nick, int fd)
{
    std::map<int, Client>::iterator it;

    for (it = this->client_map.begin(); it != this->client_map.end(); ++it)
    {
        if(fd != it->first && it->second.getNick() == new_nick)
            return(1);
    }
    return(0);
}


bool Server::User_exist(std::string new_user, int fd)
{
    std::map<int, Client>::iterator it;

    for (it = this->client_map.begin(); it != this->client_map.end(); ++it)
    {
        if(fd != it->first && it->second.getUser() == new_user)
            return(1);
    }
    return(0);
}


bool isSubstring(const std::string& str, const std::string& substring) 
{
    return str.find(substring) != std::string::npos;
}

bool wrong_pass(std::string bufferstr, std::string pass_srv)
{
    std::string pass_cl;
    size_t posPass = bufferstr.find("PASS ");
    if (posPass != std::string::npos) 
    {
        size_t posNewline = bufferstr.find_first_of("\r\n", posPass);
        if (posNewline != std::string::npos)
            pass_cl = bufferstr.substr(posPass + 5, posNewline - (posPass + 5));
    }
    if(pass_cl != pass_srv)
        return(1);
    return(0);
}

void Server::get_client_infos(std::string bufferstr, int fd)
{ 
    this->client_map[fd].setIdSocket(fd);

    size_t posNick = bufferstr.find("NICK ");
    if (posNick != std::string::npos) {
        size_t posNewline = bufferstr.find_first_of("\r\n", posNick);
        if (posNewline != std::string::npos) {
            std::string nick = bufferstr.substr(posNick + 5, posNewline - (posNick + 5));
            this->client_map[fd].setNick(nick);
        }
    }

    size_t posUser = bufferstr.find("USER ");
    if (posUser != std::string::npos) {
        size_t posNewline = bufferstr.find_first_of("\r\n", posUser);
        if (posNewline != std::string::npos) 
        {
            std::string user = bufferstr.substr(posUser + 5, posNewline - (posUser + 5));
            size_t test = user.find_first_of(" ", 0);
            if (test != std::string::npos) 
            {
                std::string user1 = user.substr(0, test);
                this->client_map[fd].setUser(user1);
            }
            else
            {
                this->client_map[fd].setUser(user);
            }
        }
    }
}


void Server::delete_pfd(int fd)
{
    for (pfd_iterator it = this->_pfds.begin(); it != this->_pfds.end(); it++)
    {
        if (it->fd == fd) 
        {
            this->_pfds.erase(it);
            break;  // Important to break out of the loop after erasing
        }
    }

}

std::string get_all_infos(char *buffer, int fd)
{
    std::string big_buffer = std::string(buffer);
    char buffer_tmp[2048];

    while(!isSubstring(big_buffer , "NICK ") 
        || !isSubstring(big_buffer , "USER "))
    {
        recv(fd, buffer_tmp, sizeof(buffer_tmp), 0);
        big_buffer += buffer_tmp;
        memset(&(buffer_tmp), 0, 2048);
    }
    return(big_buffer);
}

void Server::new_connection()
{

    int         fd;
    sockaddr_in addr = {};
    socklen_t   size = sizeof(addr);

    fd = accept(this->_nSocket, (sockaddr *) &addr, &size);
    if (fd < 0)
        throw std::runtime_error("Error while accepting a new client!");

    // including the client fd in the poll
    pollfd  pfd = {fd, POLLIN, 0};
    this->_pfds.push_back(pfd);
    //recv first msg from the client
    char buffer[2048];
    if(recv(fd, buffer, sizeof(buffer), 0) <= 0)
    {
        close(fd);
        return;
    };

    //check pass
    while(!isSubstring(std::string(buffer), "PASS ") && !isSubstring(std::string(buffer), "NICK ")) 
    {
        memset(&(buffer), 0, 2048);
        if(recv(fd, buffer, sizeof(buffer), 0) <= 0)
        {
            close(fd);
            return;
        };
    }

    if(!isSubstring(std::string(buffer), "PASS ")
        || wrong_pass(std::string(buffer), this->getPass()))
    {
        std::string msg RPL_WRONG_PASS();
        send(fd, msg.c_str(), strlen(msg.c_str()) , 0);
        close(fd);
        this->delete_pfd(fd);
        return;
    }
    std::string big_buffer = get_all_infos(buffer , fd);
    //create instance client and get User and Nick
    this->get_client_infos(big_buffer, fd);

    //get unique Nick
    while(this->Nick_exist(this->client_map[fd].getNick() , fd))
        this->client_map[fd].setNick(this->client_map[fd].getNick() + '_');

    //get unique User
    while(this->User_exist(this->client_map[fd].getUser(), fd))
        this->client_map[fd].setUser(this->client_map[fd].getUser() + '_');

    //send welcome msg 
    std::string msg RPL_WELCOME(this->client_map[fd].getNick());
    send(fd, msg.c_str(), strlen(msg.c_str()) , 0);

}






