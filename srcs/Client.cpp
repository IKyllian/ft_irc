#include "../includes/Client.hpp"

Client() {}
Client(const Client &client) : nickname(cleint.nickname), username(client.username), user_modes(client.user_modes) {}
~Client() {}

std::string get_nickname() const { return (nickname); }
std::string get_username() const { return (username); }
std::string get_user_modes() const { return (user_modes); }

void set_nickname(std::string &val) {
	nickname = val;
}

void set_username(std::string &val) {
	username = val;
}

void set_user_modes(std::string &val) {
	user_modes = val;
}