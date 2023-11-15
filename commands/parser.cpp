/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssefboughanmi <youssefboughanmi@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:31:56 by youssefboug       #+#    #+#             */
/*   Updated: 2023/11/07 15:24:38 by youssefboug      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/server.hpp"
#include"../utils/utils.hpp"


void Server::parser(char *buffer, int fd)
{
    std::string bufferstr(buffer);

    //JOIN
    if(strncmp(buffer, "JOIN ", 5) == 0)
    {
        size_t posNewline = bufferstr.find('\n', 5);
        if (posNewline != std::string::npos) 
        {
            std::string channelname = bufferstr.substr(6, posNewline - 7);
            this->join(channelname, fd);
        }
    }

    //PRIVMSG
    if(strncmp(buffer, "PRIVMSG ", 8) == 0) 
    {
        size_t posspace = bufferstr.find(' ', 9);
        if (posspace != std::string::npos) 
        {
            std::string channelname = bufferstr.substr(9, posspace - 9);
            this->privmsg(channelname, fd, buffer);
            
        }
    }

    //MODE
    if(strncmp(buffer, "MODE ", 5) == 0) 
    {
        size_t posspace = bufferstr.find(' ', 6);
        if (posspace != std::string::npos) 
        {

            std::string channelname = bufferstr.substr(6, posspace - 6);
            std::string command;
            std::string arg;
            std::string signe;

            size_t test = bufferstr.find('\r', posspace+1);
            if (posspace != std::string::npos) 
            {

                std::string cmd = bufferstr.substr(posspace+1, test - (posspace+1));
                size_t test1 = cmd.find(' ', 0);

                if (test1 != std::string::npos) {
                    command = cmd.substr(0, test1);
                    arg = cmd.substr(test1+1, bufferstr.length());
                }
                else 
                    command = cmd.substr(0, test1);
                for (std::size_t i = 0; i < command.length(); i++)
                {
                    if (command[i] == '+' || command[i] == '-')
                        signe = command[i];
                    else
                    {
                        std::cout << "ici se trouvve bug " << std::endl;
                        if (command[i] == 'o' || command[i] == 'l' ||command[i] == 'k')
                            this->mode(channelname, signe, command[i] , arg , fd);
                        else
                            this->mode(channelname, signe, command[i] , std::string(""), fd);
                    }
                }
            }
        }
    }

    //QUIT
    if(strncmp(buffer, "QUIT " , 5) == 0)
        this->client_disconnect(fd);


    //PING
    if(strncmp(buffer, "PING " , 5) == 0)
    {
        std::string msg = RPL_PONG();
        send(fd , msg.c_str(),  msg.length(), 0);
    }

    //kick

    if(strncmp(buffer, "KICK ", 5) == 0) {
    
        std::string bufferstr(buffer);

        size_t posspace = bufferstr.find(' ', 6);
        if (posspace != std::string::npos) 
        {
            std::string channelname = bufferstr.substr(6, posspace - 6);
            size_t posspace2 = bufferstr.find(' ', posspace+1);
            if (posspace2 != std::string::npos) 
            {
                std::string pseudo = bufferstr.substr(posspace+1, posspace2 - posspace-1);
                this->kick(channelname, pseudo,bufferstr , fd);
            }   
        }
    }
}
