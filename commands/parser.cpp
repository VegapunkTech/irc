/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssefboughanmi <youssefboughanmi@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:31:56 by youssefboug       #+#    #+#             */
/*   Updated: 2023/11/07 15:24:38 by youssefboug      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/server.hpp"
#include"../utils/utils.hpp"


void Server::parser(char *buffer, int fd)
{
    std::string bufferstr(buffer);

    //JOIN
    if(strncmp(buffer, "JOIN ", 5) == 0)
    {
        size_t posNewline = bufferstr.find_first_of("\r\n ", 5);
        if (posNewline != std::string::npos) 
        {
            std::string channelname = bufferstr.substr(5, posNewline - 5);
            if (channelname[0] == '#')
                    channelname.erase(channelname.begin());

            if (bufferstr[posNewline] == '\r' || bufferstr[posNewline] == '\n' ||bufferstr[posNewline] == '\0')
            {
                join(channelname, fd, std::string(""));
            }
            else
            {
                size_t posNewline2 = bufferstr.find_first_of("\r\n ", posNewline+1);
                if (posNewline2 != std::string::npos) 
                {
                    std::string password = bufferstr.substr(posNewline+1, posNewline2 - posNewline-1);
                    join(channelname, fd, password);
                }

            }
        }
    }

    //PRIVMSG
    if(strncmp(buffer, "PRIVMSG ", 8) == 0) 
    {
        size_t posspace = bufferstr.find(' ', 8);
        if (posspace != std::string::npos) {

            std::string test = bufferstr.substr(8, posspace - 8);
            if (test[0] == '#')
            {
                std::string channelname = test;
                channelname.erase(channelname.begin());
                this->privmsg_channel(channelname, fd, buffer);
            }
            else
            {
                std::string pseudo = test;
                this->privmsg_client(pseudo, fd, buffer);
            }
        }
    }

    //MODE
    if(strncmp(buffer, "MODE ", 5) == 0) 
    {
        size_t posspace = bufferstr.find(' ', 6);
        if (posspace != std::string::npos) 
        {
            if(bufferstr[5] != '#')
                return;
            std::string channelname = bufferstr.substr(6, posspace - 6);
            std::string command;
            std::string arg;
            std::string signe;

            size_t test = bufferstr.find_first_of("\r\n", posspace+1);
            if (posspace != std::string::npos) 
            {

                std::string cmd = bufferstr.substr(posspace+1, test - (posspace+1));
                size_t test1 = cmd.find(' ', 0);

                if (test1 != std::string::npos) {
                    command = cmd.substr(0, test1);
                    arg = cmd.substr(test1+1, bufferstr.length());
                }
                else 
                    command = cmd.substr(0, test1);
                for (std::size_t i = 0; i < command.length(); i++)
                {
                    if (command[i] == '+' || command[i] == '-')
                        signe = command[i];
                    else
                    {
                        if (command[i] == 'o' || command[i] == 'l' ||command[i] == 'k')
                            this->mode(channelname, signe, command[i] , arg , fd);
                        else
                            this->mode(channelname, signe, command[i] , std::string(""), fd);
                    }
                }
            }
        }
    }

    //QUIT
    if(strncmp(buffer, "QUIT :leaving" , 13) == 0)
        this->client_disconnect(fd);


    //PING
    if(strncmp(buffer, "PING 127.0.0.1" , 13) == 0)
    {
        std::string msg = RPL_PONG();
        send(fd , msg.c_str(),  msg.length(), 0);
    }

    //kick

    if(strncmp(buffer, "KICK ", 5) == 0) {
    
        std::string bufferstr(buffer);

        size_t posspace = bufferstr.find(' ', 6);
        if (posspace != std::string::npos) {

            std::string channelname = bufferstr.substr(6, posspace - 6);

            size_t posspace2 = bufferstr.find(' ', posspace+1);
            if (posspace2 != std::string::npos) {

                std::string pseudo = bufferstr.substr(posspace+1, posspace2 - posspace-1);

                if ((bufferstr[posspace2+1] == ':') && (bufferstr[posspace2+2] == '\r' || bufferstr[posspace2+2] == '\n'))
                {
                    bufferstr = bufferstr.substr(0, bufferstr.size() - 2);
                    bufferstr+=this->client_map[fd].getNick();
                }
                this->kick(channelname, pseudo , bufferstr, fd);
            }  
        }
    }

    //INVITE
    if(strncmp(buffer, "INVITE ", 7) == 0) 
    {
        std::string bufferstr(buffer);

        size_t posspace = bufferstr.find(' ', 8);
        if (posspace != std::string::npos) 
        {
            std::string pseudo = bufferstr.substr(7, posspace - 7);

            size_t posspace2 = bufferstr.find_first_of("\r\n", posspace);
            if (posspace2 != std::string::npos) 
            {
                std::string channelname = bufferstr.substr(posspace+2, posspace2 - posspace-2);
                this->invite( channelname,pseudo , fd);
            }
        }
    }

    //TOPIC
    if(strncmp(buffer, "TOPIC ", 6) == 0) 
    {
        std::string bufferstr(buffer);

        size_t posspace = bufferstr.find(' ', 7);
        if (posspace != std::string::npos) {

            std::string channelname = bufferstr.substr(7, posspace - 7);

            size_t posspace2 = bufferstr.find_first_of("\r\n", posspace+1);
            if (posspace2 != std::string::npos) 
            {
                std::string topic = bufferstr.substr(posspace+2, posspace2 - posspace-2);
                this->topic(channelname, topic , fd);
            }
        }
    }


    //PART
    if(strncmp(buffer, "PART ", 5) == 0)
    {
        std::string bufferstr(buffer);

        size_t posspace = bufferstr.find(' ', 5);
        if (posspace != std::string::npos) 
        {
            
            std::string channelname = bufferstr.substr(5, posspace - 5);
            if (channelname[0] == '#')
            {
                channelname.erase(channelname.begin());
                this->part(channelname, fd , buffer);
            }
        }
        else
        {
            size_t posspace = bufferstr.find_first_of("\r\n", 5);
            std::string channelname = bufferstr.substr(5, posspace - 5);
            if (channelname[0] == '#')
            {
                channelname.erase(channelname.begin());
                this->part(channelname, fd , buffer);
            }

        }

    }

    //Nick
    if(strncmp(buffer, "NICK ", 5) == 0)
    {
        size_t posspace = bufferstr.find_first_of("\r\n", 5);
        if (posspace != std::string::npos) 
        {
            std::string nick = bufferstr.substr(5, posspace - 5);
            if (nick[0] != '\0')
                this->nick(nick, fd);
        }
    }
}
