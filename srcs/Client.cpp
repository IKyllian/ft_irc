#include "../includes/Client.hpp"

Client::Client() : _logged(false){}
Client::Client(std::string nickname) : _nickname(nickname), _logged(false) {};
Client::Client(const Client &client) : _nickname(client._nickname), _username(client._username), _user_modes(client._user_modes), _fd(client._fd), _logged(client._logged), _buffer(client._buffer) {}
// Client::Client(const Client *client) {
// 	*this = client;
// }

Client::Client(int &fd) : _fd(fd), _logged(false){}
Client::~Client() {}

bool Client::operator==(const Client& rhs) {
	return (get_username() == rhs.get_username());
};

bool Client::operator<(const Client &rhs) const {
	return (get_username() < rhs.get_username());
}

std::string Client::get_nickname() const { return (_nickname); }
std::string Client::get_username() const { return (_username); }
std::string Client::get_user_modes() const { return (_user_modes); }
int			Client::get_fd() const { return (_fd); }
bool		Client::get_logged() const { return (_logged); }
std::string	Client::get_buffer() const { return (_buffer); }


void Client::set_nickname(std::string val) {
	_nickname = val;
}

void Client::set_username(std::string val) {
	_username = val;
}

void Client::set_user_modes(std::string mode) {
	const std::string modes = "iswo";
	if (mode.size() > 1) {
		if (mode[0] == '+') {
			for (size_t i = 1; i < mode.size(); i++) {
				if (modes.find(mode[i]) != std::string::npos) {
					if (_user_modes.find(mode[i]) != std::string::npos) {
							ft_print_numerics(501); // Check si il faut mettre l'erreur
							continue;
					} else {
						ft_print_numerics(221); // RPL_UMODEIS
						_user_modes.push_back(mode[i]);
					}
				} else
					ft_print_numerics(472);
			}
		} else if (mode[0] == '-') {
			for (size_t i = 1; i < mode.size(); i++) {
				if (modes.find(mode[i]) != std::string::npos) {
					if (_user_modes.find(mode[i]) == std::string::npos) {
							ft_print_numerics(501); // Check si il faut mettre l'erreur
							continue;
					} else {
						_user_modes.erase(_user_modes.find(mode[i]));
						ft_print_numerics(221); // RPL_UMODEIS
					}
				}
			}
		} else
			std::cout << "Mode : error syntax" << std::endl;
	} else
		ft_print_numerics(221); // RPL_CHANNELMODEIS (Si aucun mode n'est donné, renvoie juste les modes actuels)
}

void Client::set_fd(int &val) {
	_fd = val;
}

void Client::set_logged(bool &val) {
	_logged = val;
}

void Client::append_buffer(char* buffer) {
	_buffer += buffer;
}

std::string Client::extract_command(size_t pos) {
	std::string command;

	command = _buffer.substr(0, pos + 1);
	_buffer = _buffer.substr(pos + 2, - 1);

	return command;
}