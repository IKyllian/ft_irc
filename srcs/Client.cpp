#include "../includes/Client.hpp"

Client::Client() : _logged(false){}
Client::Client(std::string nickname) : _nickname(nickname), _logged(false) {};
Client::Client(const Client &client) : _nickname(client._nickname), _username(client._username), _user_modes(client._user_modes), _fd(client._fd), _logged(client._logged) {}
Client::Client(int &fd) : _fd(fd), _logged(false){}
Client::~Client() {}

bool operator==(const Client& lhs, const Client& rhs) {
	
};

std::string Client::get_nickname() const { return (_nickname); }
std::string Client::get_username() const { return (_username); }
std::string Client::get_user_modes() const { return (_user_modes); }
int			Client::get_fd() const { return (_fd); }
bool		Client::get_logged() const { return (_logged); }

void Client::set_nickname(std::string &val) {
	_nickname = val;
}

void Client::set_username(std::string &val) {
	_username = val;
}

void Client::set_user_modes(std::string &val) {
	_user_modes = val;
}

void Client::set_fd(int &val) {
	_fd = val;
}

void Client::set_logged(bool &val)
{
	_logged = val;
}