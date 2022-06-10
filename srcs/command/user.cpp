/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 14:50:32 by kzennoun          #+#    #+#             */
/*   Updated: 2022/06/10 16:31:04 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"
#include "../../includes/Message.hpp"
#include "../../includes/Client.hpp"
#include "../../includes/ft_irc.hpp"

void Server::command_USER(Client &client, Message &message)
{
	std::string answer;

	//TODO rajouter password check
	// if (!client.get_authentified())
	// {
	// 	return;
	// }

	if (message.get_tab_parameter().size() < 4)
	{
		//        461    ERR_NEEDMOREPARAMS
		//       "<command> :Not enough parameters"
		//  - Returned by the server by numerous commands to
		//    indicate to the client that it didn't supply enough
		//    parameters.
		answer = ":";
		answer += client.get_fullidentity();
		answer += " ";
		// if (!client.get_hasnick())
		// {
		// 	answer += "* USER :Not enough parameters";
		// }
		// else
		// {
			answer += print_numerics(461, client, client, NULL, &message);
		// }
		send_message(client, answer);
	}
	else if (!(client.get_realname() == ""))
	{
		//        462    ERR_ALREADYREGISTRED
		//       ":Unauthorized command (already registered)"
		//  - Returned by the server to any link which tries to
		//    change part of the registered details (such as
		//    password or user details from second USER message).
		answer = ":";
		answer += client.get_fullidentity();
		answer += " ";
		// if (!client.get_hasnick())
		// {
		// 	answer += "*  :You may not reregister";
		// }
		// else
		// {
			answer += print_numerics(462, client, client);
		// }
		send_message(client, answer);
	}
	else 
	{
		//do stuff
		// [0] username
		client.set_username(message.get_tab_parameter()[0]);
		// TODO mode mask
		// [1] mask
		// [2] unused
		answer = "";
		for (unsigned long i = 3; i < message.get_tab_parameter().size() ; i++)
		{
			answer += message.get_tab_parameter()[i];
		}
		client.set_realname(answer);
		answer = "";
		client.set_registered(true);

std::cout << std::boolalpha 
<< " hasnick: " << client.get_hasnick() << std::endl
<< " serv using pw: " << get_using_password() << std::endl
<< " client gave pw: " << client.get_authentified() << std::endl
<< " if result: " << (client.get_hasnick() && ( !get_using_password() ||  client.get_authentified() ))
<< std::endl;

		//check if NICK + USER + PASSWORD valid
		if (client.get_hasnick() && ( !get_using_password() ||  client.get_authentified() ))
		{
			//RPL WELCOME ?
			client.set_logged(true);
			answer = ":";
			answer += client.get_fullidentity();
			answer += " ";
			answer += print_numerics(001, client, client);
			send_message(client, answer);
		}
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