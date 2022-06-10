#include "../includes/ft_irc.hpp"
#include "../includes/Command.hpp"
#include "../includes/Server.hpp"


static void do_command(Server &server, Client &sender, Message &msg)
{
	/*(void)server;
	(void)receiver;*/
std::cout << "###inside do_command: msg.get_command() = " << msg.get_command() << std::endl;
	if (msg.get_command() == "CAP")
	{
		//  do_CAP();
	}
	else if (msg.get_command() == "AUTHENTICATE")
	{
		//  do_AUTHENTICATE();
	}
	else if (msg.get_command() == "PASS")
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
		//  do_PING();
	}
	else if (msg.get_command() == "PONG")
	{
		//  do_PONG();
	}
	else if (msg.get_command() == "OPER")
	{
		//  do_OPER();
	}
	else if (msg.get_command() == "QUIT")
	{
		//  do_QUIT();
	}
	else if (msg.get_command() == "ERROR")
	{
		//  do_ERROR();
	}
	else if (msg.get_command() == "JOIN")
	{
		server.command_JOIN(&(msg.get_sender()), msg);
	}
	else if (msg.get_command() == "TOPIC")
	{
		server.command_TOPIC(&(msg.get_sender()), msg);
	}
	else if (msg.get_command() == "NAMES")
	{
		//  do_NAMES();
	}
	else if (msg.get_command() == "LIST")
	{
		//  do_LIST();
	}
	else if (msg.get_command() == "INVITE")
	{
		server.command_INVITE(&(msg.get_sender()), msg);
	}
	else if (msg.get_command() == "KICK")
	{
		server.command_KICK(&(msg.get_sender()), msg);
	}
	else if (msg.get_command() == "MOTD")
	{
		//  do_MOTD();
	}
	else if (msg.get_command() == "VERSION")
	{
		//  do_VERSION();
	}
	else if (msg.get_command() == "ADMIN")
	{
		//  do_ADMIN();
	}
	else if (msg.get_command() == "CONNECT")
	{
		//  do_CONNECT();
	}
	else if (msg.get_command() == "LUSERS")
	{
		//  do_LUSERS();
	}
	else if (msg.get_command() == "TIME")
	{
		//  do_TIME();
	}
	else if (msg.get_command() == "STATS")
	{
		//  do_STATS();
	}
	else if (msg.get_command() == "HELP")
	{
		server.command_HELP(sender, msg);
	}
	else if (msg.get_command() == "INFO")
	{
		//  do_INFO();
	}
	else if (msg.get_command() == "MODE")
	{
		//  do_MODE();
	}
	else if (msg.get_command() == "PRIVMSG")
	{
		server.command_PRIVMSG(sender, msg);
	}
	else if (msg.get_command() == "NOTICE")
	{
		//  do_NOTICE();
	}
	else if (msg.get_command() == "WHO")
	{
		server.command_WHO(sender, msg);
	}
	else if (msg.get_command() == "WHOIS")
	{
		server.command_WHOIS(sender, msg);
	}
	else if (msg.get_command() == "WHOWAS")
	{
		//  do_WHOWAS();
	}
	else if (msg.get_command() == "KILL")
	{
		//  do_KILL();
	}
	else if (msg.get_command() == "RESTART")
	{
		//  do_RESTART();
	}
	else if (msg.get_command() == "SQUIT")
	{
		//  do_SQUIT();
	}
	else if (msg.get_command() == "AWAY")
	{
		server.command_AWAY(sender, msg);
	}
	else if (msg.get_command() == "LINKS")
	{
		//  do_LINKS();
	}
	else if (msg.get_command() == "USERHOST")
	{
		//  do_USERHOST();
	}
	else if (msg.get_command() == "WALLOPS")
	{
		//  do_WALLOPS();
	}
	else
	{
		std::cout << "Command not found" << std::endl;
	}
}

void    fill_server_command(Server &server)
{
	Command Away("AWAY", "The AWAY command lets clients indicate that their user is away.");
	Command Help("HELP", "The HELP command is used to return documentation about the commands it implements.");
	Command Invite("INVITE", "The INVITE command is used to invite a user to a channel.");
	Command Join("JOIN", "The JOIN command indicates that the client wants to join the given channel.");
	Command Kick("KICK", "The KICK command can be used to request the forced removal of a user from a channel.");
	Command List("LIST", "The LIST command is used to get a list of channels along with some information about each channel.");
	Command Mode("MODE", "The MODE command is used to set or remove options (or modes) from a given target.");
	Command Names("NAMES", "The NAMES command is used to view the nicknames joined to a channel and their channel membership prefixes.");
	Command Nick("NICK", "he NICK command is used to give the client a nickname or change the previous one.");
	Command Part("PART", "The PART command removes the client from the given channel(s).");
	Command Pass("PASS", "The PASS command is used to set a ‘connection password’.");
	Command Privmsg("PRIVMSG", "The PRIVMSG command is used to send private messages between users, as well as to send messages to channels.");
	Command Topic("TOPIC", "The TOPIC command is used to change or view the topic of the given channel.");
	Command User("USER", "The USER command is used at the beginning of a connection to specify the username and realname of a new user.");
	Command Who("WHO", "The WHO command is used to query a list of users who match the provided mask.");
	Command Whois("WHOIS", "The WHOIS command is used to query information about particular users.");

	server.get_commands().push_back(Away);
	server.get_commands().push_back(Help);
	server.get_commands().push_back(Invite);
	server.get_commands().push_back(Join);
	server.get_commands().push_back(Kick);
	server.get_commands().push_back(List);
	server.get_commands().push_back(Mode);
	server.get_commands().push_back(Names);
	server.get_commands().push_back(Nick);
	server.get_commands().push_back(Part);
	server.get_commands().push_back(Pass);
	server.get_commands().push_back(Privmsg);
	server.get_commands().push_back(Topic);
	server.get_commands().push_back(User);
	server.get_commands().push_back(Who);
	server.get_commands().push_back(Whois);
}

void do_parsing(Server &server, Client &sender, std::string message)
{
	std::vector<Message*> msg;
	std::vector<std::string> msg_list;
	(void) sender;
//std::cout << "###inside do_parsing" << std::endl;
	msg_list = ft_split_message(message);
	for (size_t i = 0; i < msg_list.size(); i++)
	{
		msg.push_back(ft_create_message(msg_list[i]));
	}
	for (size_t i = 0; i < msg.size(); i++)
	{
		msg[i]->set_sender(&sender);
		msg[i]->set_receiver(&sender);
		fill_server_command(server);
		do_command(server, sender, *msg[i]);
		// std::cout << "prefix = " << msg[i]->get_prefix() << std::endl;
		// std::cout << "command = " << msg[i]->get_command() << std::endl;
		// std::cout << "parameter = " << msg[i]->get_parameter() << std::endl;
		// std::cout << "first = " << msg[i]->get_nb_parameter() << std::endl;
		// for (int j = 0; j < msg[i]->get_nb_parameter(); j++)
		//     std::cout << "splited parameter = " << msg[i]->get_tab_parameter()[j] << std::endl;   
		// std::cout << std::endl;
		//fill_message(*msg[i]);

	}
	for (size_t i = 0; i < msg.size(); i++)
		delete msg[i];
	return;
}