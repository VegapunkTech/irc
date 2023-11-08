/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssefboughanmi <youssefboughanmi@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:31:58 by youssefboug       #+#    #+#             */
/*   Updated: 2023/11/07 10:17:13 by youssefboug      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
 #define SERVER_HPP

#include"client.hpp"
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
#include <cstring>
#include <vector>
#include <list>

#define SRV_IP "127.0.0.1"

#define RPL_WELCOME(User)                               std::string("001 ") + User + " :Welcome " + User + " to the ft_irc network\n"
#define RPL_PING(src)                                   std::string(":") + src + "@localhost PONG :localhost"


class Server
{
    public:
        Server(int port);
        virtual ~Server(void);
        Server(Server const & rhs);
        Server & operator=(Server const & rhs);

        int     getNSocket(void) const;
        int     getPort(void) const;
        void    run(void);


    private:
        Server(void);
        void    start(void);
        void    new_connection();

        
        int _nSocket;
        int _port;
        struct sockaddr_in srv;
        std::list<Client> client_list;

        
    
};


#endif
