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
        
        int _nSocket;
        int _port;
        struct sockaddr_in srv;
    
};


#endif
