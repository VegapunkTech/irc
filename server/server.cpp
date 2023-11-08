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

#include"server.hpp"

typedef std::vector<pollfd>::iterator       pfd_iterator;
std::vector<pollfd>  _pfds;


Server::Server(int port) : _port(port)
{
    std::cout << "Server created" << std::endl;
    return;
}

Server::~Server( void )
{
    std::cout << "Server deleted" << std::endl;
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


void new_connection(int nSocket)
{
    int         fd;
    sockaddr_in addr = {};
    socklen_t   size = sizeof(addr);

    fd = accept(nSocket, (sockaddr *) &addr, &size);
    if (fd < 0)
        throw std::runtime_error("Error while accepting a new client!");

    // including the client fd in the poll

    pollfd  pfd = {fd, POLLIN, 0};
    _pfds.push_back(pfd);

}


void manage_cl_msg(int fd, int nSocket)
{     
    char buffer[1024];
    recv(fd, buffer, sizeof(buffer), 0);

    std::cout << buffer << std::endl;
    for (pfd_iterator it = _pfds.begin(); it != _pfds.end(); it++)
    {
        if (it->fd != fd && it->fd != nSocket)
            send(it->fd, buffer , strlen(buffer) , 0);            
            
    }
    memset(&(buffer), 0, 1024);
}

void Server::run(void)
{
    this->start();

    pollfd srv = {this->_nSocket, POLLIN, 0};
    _pfds.push_back(srv);

    //Keep waiting for new requests and proceed as per the request
    while(1)
    {
        poll(_pfds.begin().base(), _pfds.size(), -1);

        //boucler sur tout les pollfd 
        for (pfd_iterator it = _pfds.begin(); it != _pfds.end(); it++)
        {
            if (it->revents == 0)
                continue;

            if ((it->revents & POLLHUP) == POLLHUP)
            {
                //client_disconnect(it->fd);
                break;
            }

            if ((it->revents & POLLIN) == POLLIN)
            {
                if (it->fd == this->_nSocket)
                {
                   // new_client_connect();
                   //std::cout << "new connection" << std::endl;
                   new_connection(this->_nSocket);
                   break;
                }

                manage_cl_msg(it->fd , this->_nSocket);
            }
        }



    }
}


void Server::start(void)
{
    int nRet = 0;

    //Initialize the socket
    this->_nSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    if (this->_nSocket < 0)
    {
        std::cout << "The socket not opened" <<std::endl;
    }
    else
    {
        std::cout << "The socket opened" << std::endl;
    }

    //Initilize the environement for sockaddr structure
    srv.sin_family = AF_INET;
    srv.sin_port = htons(this->_port);
    srv.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(&(srv.sin_zero), 0, 8);

    // making the socket NON-BLOCKING

    int optval = 1;
    if (setsockopt(this->_nSocket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)))
        throw std::runtime_error("Error while setting socket options!");

    if (fcntl(this->_nSocket, F_SETFL, O_NONBLOCK))
        throw std::runtime_error("Error while setting socket to NON-BLOCKING!");
    {
        std::cout << "ioctl ok"  << std::endl;
    }

    {
        std::cout << " setsockopt not ok !!!!!"  << std::endl;
    }

    //Bind the socket to the local port
    nRet = bind(this->_nSocket, (sockaddr*)&srv, sizeof(sockaddr));
    if (nRet < 0)
    {
        std::cout << "Bind not ok " << std::endl;
    }
    else
    {
        std::cout << "Bind ok"  << std::endl;
    }
    
    // Listen the socket 
    nRet = listen(this->_nSocket, 5);
    if (nRet < 0)
    {
        std::cout << "Listen not ok " << std::endl;
    }
    else
    {
        std::cout << "Listen ok " << std::endl;
    }

}