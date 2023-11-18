/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssefboughanmi <youssefboughanmi@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:31:58 by youssefboug       #+#    #+#             */
/*   Updated: 2023/11/07 10:17:13 by youssefboug      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include"../include/server.hpp"
#include"../utils/utils.hpp"


std::string Server::format_users(std::set<int> set_client, std::set<int> set_operator)
{
    std::set<int>::iterator it;
    std::string format_users("");

    for (it = set_client.begin(); it != set_client.end(); ++it) 
    {
        if (set_operator.find(*it) != set_operator.end())
            format_users+= "@" + this->client_map[*it].getNick() + " ";
        else
            format_users+= this->client_map[*it].getNick() + " ";
    }
    return(format_users);
}


void Server::join(std::string channel_name, int id_socket, std::string pass)
{
    std::set<int> set_client;
    std::set<int> set_operator;
    std::set<int>::iterator it;
    std::string msg;

    //check if channel name exist 
    if(this->channel_map.find(channel_name) !=  this->channel_map.end())
    {
        std::set<int> set_cl = this->channel_map[channel_name].getClient_list();
        std::set<int> set_cl_inv = this->channel_map[channel_name].getClient_list_invited();
        //not invited 
        if(this->channel_map[channel_name].getMode_i() == 1 &&
            set_cl_inv.find(id_socket) == set_cl_inv.end())
        {
            std::string msg = RPL_JOIN_NOT_INVITED(this->client_map[id_socket].getNick(), channel_name);
            send(id_socket, msg.c_str(), msg.length(), 0);
            return;
        }
        //limit Max
        if(this->channel_map[channel_name].getMode_l() == 1 &&
           set_cl.size() == this->channel_map[channel_name].getLimit())
        {
            std::string msg = RPL_JOIN_LIMIT(this->client_map[id_socket].getNick(), channel_name);
            send(id_socket, msg.c_str(), msg.length(), 0);
            return;
        }

        //bad pass
        if(this->channel_map[channel_name].getMode_k() == 1 &&
           pass != this->channel_map[channel_name].getPass())
        {
            std::string msg = RPL_JOIN_BAD_PASS(this->client_map[id_socket].getNick(), channel_name);
            send(id_socket, msg.c_str(), msg.length(), 0);
            return;
        }

        this->channel_map[channel_name].append_client(id_socket);
        this->client_map[id_socket].append_channel(channel_name);
    }

    //else created 
    else
    {
        this->channel_map[channel_name].setName(channel_name);
        this->channel_map[channel_name].setMode_t(1);
        this->channel_map[channel_name].append_client(id_socket);
        this->channel_map[channel_name].append_client_operator(id_socket);
        this->client_map[id_socket].append_channel(channel_name);
    }



    //send messages to clients
    set_client = this->channel_map[channel_name].getClient_list();
    set_operator = this->channel_map[channel_name].getClient_list_operator();

    if(this->channel_map[channel_name].getTopic().length() > 0)
    {
        msg = RPL_JOIN(this->client_map[id_socket].getNick(), this->client_map[id_socket].getUser(), channel_name) + \
                RPL_JOIN_TOPIC(this->client_map[id_socket].getNick(), channel_name, this->channel_map[channel_name].getTopic()) + \
                RPL_NAMREPLY(this->client_map[id_socket].getUser(), channel_name, this->format_users(set_client , set_operator)) + \
                RPL_ENDOFNAMES(this->client_map[id_socket].getUser(), channel_name);
    }
    else
    {
       msg = RPL_JOIN(this->client_map[id_socket].getNick(), this->client_map[id_socket].getUser(), channel_name) + \
                RPL_NAMREPLY(this->client_map[id_socket].getUser(), channel_name, this->format_users(set_client , set_operator)) + \
                RPL_ENDOFNAMES(this->client_map[id_socket].getUser(), channel_name);
    }

    send(id_socket , msg.c_str(),  msg.length(), 0);
    msg = RPL_JOIN(this->client_map[id_socket].getNick(), this->client_map[id_socket].getUser(), channel_name);
    for (it = set_client.begin(); it != set_client.end(); ++it) 
    {
        if(*it == id_socket)
            continue;
        send(*it , msg.c_str(),  msg.length(), 0);
    }
}
