
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

Bot::Bot(): _running(true), _serverFD(-1), _buffer(""), _logged(false), _nickname("") {}

int Bot::get_serverFD() const{ return (_serverFD); }
std::string	Bot::get_buffer() const { return (_buffer); }
bool Bot::get_running() const { return (_running); } 
bool Bot::get_logged() const { return (_logged); }
std::string Bot::get_nickname() const { return (_nickname); }

void Bot::set_serverFD(int serverFD)
{
	_serverFD = serverFD;
}

void Bot::set_running(bool running)
{
	_running = running;
}

void Bot::set_logged(bool logged)
{
	_logged = logged;
}

void Bot::set_nickname(std::string nick)
{
	_nickname = nick;
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

	std::cout << "\033[1;31msend: \033[0m";
	//std::cout << "sending: ";
	std::cout << buffer;

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

 	usleep(500000);
	do
	{
		memset(&buffer, 0, sizeof(buffer));
		ret = recv(_serverFD, buffer, sizeof(buffer), 0);
		append_buffer(buffer);
	}while(ret > 0);
	pos = get_buffer().rfind("\r\n");
	if (pos == std::string::npos || pos >= get_buffer().length())
	{
		// std::cout << " command incomplete, storing: " << std::endl 
		// 		<< get_buffer() << std::endl;
		return ret;
	}
	message = extract_command(pos);	
	std::cout << "\033[1;32mrecv: \033[0m" << message;
	
	do_parsing(message);
	return ret;
}



void Bot::ft_split_parameter(Message &msg)
{
    size_t position = 0;
    size_t startpoint = 0;
    int nb = 0;

    while (position != std::string::npos)
    {
        position = msg.get_parameter().find(" ", position);
        if (position - startpoint > 0)
        {
            msg.get_tab_parameter().push_back(msg.get_parameter().substr(startpoint, position - startpoint));
            nb++;
        }
        if (position != std::string::npos)
        {
            position++;
            startpoint = position;
        }
    }
    msg.set_nb_parameter(nb);
    // std::cout << "Split function " << msg.get_nb_parameter() << std::endl;

    return ;
}

Message *Bot::ft_create_message(std::string str)
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


void Bot::do_command(Message &msg)
{
	std::string answer;

	// std::cout << "msg.get_command(): " << msg.get_command() << std::endl;
	// // std::cout << "size " << msg.get_tab_parameter().size() << std::endl;
	// for (unsigned long i = 0; i < msg.get_tab_parameter().size(); i++)
	// {
	// 	std::cout << "msg tab[" << i << "]: " << msg.get_tab_parameter()[i] << std::endl;
	// }
	// std::cout << "msg.get_prefix(): " << msg.get_prefix() << std::endl;
	// std::cout << "msg.get_target_nickname(): " << msg.get_target_nickname() << std::endl;
	//msg tab[1] -> 

	if (msg.get_command() == "433" || msg.get_command() == "431"
	|| msg.get_command() == "432" || msg.get_command() == "484")
	{
		std::cout << "Unable to set nickname, aborting" << std::endl;
		set_running(false);
		return;
	}
	else if (msg.get_command() == "001")
	{
		std::cout << "Received RPL Welcome" << std::endl;
		set_logged(true);
	}
	else if (msg.get_command() == "353")
	{
		answer = "";
		answer += "PRIVMSG ";
		answer += msg.get_tab_parameter()[1];
		answer += " Welcome ";
		answer += msg.get_target_nickname();
		send_message(answer);
	}
	else if (msg.get_command() == "PRIVMSG")
	{
		if (msg.get_tab_parameter()[1] == ":!join")
		{
			//msg.get_tab_parameter()[2]
			answer = "";
			answer += "JOIN ";
			answer += msg.get_tab_parameter()[2];
			send_message(answer);
		}
		else if (msg.get_tab_parameter()[1] == ":!selfdestruct")
		{
			set_running(false);
			return;
		}
	}
	else if (msg.get_command() == "PART")
	{
		answer = "";
		answer += "PRIVMSG ";
		answer += msg.get_tab_parameter()[0];
		answer += " Goodbye ";
		answer += msg.get_target_nickname();
		send_message(answer);
	}
	else if (msg.get_command() == "KICK")
	{
		answer = "";
		answer += "PRIVMSG ";
		answer += msg.get_tab_parameter()[0];
		answer += " CHEH ";	
		answer += msg.get_tab_parameter()[1];
		send_message(answer);
	}
}

std::vector<std::string> Bot::ft_split_message(std::string str)
{
    std::vector<std::string> msg_list;
    size_t old_position;
    size_t position = 0;
    size_t startpoint = 0;
    std::string tmp;

    while (position != std::string::npos)
    {
        old_position = position;
        position = str.find("\r\n", position);
        if (position - startpoint > 0)
        {
            tmp = str.substr(startpoint, position);
            std::string tmp = str.substr(startpoint, position);
            // for (unsigned long i = 0; i < tmp.length(); i++)
            // {
            // 	std::cout << "11111 i: " << i << "tmp[i]: " << tmp[i] << "| (int): " << (int) tmp[i] << std::endl;
            // }
            if (position == std::string::npos)
            {
                if (str.substr(startpoint, position).size() <= 0)
                    break;
                // for (unsigned long i = 0; i < tmp.length(); i++)
                // {
                // 	std::cout << "22222i: " << i << "tmp[i]: " << tmp[i] << "| (int): " << (int) tmp[i] << std::endl;
                // }    
                msg_list.push_back(str.substr(startpoint, position));
                break;
            }
            msg_list.push_back(str.substr(startpoint, position - startpoint));
        }
        if (position != std::string::npos)
        {
            position += 2;
            startpoint = position;
        }
    }
    return (msg_list);
}

bool Bot::do_parsing(std::string message)
{
	std::vector<Message*> msg;
	std::vector<std::string> msg_list;
	(void) message;
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
	return true;
}