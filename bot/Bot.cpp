#include "Bot.hpp"

std::string	Bot::get_buffer() const { return (_buffer); }

void Bot::append_buffer(char* buffer) {
	_buffer += buffer;
}

std::string Bot::extract_command(size_t pos) {
	std::string command;

	command = _buffer.substr(0, pos + 2);
	_buffer = _buffer.substr(pos + 2, - 1);

	return command;
}