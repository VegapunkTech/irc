/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssefboughanmi <youssefboughanmi@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:31:58 by youssefboug       #+#    #+#             */
/*   Updated: 2023/11/07 10:17:13 by youssefboug      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPL_HPP
 #define RPL_HPP


#define RPL_WELCOME(Nick) ("001 " + std::string(Nick) + " :Welcome " + std::string(Nick) + " to the ft_irc network\r\n")

/*
>> :nick!monkey@localhost JOIN :#test
>> :localhost 353 monkey = #test :@nick
>> :localhost 366 monkey #test :End of /NAMES list.

*/

#define RPL_JOIN(Nick, User, Channel)                 (std::string(":") + Nick + "!" + User + "@localhost JOIN :#" + Channel + "\r\n")                                                 
#define RPL_NAMREPLY(User, Channel, Users)            (std::string(":localhost 353 ") + User + " = " + Channel + " :" + Users + "\r\n")
#define RPL_ENDOFNAMES(User, Channel)                 (std::string(":localhost 366 ") + User + " #" + Channel + " :End of /NAMES list.\r\n")

/*
:test!youssef@localhost PRIVMSG #Channel :salut
*/

#define RPL_PRIVMSG(Nick, User , buffer)              (std::string(":") + Nick + "!" + User + "@localhost " + buffer + "\r\n")


/*MODE*/

// :nicks!~youssef@66.225.88.79.rev.sfr.net MODE #re +i
#define RPL_MODE_I(Nick, User, Channel , Signe)                 (std::string(":") + Nick + "!~" + User + "@localhost MODE #" + Channel +" " + Signe +"i \r\n")    
#define RPL_MODE_T(Nick, User, Channel , Signe)                 (std::string(":") + Nick + "!~" + User + "@localhost MODE #" + Channel +" " + Signe +"t \r\n") 

//:youssef_!~youssef@79.88.225.66 MODE #kks +k pass
#define RPL_MODE_K(Nick, User, Channel , Signe, arg)                 (std::string(":") + Nick + "!~" + User + "@localhost MODE #" + Channel +" " + Signe +"k " + arg +"\r\n") 

//:youssef!~youssef@79.88.225.66 MODE #re -o t1
#define RPL_MODE_O(Nick, User, Channel , Signe, arg)                 (std::string(":") + Nick + "!~" + User + "@localhost MODE #" + Channel +" " + Signe +"o " + arg +"\r\n") 


#endif
