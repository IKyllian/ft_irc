/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 12:04:18 by kzennoun          #+#    #+#             */
/*   Updated: 2022/06/17 15:43:32 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_HPP
#define BOT_HPP

#include <iostream>

class Bot
{
	public:

	void append_buffer(char* buffer);
	std::string extract_command(size_t pos);
	std::string	Bot::get_buffer() const;

	protected:

	private:

	std::string	_buffer;

	

};

#endif