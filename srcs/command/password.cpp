/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   password.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 17:05:19 by kzennoun          #+#    #+#             */
/*   Updated: 2022/06/10 14:03:40 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"
#include "../../includes/Message.hpp"
#include "../../includes/Client.hpp"
#include "../../includes/ft_irc.hpp"

void Server::command_PASSWORD(Client &client, Message &message)
{
	std::string answer;

	if (message.get_tab_parameter().size() == 0)
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
	else if (client.get_authentified())
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
		client.set_authentified(true);

		//check if NICK + USER + PASSWORD valid
		if (client.get_hasnick() && client.get_registered())
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

      Command: PASS
   Parameters: <password>

   The PASS command is used to set a 'connection password'.  The
   optional password can and MUST be set before any attempt to register
   the connection is made.  Currently this requires that user send a
   PASS command before sending the NICK/USER combination.

   Numeric Replies:

           ERR_NEEDMOREPARAMS              ERR_ALREADYREGISTRED

   Example:

           PASS secretpasswordhere

*/