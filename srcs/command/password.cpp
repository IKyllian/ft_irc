/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   password.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 17:05:19 by kzennoun          #+#    #+#             */
/*   Updated: 2022/06/13 16:24:10 by kzennoun         ###   ########lyon.fr   */
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
		answer = ":";
		answer += client.get_fullidentity();
		answer += " ";
		answer += print_numerics(461, client, client, NULL, &message);
		send_message(client, answer);		
	}
	else if (client.get_authentified())
	{
		answer = ":";
		answer += client.get_fullidentity();
		answer += " ";
		answer += print_numerics(462, client, client);
		send_message(client, answer);
	}
	else
	{
		client.set_authentified(true);
		if (client.get_hasnick() && client.get_registered())
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