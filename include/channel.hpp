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
        std::set<int> _client_list;


    public:
        Channel(std::string name);
        Channel();
        ~Channel(void);

        // getters
        std::string getName(); 
        std::set<int> getClient_list();

        //setters
        void setName(std::string name);
        
        //append client
        void append_client(int id_socket);
        void delete_client(int id_socket);

};

#endif