/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rozhou <rozhou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 14:50:32 by kzennoun          #+#    #+#             */
/*   Updated: 2022/06/14 12:39:07 by rozhou           ###   ########.fr       */
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
		answer = ":";
		answer += client.get_fullidentity();
		answer += " ";
		answer += print_numerics(461, client, client, NULL, &message);
		send_message(client, answer);
	}
	else if (!(client.get_realname() == ""))
	{
		answer = ":";
		answer += client.get_fullidentity();
		answer += " ";
		answer += print_numerics(462, client, client);
		send_message(client, answer);
	}
	else 
	{
		client.set_username(message.get_tab_parameter()[0]);
		answer = "";
		for (unsigned long i = 3; i < message.get_tab_parameter().size() ; i++)
		{
			answer += message.get_tab_parameter()[i];
		}
		client.set_realname(answer);
		answer = "";
		client.set_registered(true);

		if (client.get_hasnick() && ( !get_using_password() ||  client.get_authentified() ))
		{
			client.set_logged(true);
			answer = ":";
			answer += client.get_fullidentity();
			answer += " ";
			answer += print_numerics(001, client, client);
			send_message(client, answer);
		}
	}
}
