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

#include"channel.hpp"
#include"../utils/rpl.hpp"
#include"../utils/utils.hpp"
#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sstream>
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
        Server(int port, std::string pass);
        virtual ~Server(void);
        Server(Server const & rhs);
        Server & operator=(Server const & rhs);

        int             getNSocket(void) const;
        int             getPort(void) const;
        std::string     getPass(void) const;
        void            run(void);


    private:
        Server(void);
        void            start(void);
        void            new_connection();
        void            parser(char *buffer, int fd);
        void            manage_cl_msg(int fd);
        std::string     format_users(std::set<int> client_list, std::set<int> set_operator);
        void            get_client_infos(std::string bufferstr, int fd);
        void            delete_pfd(int  fd);
        void            client_disconnect(int fd);
        
        //Mode
        void            mode(std::string channel_name, std::string signe, char mode , std::string arg, int fd);
        void            run_mode_l(std::string channel_name, std::string signe , std::string arg,int id_socket);
        void            run_mode_o(std::string channel_name, std::string signe , std::string arg, int id_socket);
        void            run_mode_k(std::string channel_name, std::string signe , std::string arg, int id_socket);
        void            run_mode_t(std::string channel_name, std::string signe, int id_socket);
        void            run_mode_i(std::string channel_name, std::string signe, int id_socket);
        int             find_client_id_channel(std::string channel_name, std::string client_kick);

        //Command
        void            privmsg(std::string Channel, int id_socket, char *buffer);
        void            join(std::string channel_name, int id_socket);
        std::set<int>   getClientChannel(int fd);
        void            kick(std::string channel_name, std::string client_kick, std::string rqt, int fd);


        int                                 _nSocket;
        int                                 _port;
        std::string                         _pass;
        struct sockaddr_in                  srv;
        std::map<int, Client>               client_map;
        std::map<std::string, Channel>      channel_map;
        std::vector<pollfd>                 _pfds;
};


#endif
