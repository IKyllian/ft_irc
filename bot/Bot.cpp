
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

void Bot::set_serverFD(int serverFD)
{
	_serverFD = serverFD;
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
	
	std::cout << "received: " << message << std::endl;

	//do_parsing(server, bot, message);
	return ret;
}