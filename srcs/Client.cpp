#include "../includes/Client.hpp"

Client::Client() {}
Client::Client(const Client &client) : nickname(client.nickname), username(client.username), user_modes(client.user_modes), fd(client.fd) {}
Client::~Client() {}

std::string Client::get_nickname() const { return (nickname); }
std::string Client::get_username() const { return (username); }
std::string Client::get_user_modes() const { return (user_modes); }
int			Client::get_fd() const { return (fd); }

void Client::set_nickname(std::string &val) {
	nickname = val;
}

void Client::set_username(std::string &val) {
	username = val;
}

void Client::set_user_modes(std::string &val) {
	user_modes = val;
}

void Client::set_fd(int &val) {
	fd = val;
}