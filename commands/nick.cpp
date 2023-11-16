/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssefboughanmi <youssefboughanmi@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:31:58 by youssefboug       #+#    #+#             */
/*   Updated: 2023/11/07 10:17:13 by youssefboug      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/server.hpp"
#include"../utils/utils.hpp"


void Server::nick(std::string new_nick, int fd)
{
    //same nick
    if(this->client_map[fd].getNick() == new_nick)
        return;
    if(Nick_exist(new_nick, fd))
    {
        std::string msg = RPL_NICK_EXIST(this->client_map[fd].getNick(), new_nick);
        send(fd, msg.c_str(), msg.length(), 0);
        return;        
    }

    std::string msg = RPL_NICK(this->client_map[fd].getNick(), this->client_map[fd].getUser(), new_nick);
    std::set<int>   set_client = this->getClientChannel(fd);

    set_client.insert(fd);
    for (std::set<int>::iterator it = set_client.begin(); it != set_client.end(); ++it)
    {
        send(*it , msg.c_str(),  msg.length(), 0);
    }
    this->client_map[fd].setNick(new_nick);
}