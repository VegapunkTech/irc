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


void Server::privmsg_channel(std::string channel_name, int id_socket, char *buffer)
{
    //channel exist 
    if(this->channel_map.find(channel_name) == this->channel_map.end())
    {
        std::string msg = RPL_PRIVMSG_NO_CHANNEL(this->client_map[id_socket].getNick() , channel_name);
        send(id_socket, msg.c_str(), msg.length(), 0);
        return;
    }

    std::set<int> set_client;
    std::set<int>::iterator it;

    set_client = this->channel_map[channel_name].getClient_list();

    for (it = set_client.begin(); it != set_client.end(); ++it) 
    {
        if(*it == id_socket)
            continue;

        std::string msg = RPL_PRIVMSG_CHANNEL(this->client_map[id_socket].getNick(), this->client_map[id_socket].getUser() , buffer);
        send(*it , msg.c_str(),  msg.length(), 0);
    }
}

void Server::privmsg_client(std::string client_name, int id_socket, char *buffer)
{

    //client n'exite pas 
    if(find_client_id(client_name) == -1)
    {
        std::string msg = RPL_PRIVMSG_NO_CLIENT(this->client_map[id_socket].getNick() , client_name);
        send(id_socket, msg.c_str(), msg.length(), 0);
        return;
    }


    int id_client = this->find_client_id(client_name);
    std::string msg = RPL_PRIVMSG_CLIENT(this->client_map[id_socket].getNick() , this->client_map[id_socket].getUser() , buffer);
    send(id_client, msg.c_str(), msg.length(), 0);
    return;
}
