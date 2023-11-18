/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssefboughanmi <youssefboughanmi@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:31:56 by youssefboug       #+#    #+#             */
/*   Updated: 2023/11/07 15:24:38 by youssefboug      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/server.hpp"
#include"../utils/utils.hpp"


Server::Server(int port, std::string pass) : _port(port), _pass(pass)
{
    return;
}

Server::~Server( void )
{
    return;
}

Server::Server( Server const & src ) 
{
    *this = src;
    return;
}

Server & Server::operator=(Server const & rhs)
{
    this->_nSocket = rhs.getNSocket();
    this->_port = rhs.getPort();
    return (*this);
}


int Server::getNSocket(void) const
{
    return(this->_nSocket);    
}

int Server::getPort(void) const
{
    return(this->_port);
}
std::string Server::getPass(void) const
{
    return(this->_pass);
}


 
void Server::manage_cl_msg(int fd)
{     
    char buffer[2048];
    if(recv(fd, buffer, sizeof(buffer), 0) <=0)
    {
        std::cout << "Error : "<<buffer <<std::endl;

        this->client_disconnect(fd);
        return;
    }
    this->parser(buffer, fd);
}



volatile sig_atomic_t interrupted = 0;

void signalHandler(int signum) {
    if (signum == SIGINT) 
    {

        interrupted = 1;
    }
}


void Server::run(void)
{
    this->start();

    pollfd srv = {this->_nSocket, POLLIN, 0};
    this->_pfds.push_back(srv);

    //Keep waiting for new requests and proceed as per the request
    while(1)
    {
        poll(this->_pfds.begin().base(), this->_pfds.size(), -1);

        //boucler sur tout les pollfd 
        for (pfd_iterator it = this->_pfds.begin(); it != this->_pfds.end(); it++)
        {
            if (it->revents == 0)
                continue;

            if ((it->revents & POLLOUT) || (it->revents & POLLERR))
            {
                this->client_disconnect(it->fd);
                break;
            }

            if ((it->revents & POLLIN) == POLLIN)
            {
                if (it->fd == this->_nSocket)
                {
                   // new client connect;
                   this->new_connection();
                   break;
                }
                this->manage_cl_msg(it->fd);
            }
        }
    }
}



void Server::start(void)
{

    //Initialize the socket
    this->_nSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (this->_nSocket < 0)
        throw std::runtime_error("Error while Creating server Socket!");

    //Initilize the environement for sockaddr structure
    srv.sin_family = AF_INET;
    srv.sin_port = htons(this->_port);
    srv.sin_addr.s_addr = inet_addr(SRV_IP);
    memset(&(srv.sin_zero), 0, 8);

    // making the socket NON-BLOCKING

    int optval = 1;
    if (setsockopt(this->_nSocket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)))
        throw std::runtime_error("Error while setting socket options!");

    if (fcntl(this->_nSocket, F_SETFL, O_NONBLOCK))
        throw std::runtime_error("Error while setting socket to NON-BLOCKING!");


    //Bind the socket to the local port
    if (bind(this->_nSocket, (sockaddr*)&srv, sizeof(sockaddr)))
        throw std::runtime_error("Error while bind!");
    
    // Listen the socket 
    if (listen(this->_nSocket, 5))
        throw std::runtime_error("Error while listen!");

}