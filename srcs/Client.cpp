#include "../includes/Client.hpp"

Client::Client() : _realname (""), _logged(false), _away(false) {}
Client::Client(std::string nickname) : _nickname(nickname), _logged(false), _away(false) {};
Client::Client(const Client &client) : 
	_nickname(client._nickname),
	_username(client._username),
	_realname(client._realname),
	_hostname(client._hostname),
	_user_modes(client._user_modes),
	_fd(client._fd),
	_logged(client._logged),
	_registered(client._registered), 
	_authentified(client._authentified), 
	_hasnick(client._hasnick), 
	_away(client._away),
	_quitting(client._quitting),
	_away_msg(client._away_msg),
	_buffer(client._buffer) {}
// Client::Client(const Client *client) {
// 	*this = client;
// }

Client::Client(int &fd) : 
	_nickname("*"), 
	_username("*"), 
	_realname(""),
	_hostname("*"), 
	_user_modes(""), 
	_fd(fd), 
	_logged(false), 
	_registered(false), 
	_authentified(false), 
	_hasnick(false), 
	_away(false), 
	_quitting(false),
	_away_msg(""), 
	_buffer("")  {}
	
Client::~Client() {
	_channel.clear();
}

bool Client::operator==(const Client& rhs) {
	return (get_nickname() == rhs.get_nickname());
};

// bool Client::operator<(const Client &rhs) const {
// 	return (get_nickname() < rhs.get_nickname());
// }
//:<nickname>@<username>!<hostname>
std::string 			Client::get_nickname() const { return (_nickname); }
std::string 			Client::get_username() const { return (_username); }
std::string 			Client::get_realname() const { return (_realname); }
std::string 			Client::get_hostname() const { return (_hostname); }
std::string				Client::get_fullidentity() const { return  (get_nickname() + "!" + get_username() + "@" + get_hostname()); }
std::string 			Client::get_user_modes() const { return (_user_modes); }
int						Client::get_fd() const { return (_fd); }
bool					Client::get_logged() const { return (_logged); }
bool					Client::get_registered() const { return (_registered); }
bool					Client::get_authentified() const { return (_authentified); }
bool					Client::get_hasnick() const { return (_hasnick); }
bool					Client::get_away() const { return (_away); }
bool					Client::get_quitting() const { return (_quitting); }
std::string 			Client::get_away_msg() const { return (_away_msg); }
std::string				Client::get_buffer() const { return (_buffer); }
std::vector<Channel*>	&Client::get_channel() { return (_channel); };


std::vector<Channel*>::iterator	Client::get_channel_by_name(std::string name) {
	std::vector<Channel*>::iterator	channel_it;

	for (channel_it = _channel.begin(); channel_it != _channel.end(); channel_it++)
		if ((*channel_it)->get_name() == name)
			break;
	return (channel_it);
}

void Client::set_nickname(std::string val) {
	_nickname = val;
	set_hasnick(true);
}

void Client::set_username(std::string val) {
	_username = val;
}

void Client::set_realname(std::string val) {
	_realname = val;
}

void Client::set_hostname(std::string val) {
	_hostname = val;
}

// void Client::set_user_modes(std::string mode) {
// 	const std::string modes = "iswo";

// 	if (mode.size() > 1) {
// 		if (mode[0] == '+') {
// 			for (size_t i = 1; i < mode.size(); i++) {
// 				if (modes.find(mode[i]) != std::string::npos) {
// 					if (_user_modes.find(mode[i]) != std::string::npos) {
// 							ft_print_numerics(501);
// 							continue;
// 					} else {
// 						ft_print_numerics(221); // RPL_UMODEIS
// 						_user_modes.push_back(mode[i]);
// 					}
// 				} else
// 					ft_print_numerics(472);
// 			}
// 		} else if (mode[0] == '-') {
// 			for (size_t i = 1; i < mode.size(); i++) {
// 						_user_modes.erase(_user_modes.find(mode[i]));
// 						ft_print_numerics(221); // RPL_UMODEIS
				
// 				}
// 			}
// 		} else
// 			std::cout << "Mode : error syntax" << std::endl;
// 	} else
// 		send_message(*sender, _server->print_numerics(221, *this, *this, NULL, NULL));
// 		// ft_print_numerics(221); // RPL_CHANNELMODEIS (Si aucun mode n'est donné, renvoie juste les modes actuels)
// }

void Client::set_user_modes(std::string mode, Server &server) {
	const std::string modes = "iswo";
	std::string string_mode;
	std::string output = "";
	char symbol;

	if (mode.size() > 1) {
		if (mode[0] != '+' && mode[0] != '-')
			std::cout << "Mode : error syntax" << std::endl;
		else {
			for (size_t i = 0; i < mode.size(); i++) {
				if (mode[i] == '+' || mode[i] == '-') {
					symbol = mode[i];
					continue ;
				}
				if (symbol == '+') {
					if (modes.find(mode[i]) != std::string::npos) {
						_user_modes.push_back(mode[i]);
						if (output.find("+") == std::string::npos)
							output += "+";
						output += mode[i];
					} else {
						string_mode += mode[i];
						send_message(*this, build_message2(472, *this, string_mode, NULL));
						string_mode = "";
					}
				} else if (symbol == '-') {
					if (modes.find(mode[i]) != std::string::npos) {
						if (_user_modes.find(mode[i]) == std::string::npos)
							continue ;
						_user_modes.erase(_user_modes.find(mode[i]));
						if (output.find("-") == std::string::npos)
							output += "-";
						output += mode[i];
					} else {
						string_mode += mode[i];
						send_message(*this, build_message2(472, *this, string_mode, NULL));
						string_mode = "";
					}
				}
			}
			if (mode.size() > 0) {
				send_message(*this, build_command_message(_nickname, output, _nickname, "MODE"));
			}
		}
	} else		
		send_message(*this, server.print_numerics(221, *this, *this, NULL, NULL));
}


void Client::set_fd(int val) {
	_fd = val;
}

void Client::set_logged(bool val) {
	_logged = val;
}

void Client::set_registered(bool val) {
	_registered = val;
}

void Client::set_authentified(bool val) {
	_authentified = val;
}

void Client::set_hasnick(bool val) {
	_hasnick = val;
}

void Client::set_away(bool val){
	_away = val;
}

void Client::set_quitting(bool val) {
	_quitting = val;
}

void Client::set_away_msg(std::string msg)
{
	_away_msg = msg;
}

void Client::append_buffer(char* buffer) {
	_buffer += buffer;
}

std::string Client::extract_command(size_t pos) {
	std::string command;

	command = _buffer.substr(0, pos + 2);
	_buffer = _buffer.substr(pos + 2, - 1);

// std::cout << "######commamnd:" << std::endl;
// 	for (unsigned long k = 0; k < command.length(); k++)
// 	{
// 		std::cout << "i: " << k << " command[k]: " << command[k] << " (int): " << (int) command[k] << std::endl;
// 	}
// std::cout << "######buffer:" << std::endl;
// 	for (unsigned long k = 0; k < _buffer.length(); k++)
// 	{
// 		std::cout << "i: " << k << " _buffer[k]: " << _buffer[k] << " (int): " << (int) _buffer[k] << std::endl;
// 	}

	return command;
}