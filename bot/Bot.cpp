
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 12:17:38 by kzennoun          #+#    #+#             */
/*   Updated: 2022/06/17 16:18:31 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

int Bot::get_serverFD() const{ return (_serverFD); }
std::string	Bot::get_buffer() const { return (_buffer); }
bool Bot::get_running() const { return (_running); } 

void Bot::set_serverFD(int serverFD)
{
	_serverFD = serverFD;
}

void Bot::set_running(bool running)
{
	_running = running;
}


void Bot::append_buffer(char* buffer) {
	_buffer += buffer;
}

std::string Bot::extract_command(size_t pos) {
	std::string command;

	command = _buffer.substr(0, pos + 2);
	_buffer = _buffer.substr(pos + 2, - 1);

	return command;
}

bool Bot::send_message(std::string message)
{
	int					ret;
	unsigned long 		i;
	char				buffer[65535];
	size_t				len;

	memset(&buffer, 0, sizeof(buffer));
	for (i = 0; i < message.length(); i++)
	{
		buffer[i] = message[i];
	}
	buffer[i] = '\r';
	buffer[i + 1] = '\n';
	buffer[i + 2] = '\0';
	len = i + 2;

	std::cout << "sending: ";
	std::cout << buffer << std::endl;

	ret = send(_serverFD, buffer, len, 0);
	if (ret < 0)
	{
		perror("  send() failed");
		return false;
	}

	return true;
}


int Bot::handle_incoming_message()
{
	int				ret;
	size_t			pos;
	char			buffer[65535];
	std::string		message;


	do
	{
		memset(&buffer, 0, sizeof(buffer));
		ret = recv(_serverFD, buffer, sizeof(buffer), 0);
		append_buffer(buffer);
	}while(ret > 0);

	pos = get_buffer().rfind("\r\n");
	if (pos == std::string::npos || pos >= get_buffer().length())
	{
		std::cout << " command incomplete, storing: " << std::endl 
				<< get_buffer() << std::endl
				<< "--------------" << std::endl;
		return ret;
	}
	
	message = extract_command(pos);
	
	std::cout << "received: " << message;
	
	do_parsing(message);
	return ret;
}


Message *Bot::ft_create_message(std::string str) const
{
    Message *msg = new Message;
    std::string delimiter = " ";
    std::string str_to_pass;
    size_t position = 0;
    size_t startpoint = 0;
    
    if (str[0] == ':')
    {
        position = str.find(' ', position);
        str_to_pass = str.substr(startpoint, position - startpoint);
        msg->set_prefix(str_to_pass);
        position++;
        startpoint = position;
    }
    position = str.find(' ', position);
    str_to_pass = str.substr(startpoint, position - startpoint);
    msg->set_command(str_to_pass);
    msg->set_nb_parameter(0);
    if (position != std::string::npos)
    {
        position++;
        startpoint = position;
        position = str.length();
        str_to_pass = str.substr(startpoint, position - startpoint);
 //       std::cout << str_to_pass << std::endl;
        msg->set_parameter(str_to_pass);
        position++;
        startpoint = position;
        ft_split_parameter(*msg);
    }
    return (msg);
}


void Bot::do_command(Message &msg) const
{

	std::cout << "msg.get_command(): " << msg.get_command() << std::endl;
	for (unsigned long i = 0; i < msg.get_tab_parameter().size(); i++)
	{
		std::cout << "msg tab[" << i << "]: " << msg.get_tab_parameter()[i] << std::endl;
	}


	//if ERR NICK/USER/PASS ?
	//if 001 ?



// std::cout << "###inside do_command: msg.get_command() = " << msg.get_command() << std::endl;
// 	if (msg.get_command() == "CAP")
// 	{

// 	}
// 	else if (msg.get_command() == "AUTHENTICATE")
// 	{
// 		//  do_AUTHENTICATE();
// 	}
// 	else if (msg.get_command() == "PASS")
// 	{
// 		server.command_PASSWORD(msg.get_sender(), msg);
// 	}
// 	else if (msg.get_command() == "NICK")
// 	{
// 		server.command_NICK(msg.get_sender(), msg);
// 	}
// 	else if (msg.get_command() == "USER")
// 	{
// 		server.command_USER(msg.get_sender(), msg);
// 	}
// 	else if (msg.get_command() == "PING")
// 	{
// 		send_message(*sender,  server.build_response(*sender, "PONG " + sender->get_hostname() + " :" + msg.get_parameter()));
// 	}
// 	else if (msg.get_command() == "PONG")
// 	{
// 		//  do_PONG();
// 	}
// 	else if (msg.get_command() == "OPER")
// 	{
// 		//  do_OPER();
// 	}
// 	else if (msg.get_command() == "QUIT")
// 	{
// 		server.command_QUIT(msg.get_sender(), msg);
// 	}
// 	else if (msg.get_command() == "ERROR")
// 	{
// 		//  do_ERROR();
// 	}
// 	else if (msg.get_command() == "JOIN")
// 	{
// 		server.command_JOIN(sender, msg, server);
// 		for (size_t i = 0; i < sender->get_channel().size(); i++)
//         	std::cout << "channel names = " << sender->get_channel()[i]->get_name() << std::endl;
// 	}
// 	else if (msg.get_command() == "PART")
// 	{
// 		server.command_PART(sender, msg);
// 	}
// 	else if (msg.get_command() == "TOPIC")
// 	{
// 		server.command_TOPIC(sender, msg);
// 	}
// 	else if (msg.get_command() == "NAMES")
// 	{
// 		server.command_NAMES(msg);
// 	}
// 	else if (msg.get_command() == "LIST")
// 	{
// 		server.command_LIST(msg);
// 	}
// 	else if (msg.get_command() == "INVITE")
// 	{
// 		server.command_INVITE(sender, msg);
// 	}
// 	else if (msg.get_command() == "KICK")
// 	{
// 		server.command_KICK(sender, msg);
// 	}
// 	else if (msg.get_command() == "MOTD")
// 	{
// 		//  do_MOTD();
// 	}
// 	else if (msg.get_command() == "VERSION")
// 	{
// 		//  do_VERSION();
// 	}
// 	else if (msg.get_command() == "ADMIN")
// 	{
// 		//  do_ADMIN();
// 	}
// 	else if (msg.get_command() == "CONNECT")
// 	{
// 		//  do_CONNECT();
// 	}
// 	else if (msg.get_command() == "LUSERS")
// 	{
// 		//  do_LUSERS();
// 	}
// 	else if (msg.get_command() == "TIME")
// 	{
// 		//  do_TIME();
// 	}
// 	else if (msg.get_command() == "STATS")
// 	{
// 		//  do_STATS();
// 	}
// 	else if (msg.get_command() == "HELP")
// 	{
// 		// PAS FAIT
// 	}
// 	else if (msg.get_command() == "INFO")
// 	{
// 		//  do_INFO();
// 	}
// 	else if (msg.get_command() == "MODE")
// 	{
// 		if (msg.get_tab_parameter()[0].size() > 0 && (msg.get_tab_parameter()[0][0] == '#' || msg.get_tab_parameter()[0][0] == '@'))
// 			server.command_MODE_CHAN(sender, msg);
// 		else
// 			server.command_MODE_USER(sender, msg);
// 	}
// 	else if (msg.get_command() == "PRIVMSG")
// 	{
// 		server.command_PRIVMSG(*sender, msg, server, 0);
// 	}
// 	else if (msg.get_command() == "NOTICE")
// 	{
// 		server.command_PRIVMSG(*sender, msg, server, 1);
// 	}
// 	else if (msg.get_command() == "WHO")
// 	{
// 		server.command_WHO(*sender, msg);
// 	}
// 	else if (msg.get_command() == "WHOIS")
// 	{
// 		server.command_WHOIS(*sender, msg);
// 	}
// 	else if (msg.get_command() == "WHOWAS")
// 	{
// 		//  do_WHOWAS();
// 	}
// 	else if (msg.get_command() == "KILL")
// 	{
// 		//  do_KILL();
// 	}
// 	else if (msg.get_command() == "RESTART")
// 	{
// 		//  do_RESTART();
// 	}
// 	else if (msg.get_command() == "SQUIT")
// 	{
// 		//  do_SQUIT();
// 	}
// 	else if (msg.get_command() == "AWAY")
// 	{
// 		server.command_AWAY(*sender, msg);
// 	}
// 	else if (msg.get_command() == "LINKS")
// 	{
// 		//  do_LINKS();
// 	}
// 	else if (msg.get_command() == "USERHOST")
// 	{
// 		//  do_USERHOST();
// 	}
// 	else if (msg.get_command() == "WALLOPS")
// 	{
// 		//  do_WALLOPS();
// 	}
// 	else
// 	{
// 		std::cout << "Command not found" << std::endl;
// 	}
}



bool Bot::do_parsing(std::string message) const
{
	std::vector<Message*> msg;
	std::vector<std::string> msg_list;

	msg_list = ft_split_message(message);
	for (size_t i = 0; i < msg_list.size(); i++)
	{
		msg.push_back(ft_create_message(msg_list[i]));
	}
//	std::cout << "msg size = " << msg.size() << std::endl;
	for (size_t i = 0; i < msg.size(); i++)
	{
		do_command(*msg[i]);
	}
	for (size_t i = 0; i < msg.size(); i++)
		delete msg[i];
	return;
}