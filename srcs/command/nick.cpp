/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 13:25:54 by kzennoun          #+#    #+#             */
/*   Updated: 2022/06/10 16:26:52 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"
#include "../../includes/ft_irc.hpp"

void Server::command_NICK(Client &client, Message &message) {

	std::string answer;

	// TODO rajouter password check
	// if (!client.get_authentified())
	// {
	// 	return;
	// }

	if (message.get_tab_parameter().size() == 0)
	{
		// if (client.get_hasnick())
		// {
			answer = ":";
			answer += client.get_fullidentity();
			answer += " ";
			answer += print_numerics(431, client, client);
			send_message(client, answer);
		// }
		// else
		// {
		// 	answer = ":";
		// 	answer += this->get_hostname();
		// 	answer += " 431 * ";
		// 	answer += ":No nickname given";
		// 	send_message(client, answer);
		// }
		return;
	}

	std::string new_nick = message.get_tab_parameter()[0];

	if (!_nick_available(new_nick))
	{
//std::cout << ">>>nick not available" << std::endl;
			// if (client.get_hasnick())
			// {
				answer = ":";
				answer += client.get_fullidentity();
				answer += " ";		
				answer += print_numerics(433, client, client);
			// }
			// else
			// {
			// 	answer = ":";
			// 	answer += this->get_hostname();
			// 	answer += " 433 * :Nickname is already in use";
			// }

			send_message(client, answer);
	}
	else if (!_nick_isvalid(new_nick))
	{
//std::cout << ">>>nick invalid" << std::endl;

		// if (client.get_hasnick())
		// {
			answer = ":";
			answer += client.get_fullidentity();
			answer += " ";
			answer += print_numerics(432, client, client);
		// }
		// else
		// {
		// 	answer = ":";
		// 	answer += this->get_hostname();
		// 	answer += " 432 * :Erroneous nickname";
		// }
			send_message(client, answer);
	}
	else if (client.get_user_modes().find('r') != std::string::npos)
	{
//std::cout << ">>>user restricted" << std::endl;

		// if (client.get_hasnick())
		// {
			answer = ":";
			answer += client.get_fullidentity();
			answer += " ";
			answer += print_numerics(484, client, client);
		// }
		// else
		// {
		// 	answer = ":";
		// 	answer += this->get_hostname();
		// 	answer += " 484 * :Your connection is restricted!";
		// }
			send_message(client, answer);
	}
	else 
	{
//std::cout << ">>>changing nickname" << std::endl;
		client.set_nickname(new_nick);

		//check if NICK + USER + PASSWORD valid
std::cout << std::boolalpha << std::endl
<< " register: " << client.get_registered() << std::endl
<< " serv using pw: " << get_using_password() << std::endl
<< " client gave pw: " << client.get_authentified() << std::endl
<< " if result: " << (client.get_registered() && ( !get_using_password() ||  client.get_authentified() ))
<< std::endl;
		if (client.get_registered() && ( !get_using_password() ||  client.get_authentified() ))
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

//test response
// std::cout << "************" << std::endl;
// std::cout << "NICK client fd = " << client.get_fd() << std::endl;
// 		send_message(client, ":irc.example.com 001 abc :Welcome to the Internet Relay Network abc!abc@polaris.cs.uchicago.edu");


	    //    437    ERR_UNAVAILRESOURCE
        //       "<nick/channel> :Nick/channel is temporarily unavailable"
        //  - Returned by a server to a user trying to join a channel
        //    currently blocked by the channel delay mechanism.
        //  - Returned by a server to a user trying to change nickname
        //    when the desired nickname is blocked by the nick delay
        //    mechanism.

		//        436    ERR_NICKCOLLISION
        //       "<nick> :Nickname collision KILL from <user>@<host>"
        //  - Returned by a server to a client when it detects a
        //    nickname collision (registered of a NICK that
        //    already exists by another server).

}
