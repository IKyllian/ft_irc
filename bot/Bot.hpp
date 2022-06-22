/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 12:04:18 by kzennoun          #+#    #+#             */
/*   Updated: 2022/06/22 12:29:11 by kzennoun         ###   ########lyon.fr   */
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
		Bot(const Bot &src);
		~Bot();

		bool get_running() const;
		int get_serverFD() const;
		std::string	get_buffer() const;
		bool get_logged() const;
		std::string get_nickname() const;
		
		void set_running(bool running);
		void set_serverFD(int serverFD);
		void set_logged(bool logged);
		void set_nickname(std::string nick);

		Bot& operator=(const Bot& rhs);

		void append_buffer(char* buffer);
		std::string extract_command(size_t pos);
		bool send_message(std::string message);
		int handle_incoming_message();
		void ft_split_parameter(Message &msg);
		Message *ft_create_message(std::string str);
		void do_command(Message &msg);
		std::vector<std::string> ft_split_message(std::string str);
		bool do_parsing(std::string message);

	protected:

	private:

		bool		_running;
		int			_serverFD;
		std::string	_buffer;
		bool		_logged;
		std::string _nickname;
};

#endif