/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssefboughanmi <youssefboughanmi@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:31:58 by youssefboug       #+#    #+#             */
/*   Updated: 2023/11/07 10:17:13 by youssefboug      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/client.hpp"

Client::Client( void )
{
    return;
}

Client::~Client(void)
{
    return;
}

Client::Client(int id_socket) :_id_socket(id_socket)
{
    return;
}



Client::Client( Client const & src ) 
{
    *this = src;
}

Client&   Client::operator=( const Client& rhs ) 
{

    this->_id_socket = rhs._id_socket;

    return *this;
}

// getters
std::string Client::getUser()  
{
    return(this->_user);
}

std::string Client::getNick() 
{
    return(this->_nick);
}
        
int Client::getId_socket() 
{
    return (this->_id_socket);
}

std::set<std::string> Client::getSet_channel()
{
    return (this->set_channel);
}

// setters
void Client::setUser(std::string user) 
{
    this->_user = user;
}

void Client::setNick(std::string nick) 
{
    this->_nick = nick;
}


void Client::setIdSocket(int id_socket) 
{
    this->_id_socket = id_socket;
}

//append channel
void Client::append_channel(std::string channel_name)
{
    this->set_channel.insert(channel_name);
}