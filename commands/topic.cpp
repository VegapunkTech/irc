/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssefboughanmi <youssefboughanmi@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:31:58 by youssefboug       #+#    #+#             */
/*   Updated: 2023/11/07 10:17:13 by youssefboug      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include"../include/server.hpp"
#include"../utils/utils.hpp"


void Server::topic(std::string channel_name, std::string topic , int fd)
{
    std::set<int>::iterator it;
    std::set<int> set_cl = this->channel_map[channel_name].getClient_list();
    std::set<int> set_cl_op = this->channel_map[channel_name].getClient_list_operator();

    //channel exit
    if(this->channel_map.find(channel_name) == this->channel_map.end())
        return;


    //Client in channel 
    if(set_cl.find(fd) == set_cl.end())
    {
        std::string msg = RPL_TOPIC_NO_CHANNEL(this->client_map[fd].getNick() , channel_name);
        send(fd, msg.c_str() , msg.length() , 0);
        return;
    }

    //Client not operator 
    if(set_cl_op.find(fd) == set_cl_op.end() && this->channel_map[channel_name].getMode_t())
    {
        std::string msg = RPL_TOPIC_NO_OP(this->client_map[fd].getNick() , channel_name);
        send(fd, msg.c_str() , msg.length() , 0);
        return;
    }


    for (it = set_cl.begin(); it != set_cl.end(); ++it) 
    {
        std::string msg = RPL_TOPIC(this->client_map[fd].getNick(), this->client_map[fd].getUser(), topic ,channel_name);
        send(*it , msg.c_str(),  msg.length(), 0);
    }
    this->channel_map[channel_name].setTopic(topic);
}