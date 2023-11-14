/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssefboughanmi <youssefboughanmi@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:31:56 by youssefboug       #+#    #+#             */
/*   Updated: 2023/11/07 15:24:38 by youssefboug      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/server.hpp"
#include"../utils/utils.hpp"


void Server::privmsg(std::string channel_name, int id_socket, char *buffer)
{

    std::set<int> set_client;
    std::set<int>::iterator it;

    set_client = this->channel_map[channel_name].getClient_list();

    for (it = set_client.begin(); it != set_client.end(); ++it) 
    {
        if(*it == id_socket)
            continue;

        std::string msg = RPL_PRIVMSG(this->client_map[id_socket].getNick(), this->client_map[id_socket].getUser() , buffer);
        send(*it , msg.c_str(),  msg.length(), 0);
        std::cout << msg << std::endl;
    }
}