#include "../includes/Message.hpp"

Message::Message() {}
Message::Message(const Message &message) :_sender(message._sender), _receiver(message._receiver), _payload(message._payload), _prefix(message._prefix),  _command(message._command),/* _command_info(message._command_info), _mask(message._mask), _subject(message._subject),*/ _parameter(message._parameter) {}
Message::~Message() {}

void Message::set_sender(Client *val) {
	_sender = val;
}

// void Message::set_receiver(Client &val) {
// 	*_receiver = val;
// }

// void Message::set_payload(std::string &val) {
// 	_payload = val;
// }

void Message::set_prefix(std::string &val) {
	_prefix = val;
}

void Message::set_command(std::string &val) {
	_command = val;
}

// void Message::set_command_info(std::string &val) {
// 	_command_info = val;
// }

// void Message::set_mask(std::string &val) {
// 	_mask = val;
// }

// void Message::set_subject(std::string &val) {
// 	_subject = val;
// }

void Message::set_parameter(std::string &val) {
	_parameter = val;
}

void Message::set_nb_parameter(int val) {
	_nb_parameter = val;
}

Client 						&Message::get_sender() const { return (*_sender); };
Client 						&Message::get_receiver() const { return (*_receiver); } ;
// std::string 				Message::get_payload() const { return (_payload); } ;
std::string 				Message::get_prefix() const { return (_prefix); } ;
std::string 				Message::get_command() const { return (_command); };
// std::string 				Message::get_command_info() const { return (_command_info); } ;
// std::string 				Message::get_mask() const { return (_mask); } ;
// std::string 				Message::get_subject() const { return (_subject); } ;
std::string 				Message::get_parameter() const { return (_parameter); } ;
int							Message::get_nb_parameter() const { return (_nb_parameter); } ;
std::vector<std::string>	&Message::get_tab_parameter() { return (_tab_parameter); }
