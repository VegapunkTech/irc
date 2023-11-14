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


void Server::join(std::string channel_name, int id_socket)
{
    std::set<int> set_client;
    std::set<int> set_operator;
    std::set<int>::iterator it;

    //check if channel name exist 
    if(this->channel_map.find(channel_name) !=  this->channel_map.end())
        this->channel_map[channel_name].append_client(id_socket);

    //else created 
    else
    {
        this->channel_map[channel_name].setName(channel_name);
        this->channel_map[channel_name].append_client(id_socket);
        this->channel_map[channel_name].append_client_operator(id_socket);
    }

    //send messages to clients
    set_client = this->channel_map[channel_name].getClient_list();
    set_operator = this->channel_map[channel_name].getClient_list_operator();

    for (it = set_client.begin(); it != set_client.end(); ++it) 
    {
        std::string msg = RPL_JOIN(this->client_map[id_socket].getNick(), this->client_map[id_socket].getUser(), channel_name) + \
                            RPL_NAMREPLY(this->client_map[id_socket].getUser(), channel_name, this->format_users(set_client , set_operator)) + \
                                RPL_ENDOFNAMES(this->client_map[id_socket].getUser(), channel_name);
        send(*it , msg.c_str(),  msg.length(), 0);
        std::cout << msg << std::endl;
    }
}
