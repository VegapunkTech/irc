/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssefboughanmi <youssefboughanmi@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:31:56 by youssefboug       #+#    #+#             */
/*   Updated: 2023/11/07 15:24:38 by youssefboug      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/server.hpp"
#include"../utils/utils.hpp"

void Server::run_mode_i(std::string channel_name, std::string signe, int id_socket)
{

    int old_signe = this->channel_map[channel_name].getMode_i();

    if(strncmp(signe.c_str(), "+", 1) == 0)
        this->channel_map[channel_name].setMode_i(1);
    if(strncmp(signe.c_str(), "-", 1) == 0)
        this->channel_map[channel_name].setMode_i(0);

    if((old_signe == 0 && strncmp(signe.c_str(), "+", 1) == 0 ) ||
        ( old_signe == 1 && strncmp(signe.c_str(), "-", 1) == 0 ))
    {
        std::set<int> set_client = this->channel_map[channel_name].getClient_list();
        std::set<int>::iterator it;

        for (it = set_client.begin(); it != set_client.end(); ++it) 
        {
            std::string msg = RPL_MODE_I(this->client_map[id_socket].getNick(), this->client_map[id_socket].getUser() , channel_name , signe);
            send(*it , msg.c_str(),  msg.length(), 0);
        }
    }
}


void Server::run_mode_t(std::string channel_name, std::string signe, int id_socket)
{

    int old_signe = this->channel_map[channel_name].getMode_t();

    if(strncmp(signe.c_str(), "+", 1) == 0)
        this->channel_map[channel_name].setMode_t(1);
    if(strncmp(signe.c_str(), "-", 1) == 0)
        this->channel_map[channel_name].setMode_t(0);

    if((old_signe == 0 && strncmp(signe.c_str(), "+", 1) == 0 ) ||
        ( old_signe == 1 && strncmp(signe.c_str(), "-", 1) == 0 ))
    {
        std::set<int> set_client = this->channel_map[channel_name].getClient_list();
        std::set<int>::iterator it;

        for (it = set_client.begin(); it != set_client.end(); ++it) 
        {
            std::string msg = RPL_MODE_T(this->client_map[id_socket].getNick(), this->client_map[id_socket].getUser() , channel_name , signe);
            send(*it , msg.c_str(),  msg.length(), 0);
        }
    }
}


void Server::run_mode_k(std::string channel_name, std::string signe , std::string arg, int id_socket)
{
    if(arg.length() == 0)
        return;

    int old_signe = this->channel_map[channel_name].getMode_k();

    if((strncmp(signe.c_str(), "+", 1) == 0) && (old_signe != 1)) 
    {
        this->channel_map[channel_name].setMode_k(1);
        this->channel_map[channel_name].setPass(arg);
    }
    if(strncmp(signe.c_str(), "-", 1) == 0)
    {
        if(arg != this->channel_map[channel_name].getPass())
            return;
        this->channel_map[channel_name].setMode_k(0);
    }

    if((old_signe == 0 && strncmp(signe.c_str(), "+", 1) == 0 ) ||
        ( old_signe == 1 && strncmp(signe.c_str(), "-", 1) == 0 ))
    {
        std::set<int> set_client = this->channel_map[channel_name].getClient_list();
        std::set<int>::iterator it;

        for (it = set_client.begin(); it != set_client.end(); ++it) 
        {
            std::string msg = RPL_MODE_K(this->client_map[id_socket].getNick(), this->client_map[id_socket].getUser() , channel_name , signe, arg);
            send(*it , msg.c_str(),  msg.length(), 0);
        }
    }
}





void Server::run_mode_o(std::string channel_name, std::string signe , std::string arg,int id_socket)
{
    int fd = -1;
    int send_msg = 0;
    std::set<int> set_client = this->channel_map[channel_name].getClient_list();
    std::set<int>::iterator it;


    for (it = set_client.begin(); it != set_client.end(); ++it) 
    {
        if( this->client_map[*it].getNick() == arg)
            fd = *it;
    }
    if(fd == -1)
        return;
    std::set<int> set_client_op = this->channel_map[channel_name].getClient_list_operator();

    if((strncmp(signe.c_str(), "+", 1) == 0 ) && (set_client_op.find(fd) == set_client_op.end()))
    {
        this->channel_map[channel_name].append_client_operator(fd);
        send_msg = 1;
    }
    if(strncmp(signe.c_str(), "-", 1) == 0 && set_client_op.find(fd) != set_client_op.end())
    {
        this->channel_map[channel_name].delete_client_operator(fd);
        send_msg = 1;
    }

    if(send_msg)
    {
        std::set<int> set_client = this->channel_map[channel_name].getClient_list();
        std::set<int>::iterator it;

        for (it = set_client.begin(); it != set_client.end(); ++it) 
        {
            std::string msg = RPL_MODE_O(this->client_map[id_socket].getNick(), this->client_map[id_socket].getUser() , channel_name , signe, arg);
            send(*it , msg.c_str(),  msg.length(), 0);
        }
    }

}



void Server::run_mode_l(std::string channel_name, std::string signe , std::string arg, int id_socket)
{
    int send_msg = 0;

    if(strncmp(signe.c_str(), "+", 1) == 0 
        && std::atoi(arg.c_str()) > 0
        && (unsigned int)std::atoi(arg.c_str()) != this->channel_map[channel_name].getLimit())
    {
        this->channel_map[channel_name].setMode_l(1);
        this->channel_map[channel_name].setLimit(std::atoi(arg.c_str()));
        send_msg = 1;
        std::stringstream convertisseur;
        convertisseur <<  std::atoi(arg.c_str());
        arg = convertisseur.str();
    }
    if(strncmp(signe.c_str(), "-", 1) == 0
         && this->channel_map[channel_name].getMode_l() == 1)
    {
        this->channel_map[channel_name].setMode_l(0);
        send_msg = 1;
        arg = std::string("");
    }

    if(send_msg == 1)
    {
        std::set<int> set_client = this->channel_map[channel_name].getClient_list();
        std::set<int>::iterator it;

        for (it = set_client.begin(); it != set_client.end(); ++it) 
        {
            std::string msg = RPL_MODE_L(this->client_map[id_socket].getNick(), this->client_map[id_socket].getUser() 
                , channel_name , signe, arg);
            send(*it , msg.c_str(),  msg.length(), 0);
        }
    }
}



void Server::mode(std::string channel_name, std::string signe, char mode , std::string arg, int fd)
{
    std::set<int> set_cl = this->channel_map[channel_name].getClient_list_operator();

    if(this->channel_map.find(channel_name) == this->channel_map.end())
        return;
    if(set_cl.find(fd) == set_cl.end())
        return;


    if(mode == 'i')
        this->run_mode_i(channel_name , signe, fd);
    if(mode == 't')
        this->run_mode_t(channel_name , signe, fd);
    if(mode == 'k')
        this->run_mode_k(channel_name , signe, arg, fd);
    if(mode == 'o')
        this->run_mode_o(channel_name , signe, arg, fd);
    if(mode == 'l')
        this->run_mode_l(channel_name , signe, arg, fd);
}
