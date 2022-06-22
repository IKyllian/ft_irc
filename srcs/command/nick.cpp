/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 13:25:54 by kzennoun          #+#    #+#             */
/*   Updated: 2022/06/22 14:10:46 by kzennoun         ###   ########lyon.fr   */
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
		answer = ":";
		answer += client.get_fullidentity();
		answer += " ";
		answer += print_numerics(431, client, client);
		answer += "\r\n";
		send_message(client, answer);
		return;
	}

	std::string new_nick = message.get_tab_parameter()[0];

	if (!_nick_available(new_nick))
	{
		answer = ":";
		answer += client.get_fullidentity();
		answer += " ";		
		answer += print_numerics(433, client, client);
		answer += "\r\n";
		send_message(client, answer);
	}
	else if (!_nick_isvalid(new_nick))
	{
		answer = ":";
		answer += client.get_fullidentity();
		answer += " ";
		answer += print_numerics(432, client, client);
		answer += "\r\n";
		send_message(client, answer);
	}
	else 
	{
	//	send_message(client, ":" + client.get_fullidentity() + " NICK " + message.get_tab_parameter()[0]);

		for (unsigned long i = 0; i < get_clients().size(); i++)
		{
			send_message(*(get_clients()[i]), ":" + client.get_fullidentity() + " NICK " + message.get_tab_parameter()[0]);
		}
		client.set_nickname(new_nick);

		
		if (client.get_registered() && ( !get_using_password() ||  client.get_authentified() ))
		{
			if (client.get_logged() == false)
			{
				answer = build_response(001, client, client);
				send_message(client, answer);
			}
			client.set_logged(true);
		}
	}
}
