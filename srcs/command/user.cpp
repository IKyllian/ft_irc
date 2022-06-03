/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 14:50:32 by kzennoun          #+#    #+#             */
/*   Updated: 2022/06/03 15:42:23 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"
#include "../../includes/ft_irc.hpp"

void Server::command_USER(Client &client, Message &message)
{
        std::string answer;
        
	if (message.get_tab_parameter().size() < 4)
	{
		//        461    ERR_NEEDMOREPARAMS
        //       "<command> :Not enough parameters"

        //  - Returned by the server by numerous commands to
        //    indicate to the client that it didn't supply enough
        //    parameters.
	}
	else if (client.get_realname() == "")
	{
		//already logged

		//        462    ERR_ALREADYREGISTRED
        //       ":Unauthorized command (already registered)"

        //  - Returned by the server to any link which tries to
        //    change part of the registered details (such as
        //    password or user details from second USER message).
	}
        else 
        {
                //do stuff
        }
}

/*

      Command: USER
   Parameters: <user> <mode> <unused> <realname>

   The USER command is used at the beginning of connection to specify
   the username, hostname and realname of a new user.

   The <mode> parameter should be a numeric, and can be used to
   automatically set user modes when registering with the server.  This
   parameter is a bitmask, with only 2 bits having any signification: if
   the bit 2 is set, the user mode 'w' will be set and if the bit 3 is
   set, the user mode 'i' will be set.  (See Section 3.1.5 "User
   Modes").

   The <realname> may contain space characters.

   Numeric Replies:

           ERR_NEEDMOREPARAMS              ERR_ALREADYREGISTRED

   Example:

   USER guest 0 * :Ronnie Reagan   ; User registering themselves with a
                                   username of "guest" and real name
                                   "Ronnie Reagan".

   USER guest 8 * :Ronnie Reagan   ; User registering themselves with a
                                   username of "guest" and real name
                                   "Ronnie Reagan", and asking to be set
                                   invisible.
*/