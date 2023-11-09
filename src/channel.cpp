/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssefboughanmi <youssefboughanmi@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:31:58 by youssefboug       #+#    #+#             */
/*   Updated: 2023/11/07 10:17:13 by youssefboug      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/channel.hpp"

Channel::Channel( void )
{
    std::cout << "Channel Created" << std::endl;
    return;
}

Channel::~Channel(void)
{
    std::cout << "Channel deleted" << std::endl;
    return;
}

Channel::Channel(std::string name) :_name(name)
{
    std::cout << "Channel "<< name << " created" << std::endl;
    return;
}

// getters
std::string Channel::getName()  
{
    return(this->_name);
}

std::set<int> Channel::getClient_list() 
{
    return(this->_client_list);
}

//setters
void Channel::setName(std::string name)
{
    this->_name = name;
}

//append client
void Channel::append_client(int id_socket)
{
    this->_client_list.insert(id_socket);
}

//append client
void Channel::delete_client(int id_socket)
{
    this->_client_list.erase(id_socket);
}