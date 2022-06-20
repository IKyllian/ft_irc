#include "../includes/Message.hpp"

Message::Message() {}
Message::Message(const Message &message):
		_sender(message._sender),
		_receiver(message._receiver),
		_payload(message._payload),
		_prefix(message._prefix),
		_command(message._command),
		_parameter(message._parameter),
		_nb_parameter(message._nb_parameter){}

Message::~Message() {}


Message& Message::operator=(const Message& rhs)
{
	_sender = rhs._sender;
	_receiver = rhs._receiver;
	_payload = rhs._payload;
	_prefix = rhs._prefix;
	_command = rhs._command;
	_parameter = rhs._parameter;
	_nb_parameter = rhs._nb_parameter;

	return *this;
}


void Message::set_sender(Client *val) {
	_sender = val;
}

void Message::set_receiver(Client *val) {
	_receiver = val;
}

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

Client 						&Message::get_sender() const { return (*_sender); };
Client 						&Message::get_receiver() const { return (*_receiver); } ;
std::string 				Message::get_prefix() const { return (_prefix); } ;
std::string 				Message::get_command() const { return (_command); };
std::string 				Message::get_parameter() const { return (_parameter); } ;
int							Message::get_nb_parameter() const { return (_nb_parameter); } ;
std::vector<std::string>	&Message::get_tab_parameter() { return (_tab_parameter); }
