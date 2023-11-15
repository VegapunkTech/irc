/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssefboughanmi <youssefboughanmi@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:31:58 by youssefboug       #+#    #+#             */
/*   Updated: 2023/11/07 10:17:13 by youssefboug      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include"../include/server.hpp"
#include"../utils/utils.hpp"



std::set<int>   Server::getClientChannel(int fd)
{
    std::set<std::string>   channel_set = this->client_map[fd].getSet_channel();
    std::set<int>           set_all_client;
    std::set<int>           set_client;


    for (std::set<std::string>::iterator it = channel_set.begin(); it != channel_set.end(); ++it)
    {
        set_client = this->channel_map[*it].getClient_list();
        set_all_client.insert(set_client.begin(), set_client.end());
    }
    return(set_all_client);
}

void Server::client_disconnect(int fd)
{
    /* set rpl */
    std::string msg = RPL_EXIT(this->client_map[fd].getNick(), this->client_map[fd].getUser());

    std::set<int>   set_client = this->getClientChannel(fd);
    for (std::set<int>::iterator it = set_client.begin(); it != set_client.end(); ++it) 
        send(*it , msg.c_str(),  msg.length(), 0);

    delete_pfd(fd);
    this->client_map.erase(fd);
    close(fd);
}

