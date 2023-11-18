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

int Server::find_client_id(std::string client_invited)
{
    std::map<int, Client>::iterator it;

    for (it = this->client_map.begin(); it != this->client_map.end(); ++it)
    {
        if(it->second.getNick() == client_invited)
            return(it->first);
    }
    return(-1);
}

void Server::invite(std::string channel_name, std::string client_invited, int fd)
{
    std::set<int> set_cl = this->channel_map[channel_name].getClient_list();
    std::set<int> set_cl_op = this->channel_map[channel_name].getClient_list_operator();
    std::set<int> set_cl_inv = this->channel_map[channel_name].getClient_list_invited();

    //channel exit
    if(this->channel_map.find(channel_name) == this->channel_map.end())
        return;
    //fd is operator 
    if(set_cl_op.find(fd) == set_cl_op.end())
        return;


    //client exist 
    int fd_invited = this->find_client_id(client_invited);
    if(fd_invited == -1)
    {
        std::string msg= RPL_INVITE_NO(this->client_map[fd].getNick(), client_invited);
        send(fd, msg.c_str(), msg.length() , 0);
        return;
    }
    this->channel_map[channel_name].append_client_invited(fd_invited);

    std::string msg= RPL_INVITE_SEND(this->client_map[fd].getNick(), client_invited, channel_name);
    send(fd, msg.c_str(), msg.length() , 0);

    if((set_cl.find(fd_invited) == set_cl.end()))
    {
        msg = RPL_INVITE_RECV(this->client_map[fd].getNick(), this->client_map[fd].getUser(), client_invited, channel_name);
        send(fd_invited, msg.c_str(), msg.length() , 0);
    }
    return;
}
