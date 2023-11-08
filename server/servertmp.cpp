/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   servertmp.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssefboughanmi <youssefboughanmi@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 16:06:42 by youssefboug       #+#    #+#             */
/*   Updated: 2023/11/07 09:44:37 by youssefboug      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <poll.h>
typedef std::vector<pollfd>::iterator       pfd_iterator;

struct sockaddr_in srv;
#define PORT 9909
int nSocket;


std::vector<pollfd>  _pfds;


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


int main()
{
    //int nMaxFd;
    int nRet = 0;
    //Initialize the socket
    nSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    if (nSocket < 0)
    {
        std::cout << "The socket not opened" <<std::endl;
    }
    else
    {
        std::cout << "The socket opened" << std::endl;
    }

    //Initilize the environement for sockaddr structure
    srv.sin_family = AF_INET;
    srv.sin_port = htons(PORT);
    srv.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(&(srv.sin_zero), 0, 8);

    //About  the bloàcking vs Non Blocking sockets
    // 0 means Blocking and 1 means non blocking 
    // forcefully attacing socket to the port by making it reusable

    int optval = 1;
    if (setsockopt(nSocket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)))
        throw std::runtime_error("Error while setting socket options!");

    // making the socket NON-BLOCKING

    if (fcntl(nSocket, F_SETFL, O_NONBLOCK))
        throw std::runtime_error("Error while setting socket to NON-BLOCKING!");
    {
        std::cout << "ioctl ok"  << std::endl;
    }

    {
        std::cout << " setsockopt not ok !!!!!"  << std::endl;
    }

    //Bind the socket to the local port
    nRet = bind(nSocket, (sockaddr*)&srv, sizeof(sockaddr));
    if (nRet < 0)
    {
        std::cout << "Bind not ok " << std::endl;
    }
    else
    {
        std::cout << "Bind ok"  << std::endl;
    }
    
    // Listen the socket 
    nRet = listen(nSocket, 5);
    if (nRet < 0)
    {
        std::cout << "Listen not ok " << std::endl;
    }
    else
    {
        std::cout << "Listen ok " << std::endl;
    }



    pollfd srv = {nSocket, POLLIN, 0};
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
                if (it->fd == nSocket)
                {
                   // new_client_connect();
                   std::cout << "new connection" << std::endl;
                   new_connection(nSocket);
                   break;
                }
                char buffer[1024];
                recv(it->fd, buffer, sizeof(buffer), 0);
                std::cout << buffer << std::endl;

                memset(&(buffer), 0, 1024);
                //client_message(it->fd);
            }
        }



    }
    

}

