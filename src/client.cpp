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
    std::cout << "Client created" << std::endl;
    return;
}

Client::~Client(void)
{
    std::cout << "Client deleted" << std::endl;
    return;
}

Client::Client(int id_socket) :_id_socket(id_socket)
{
    std::cout << "Client created with id" << std::endl;
    return;
}



Client::Client( Client const & src ) 
{
    *this = src;
    std::cout << "Client created by copy" << std::endl;
}

Client&   Client::operator=( const Client& rhs ) 
{

    this->_id_socket = rhs._id_socket;

    std::cout << "Client created by affectation" << std::endl;
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