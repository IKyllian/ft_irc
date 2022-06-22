#include "../includes/ft_irc.hpp"
#include "../includes/Server.hpp"


static void do_command(Server &server, Client *sender, Message &msg)
{
	if (!sender->get_logged() && !( msg.get_command() == "NICK" || msg.get_command() == "USER" || msg.get_command() == "PASS" ) )
		return;

	if (msg.get_command() == "PASS")
	{
		server.command_PASSWORD(msg.get_sender(), msg);
	}
	else if (msg.get_command() == "NICK")
	{
		server.command_NICK(msg.get_sender(), msg);
	}
	else if (msg.get_command() == "USER")
	{
		server.command_USER(msg.get_sender(), msg);
	}
	else if (msg.get_command() == "PING")
	{
		send_message(*sender,  server.build_response(*sender, "PONG " + sender->get_hostname() + " :" + msg.get_parameter()));
	}
	else if (msg.get_command() == "QUIT")
	{
		server.command_QUIT(msg.get_sender(), msg);
	}
	else if (msg.get_command() == "JOIN")
	{
		server.command_JOIN(sender, msg, server);
	}
	else if (msg.get_command() == "PART")
	{
		server.command_PART(sender, msg);
	}
	else if (msg.get_command() == "TOPIC")
	{
		server.command_TOPIC(sender, msg);
	}
	else if (msg.get_command() == "NAMES")
	{
		server.command_NAMES(msg);
	}
	else if (msg.get_command() == "LIST")
	{
		server.command_LIST(msg);
	}
	else if (msg.get_command() == "INVITE")
	{
		server.command_INVITE(sender, msg);
	}
	else if (msg.get_command() == "KICK")
	{
		server.command_KICK(sender, msg);
	}
	else if (msg.get_command() == "MODE")
	{
		if (msg.get_tab_parameter()[0].size() > 0 && (msg.get_tab_parameter()[0][0] == '#' || msg.get_tab_parameter()[0][0] == '@'))
			server.command_MODE_CHAN(sender, msg);
		else
			server.command_MODE_USER(sender, msg, server);
	}
	else if (msg.get_command() == "PRIVMSG")
	{
		server.command_PRIVMSG(*sender, msg, server, 0);
	}
	else if (msg.get_command() == "NOTICE")
	{
		server.command_PRIVMSG(*sender, msg, server, 1);
	}
	else if (msg.get_command() == "WHO")
	{
		server.command_WHO(*sender, msg);
	}
	else if (msg.get_command() == "WHOIS")
	{
		server.command_WHOIS(*sender, msg);
	}
	else if (msg.get_command() == "AWAY")
	{
		server.command_AWAY(*sender, msg);
	}
	else
	{
		std::cout << "Command not found" << std::endl;
	}
}

void do_parsing(Server &server, Client *sender, std::string message)
{
	std::vector<Message*> msg;
	std::vector<std::string> msg_list;

	msg_list = ft_split_message(message);
	for (size_t i = 0; i < msg_list.size(); i++)
	{
		msg.push_back(ft_create_message(msg_list[i]));
	}
	for (size_t i = 0; i < msg.size(); i++)
	{
		msg[i]->set_sender(sender);
		msg[i]->set_receiver(sender);
		do_command(server, sender, *msg[i]);
	}
	for (size_t i = 0; i < msg.size(); i++)
		delete msg[i];
	return;
}