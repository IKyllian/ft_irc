#include "Message.hpp"

Message::Message() {}
Message::Message(const Message &message):
				_prefix(message._prefix),
				_command(message._command),
				_parameter(message._parameter),
				_tab_parameter(message._tab_parameter) {}
Message::~Message() {}

std::string 				Message::get_prefix() const { return (_prefix); } ;
std::string 				Message::get_command() const { return (_command); };
std::string 				Message::get_parameter() const { return (_parameter); } ;
std::vector<std::string>	&Message::get_tab_parameter() { return (_tab_parameter); }

void Message::set_prefix(std::string &val) {
	_prefix = val;
}

void Message::set_command(std::string &val) {
	_command = val;
}

void Message::set_parameter(std::string &val) {
	_parameter = val;
}

Message& Message::operator=(const Message& rhs) {
	_prefix = rhs._prefix;
	_command = rhs._command;
	_parameter = rhs._parameter;
	_tab_parameter = rhs._tab_parameter;
	return *this;
}

std::string Message::get_target_nickname() const
{
	std::string nick;
	size_t pos = get_prefix().find("!");

	nick = get_prefix().substr(1, pos - 1);

	return nick;
}