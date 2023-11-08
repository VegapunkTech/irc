/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssefboughanmi <youssefboughanmi@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:31:58 by youssefboug       #+#    #+#             */
/*   Updated: 2023/11/07 10:17:13 by youssefboug      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CLIENT_HPP
 #define CLIENT_HPP  

#include <string>
#include <cstddef>
#include <iostream>

class Client 
{

    private:
        std::string _user;
        std::string _nick;

        int _id_socket;
        Client();

    public:
        Client(int id_socket);

        // getters
        std::string getUser() ; 
        std::string getNick() ;
        int getId_socket() ;


        // setters
        void setUser(std::string user);
        void setNick(std::string nick);
        void setIdSocket(int id_socket);

};

#endif