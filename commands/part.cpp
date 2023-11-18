/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssefboughanmi <youssefboughanmi@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:31:58 by youssefboug       #+#    #+#             */
/*   Updated: 2023/11/07 10:17:13 by youssefboug      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include"../include/server.hpp"
#include"../utils/utils.hpp"

void Server::part(std::string channel_name, int fd, char *buffer)
{

    if(this->channel_map.find(channel_name) == this->channel_map.end())
        return;
    
    std::set<int> set_cl = this->channel_map[channel_name].getClient_list();
    if(set_cl.find(fd) == set_cl.end())
        return;

    
    std::set<int>::iterator it;
    for (it = set_cl.begin(); it != set_cl.end(); ++it) 
    {
        std::string msg = RPL_PART(this->client_map[fd].getNick(), this->client_map[fd].getUser() , buffer);
        send(*it , msg.c_str(),  msg.length(), 0);
    }


    // kick from channel
    this->channel_map[channel_name].delete_client(fd);
    this->channel_map[channel_name].delete_client_operator(fd);
}