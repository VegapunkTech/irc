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
#include"channel.hpp"
#include"../utils/rpl.hpp"
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
#include <map>
#include <set>

#define SRV_IP "127.0.0.1"


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
        void    parser(char *buffer, int fd);
        void    manage_cl_msg(int fd);
        std::string format_users(std::set<int> client_list);
        void get_client_infos(const char *buffer, int fd);

        //Command
        void    privmsg(std::string Channel, int id_socket, char *buffer);
        void    join(std::string channel_name, int id_socket);


        int _nSocket;
        int _port;
        struct sockaddr_in srv;
        std::map<int, Client> client_map;
        std::map<std::string, Channel> channel_map;

        
    
};


#endif
