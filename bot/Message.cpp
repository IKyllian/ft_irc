#include "Message.hpp"

Message::Message() {}
Message::Message(const Message &message) : _payload(message._payload), _prefix(message._prefix),  _command(message._command),/* _command_info(message._command_info), _mask(message._mask), _subject(message._subject),*/ _parameter(message._parameter) {}
Message::~Message() {}

void Message::set_prefix(std::string &val) {
	_prefix = val;
}

void Message::set_command(std::string &val) {
	_command = val;
}

void Message::set_parameter(std::string &val) {
	_parameter = val;
}

void Message::set_nb_parameter(int val) {
	_nb_parameter = val;
}

std::string 				Message::get_prefix() const { return (_prefix); } ;
std::string 				Message::get_command() const { return (_command); };
std::string 				Message::get_parameter() const { return (_parameter); } ;
int							Message::get_nb_parameter() const { return (_nb_parameter); } ;
std::vector<std::string>	&Message::get_tab_parameter() { return (_tab_parameter); }

std::string 				Message::get_target_nickname() const
{
	std::string nick;
	size_t pos = get_prefix().find("!");

	nick = get_prefix().substr(1, pos - 1);

	return nick;
}
