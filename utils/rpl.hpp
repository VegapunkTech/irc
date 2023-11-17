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
>> :localhost 332 youssef_ #re :lol
>> :localhost 353 monkey = #test :@nick
>> :localhost 366 monkey #test :End of /NAMES list.

*/

#define RPL_JOIN(Nick, User, Channel)                 (std::string(":") + Nick + "!" + User + "@localhost JOIN :#" + Channel + "\r\n") 
#define RPL_JOIN_TOPIC(Nick , Channel , Topic)        (std::string(":localhost 332 ") + Nick + " #" + Channel + " :" + Topic + "\r\n")                              
#define RPL_NAMREPLY(Nick, Channel, Users)            (std::string(":localhost 353 ") + Nick + " = #" + Channel + " :" + Users + "\r\n")
#define RPL_ENDOFNAMES(Nick, Channel)                 (std::string(":localhost 366 ") + Nick + " #" + Channel + " :End of /NAMES list.\r\n")



//:underworld2.no.quakenet.org 473 youssef_ #re :Cannot join channel, you must be invited (+i)

#define RPL_JOIN_NOT_INVITED(Nick, Channel)                  (std::string(":localhost 473 ") + Nick + " #" + Channel + " :Cannot join channel, you must be invited (+i)\r\n")

//:tngnet.nl.quakenet.org 471 youssef_ #RE :Cannot join channel, Channel is full (+l)
#define RPL_JOIN_LIMIT(Nick, Channel)                  (std::string(":localhost 471 ") + Nick + " #" + Channel + " :Cannot join channel, Channel is full (+l)\r\n")

//:hostsailor.ro.quakenet.org 475 youssef #re :Cannot join channel, you need the correct key (+k)
#define RPL_JOIN_BAD_PASS(Nick, Channel)                  (std::string(":localhost 475 ") + Nick + " #" + Channel + " :Cannot join channel, you need the correct key (+k)\r\n")


/*
:test!youssef@localhost PRIVMSG #Channel :salut
:irc.rizon.club 404 monkey #ok :Cannot send to channel
*/

#define RPL_PRIVMSG_CHANNEL(Nick, User , buffer)              (std::string(":") + Nick + "!" + User + "@localhost " + buffer + "\r\n")
#define RPL_PRIVMSG_NO_CHANNEL(Nick, Channel)                 (std::string(":localhost 404 ") + Nick + " #" + Channel + " :Cannot send to channel\r\n")  


/*
:monkey!~monkey@lfbn-nic-1-511-105.w90-116.abo.wanadoo.fr PRIVMSG nick :test
:adrift.sg.quakenet.org 401 Nick pseudo :No such nick
*/


#define RPL_PRIVMSG_CLIENT(Nick, User , buffer)              (std::string(":") + Nick + "!~" + User + "@localhost " + buffer + "\r\n")
#define RPL_PRIVMSG_NO_CLIENT(Nick, Client)                  (std::string(":localhost 401 ") + Nick + " " + Client + " :No such nick\r\n")




/*MODE*/

// :nicks!~youssef@66.225.88.79.rev.sfr.net MODE #re +i
#define RPL_MODE_I(Nick, User, Channel , Signe)                 (std::string(":") + Nick + "!~" + User + "@localhost MODE #" + Channel +" " + Signe +"i \r\n")    
#define RPL_MODE_T(Nick, User, Channel , Signe)                 (std::string(":") + Nick + "!~" + User + "@localhost MODE #" + Channel +" " + Signe +"t \r\n") 

//:youssef_!~youssef@79.88.225.66 MODE #kks +k pass
#define RPL_MODE_K(Nick, User, Channel , Signe, arg)                 (std::string(":") + Nick + "!~" + User + "@localhost MODE #" + Channel +" " + Signe +"k " + arg +"\r\n") 

//:youssef!~youssef@79.88.225.66 MODE #re -o t1
#define RPL_MODE_O(Nick, User, Channel , Signe, arg)                 (std::string(":") + Nick + "!~" + User + "@localhost MODE #" + Channel +" " + Signe +"o " + arg +"\r\n") 

//:youssef!~youssef@79.88.225.66 MODE #re +l 100
#define RPL_MODE_L(Nick, User, Channel , Signe, arg)                 (std::string(":") + Nick + "!~" + User + "@localhost MODE #" + Channel +" " + Signe +"l " + arg +"\r\n") 

//:localhost 464  :Password incorrect.
#define RPL_WRONG_PASS()                 (":localhost 464  :Password incorrect.\r\n") 

//::youssef_!~youssef@79.88.225.66 QUIT :Quit: leaving
#define RPL_EXIT(Nick, User)                 (std::string(":") + Nick + "!~" + User + "@localhost QUIT :Quit: leaving\r\n");

//:127.0.0.1 PONG 127.0.0.1 :127.0.0.1

#define RPL_PONG()                 (":127.0.0.1 PONG 127.0.0.1 :127.0.0.1\r\n");


//:youssef!~youssef@66.225.88.79.rev.sfr.net KICK #re youssef_ :youssef
#define RPL_KICK(Nick, User, msg)                 (std::string(":") + Nick + "!~" + User + " "+ msg +"\r\n");


//:adrift.sg.quakenet.org 401 youssef testpote :No such nick
//send     //:adrift.sg.quakenet.org 341 youssef tes1 #re 
//rev      //:youssef!~youssef@66.225.88.79.rev.sfr.net INVITE tes1 #re

#define RPL_INVITE_NO(Nick, Invite)                        (std::string(":127.0.0.1 401 ") + Nick + " " + Invite + " :No such nick\r\n");
#define RPL_INVITE_SEND(Nick, Invite, Channel)             (std::string(":127.0.0.1 341 ") + Nick + " " + Invite + " #"+ Channel + "\r\n")
#define RPL_INVITE_RECV(Nick, User, Invite ,Channel)       (std::string(":") + Nick + "!~" + User + "@localhost INVITE " + Invite + " #"+ Channel +"\r\n")


//:tngnet.nl.quakenet.org 442 tes2 #res :You're not on that channel
//:tngnet.nl.quakenet.org 482 tes2 #res :You're not channel operator
//:tes2!~youssef@79.88.225.66 TOPIC #res :lol


#define RPL_TOPIC_NO_CHANNEL(Nick, Channel)                (std::string(":127.0.0.1 442 ") + Nick + " #" + Channel +" :You're not on that channel\r\n")
#define RPL_TOPIC_NO_OP(Nick, Channel)                     (std::string(":127.0.0.1 482 ") + Nick + " #" + Channel +" :You're not channel operator\r\n")
#define RPL_TOPIC(Nick, User, Topic ,Channel)              (std::string(":") + Nick + "!~" + User + "@localhost TOPIC #" + Channel + " :"+ Topic +"\r\n")             

/*part*/
//:tes2!~youssef@66.225.88.79.rev.sfr.net PART #re
#define RPL_PART(Nick, User, buffer)              (std::string(":") + Nick + "!~" + User + "@localhost "+ buffer +"\r\n")             


/*Nick*/
//:irc.uworld.se 433 monkey mon :Nickname is already in use.
//:monkey!~monkey@Rizon-5467865.w90-116.abo.wanadoo.fr NICK :mon

#define RPL_NICK_EXIST(Nick, New_nick)          (std::string(":127.0.0.1 433 ") + Nick + " " + New_nick +" :Nickname is already in use.\r\n")
#define RPL_NICK(Nick, User, New_nick)          (std::string(":") + Nick + "!~" + User + "@localhost NICK :" + New_nick +"\r\n")             



#endif
