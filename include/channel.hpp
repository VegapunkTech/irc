/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssefboughanmi <youssefboughanmi@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:31:58 by youssefboug       #+#    #+#             */
/*   Updated: 2023/11/07 10:17:13 by youssefboug      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CHANNEL_HPP
 #define CHANNEL_HPP  

#include <string>
#include <cstddef>
#include <iostream>
#include <set>

class Channel 
{

    private:
        std::string _name;
        std::string _pass;
        std::string _topic;
        unsigned int _limit;
        std::set<int> _client_list;
        std::set<int> _client_list_invited;
        std::set<int> _client_list_operator;

        bool _mode_i;
        bool _mode_t;
        bool _mode_k;
        bool _mode_l;

    public:
        Channel(std::string name);
        Channel();
        ~Channel(void);

        // getters
        std::string getName(); 
        std::string getPass();
        unsigned int getLimit();
        std::string  getTopic();

        std::set<int> getClient_list();
        std::set<int> getClient_list_invited();
        std::set<int> getClient_list_operator();
        bool getMode_i();
        bool getMode_t();
        bool getMode_k();
        bool getMode_l();

        //setters
        void setName(std::string name);
        void setPass(std::string pass);
        void setLimit(unsigned int limit);
        void setMode_i(bool n);
        void setMode_t(bool n);
        void setMode_k(bool n);
        void setMode_l(bool n);
        void setTopic(std::string topic);
        //append delete client 
        void append_client(int id_socket);
        void delete_client(int id_socket);

        void append_client_invited(int id_socket);
        void delete_client_invited(int id_socket);

        void append_client_operator(int id_socket);
        void delete_client_operator(int id_socket);
};

#endif