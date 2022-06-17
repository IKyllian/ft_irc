#ifndef BOT_HPP
#define BOT_HPP

#include <iostream>

class Bot
{
	public:

	void append_buffer(char* buffer);
	std::string extract_command(size_t pos);
	std::string	get_buffer() const;

	protected:

	private:

	std::string	_buffer;

	

};

#endif