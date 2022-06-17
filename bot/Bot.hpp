/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 12:04:18 by kzennoun          #+#    #+#             */
/*   Updated: 2022/06/17 18:14:12 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_HPP
#define BOT_HPP

#include "Message.hpp"

#include <iostream>
#include <sys/socket.h>
#include <vector>

class Bot
{
	public:

	void set_serverFD(int serverFD);
	void set_running(bool running);

	bool get_running() const;
	int get_serverFD() const;
	std::string	get_buffer() const;

	void append_buffer(char* buffer);
	std::string extract_command(size_t pos);
	bool do_parsing(std::string message) const;
	bool send_message(std::string message);
	int handle_incoming_message();
	Message *ft_create_message(std::string str) const;
	void Bot::do_command(Message &msg) const;

	protected:

	private:

	std::string	_buffer;
	int			_serverFD;
	bool		_running;

	

};

#endif