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

Channel::Channel( void ) : _mode_i(0), _mode_t(0), _mode_k(0), _mode_l(0)
{
    return;
}

Channel::~Channel(void)
{
    return;
}

Channel::Channel(std::string name) :_name(name), _mode_i(0), _mode_t(0), _mode_k(0), _mode_l(0)
{
    return;
}


















// getters
std::string Channel::getName()  
{
    return(this->_name);
}

std::string Channel::getPass()  
{
    return(this->_pass);
}

unsigned int Channel::getLimit()
{
    return(this->_limit);
}

std::set<int> Channel::getClient_list() 
{
    return(this->_client_list);
}

std::set<int> Channel::getClient_list_invited() 
{
    return(this->_client_list_invited);
}

std::set<int> Channel::getClient_list_operator() 
{
    return(this->_client_list_operator);
}

bool Channel::getMode_i()
{
    return(this->_mode_i);
}

bool Channel::getMode_t()
{
    return(this->_mode_t);
}

bool Channel::getMode_k()
{
    return(this->_mode_k);
}

bool Channel::getMode_l()
{
    return(this->_mode_l);
}


std::string Channel::getTopic()
{
    return(this->_topic);
}





























//setters
void Channel::setName(std::string name)
{
    this->_name = name;
}

void Channel::setPass(std::string pass)
{
    this->_pass = pass;
}

void Channel::setLimit(unsigned int limit)
{
    this->_limit = limit;
}

void Channel::setMode_i(bool n)
{
    this->_mode_i = n;
}
void Channel::setMode_t(bool n)
{
    this->_mode_t = n;
}

void Channel::setMode_k(bool n)
{
    this->_mode_k = n;
}

void Channel::setMode_l(bool n)
{
    this->_mode_l = n;
}

void Channel::setTopic(std::string topic)
{
    this->_topic = topic;
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

//append client invited
void Channel::append_client_invited(int id_socket)
{
    this->_client_list_invited.insert(id_socket);
}

//append client invited
void Channel::delete_client_invited(int id_socket)
{
    this->_client_list_invited.erase(id_socket);
}

//append client invited
void Channel::append_client_operator(int id_socket)
{
    this->_client_list_operator.insert(id_socket);
}

//append client invited
void Channel::delete_client_operator(int id_socket)
{
    this->_client_list_operator.erase(id_socket);
}