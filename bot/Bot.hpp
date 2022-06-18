/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 12:04:18 by kzennoun          #+#    #+#             */
/*   Updated: 2022/06/18 15:57:14 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_HPP
#define BOT_HPP

#include "Message.hpp"

#include <iostream>
#include <sys/socket.h>
#include <vector>
#include <unistd.h>

class Bot
{
	public:

	Bot();

	void set_serverFD(int serverFD);
	void set_running(bool running);
	void set_logged(bool logged);
	void set_nickname(std::string nick);

	bool get_running() const;
	int get_serverFD() const;
	std::string	get_buffer() const;
	bool get_logged() const;
	std::string get_nickname() const;

	void append_buffer(char* buffer);
	std::string extract_command(size_t pos);
	bool do_parsing(std::string message);
	bool send_message(std::string message);
	int handle_incoming_message();
	Message *ft_create_message(std::string str);
	void do_command(Message &msg);
	std::vector<std::string> ft_split_message(std::string str);
	void ft_split_parameter(Message &msg);
	protected:

	private:

	bool		_running;
	int			_serverFD;
	std::string	_buffer;
	bool		_logged;
	std::string _nickname;

	

};

#endif