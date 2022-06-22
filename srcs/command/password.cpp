#include "../../includes/Server.hpp"

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