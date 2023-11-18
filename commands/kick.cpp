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

int Server::find_client_id_channel(std::string channel_name, std::string client_kick)
{
    std::set<int>::iterator it;
    std::set<int> set_cl = this->channel_map[channel_name].getClient_list();

    for (it = set_cl.begin(); it != set_cl.end(); ++it)
    {
        if(this->client_map[*it].getNick() == client_kick)
            return(*it);
    }
    return(-1);
}


void Server::kick(std::string channel_name, std::string client_kick, std::string rqt, int fd)
{
    std::set<int> set_cl = this->channel_map[channel_name].getClient_list();
    std::set<int> set_cl_op = this->channel_map[channel_name].getClient_list_operator();

    if(this->channel_map.find(channel_name) == this->channel_map.end())
        return;

    if(set_cl_op.find(fd) == set_cl_op.end())
        return;

    int fd_kick = this->find_client_id_channel(channel_name,client_kick);

    if(set_cl.find(fd_kick) == set_cl.end())
    {
        return;
    }
    //send msg
    std::set<int>::iterator it;
    std::string msg = RPL_KICK(this->client_map[fd].getNick(), this->client_map[fd].getUser() , rqt)  

    for (it = set_cl.begin(); it != set_cl.end(); ++it) 
        send(*it , msg.c_str(),  msg.length(), 0);

    this->channel_map[channel_name].delete_client_operator(fd_kick);
    this->channel_map[channel_name].delete_client(fd_kick);
    return;
}