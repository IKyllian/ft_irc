/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 12:04:18 by kzennoun          #+#    #+#             */
/*   Updated: 2022/06/17 16:45:31 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_HPP
#define BOT_HPP

#include <iostream>
#include <sys/socket.h>

class Bot
{
	public:

	void set_serverFD(int serverFD);
	int get_serverFD() const;

	void append_buffer(char* buffer);
	std::string extract_command(size_t pos);
	std::string	get_buffer() const;
	bool parse_and_do(std::string message) const;
	bool send_message(std::string message);
	int handle_incoming_message();

	protected:

	private:

	std::string	_buffer;
	int			_serverFD;

	

};

#endif