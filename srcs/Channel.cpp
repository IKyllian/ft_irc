#include "../includes/Channel.hpp"

Channel::Channel() {}
Channel::Channel(std::string &name) : name(name) {}
Channel::Channel(const Channel &channel) : name(channel.name) {
	users.clear();
	users.insert(channel.users.begin(), channel.users.end());
	channel_modes = channel.channel_modes;
}

Channel::~Channel() {
	users.clear();
}

std::string Channel::get_name() const { return (name); }
std::map<Client&, std::string> &Channel::get_users()  { return (users); }
std::map<Client&, std::string>::iterator Channel::get_user(Client& client) { return (users.find(client)); }
std::string Channel::get_channel_modes() const { return (channel_modes); }

void Channel::set_name(std::string val) {
	name = val;
}

void Channel::set_users(Client& user) {
	users.insert(std::pair<Client&, std::string>(user, ""));
}

void Channel::set_channel_modes(std::string mode) {
	std::string modes = "opsitnmlbvk";
	if (mode.size() > 2) {
		if (mode[0] == '+') {
			for (size_t i = 1; i < mode.size(); i++) {
				if (modes.find(mode[i]) != std::string::npos) {
					if (channel_modes.find(mode[i]) != std::string::npos) {
							ft_message(501);
							continue;
						}
					else
						channel_modes.push_back(mode[i]);
				}
			}
		} else if (mode[0] == '-') {
			for (size_t i = 1; i < mode.size(); i++) {
				if (modes.find(mode[i]) != std::string::npos) {
					if (channel_modes.find(mode[i]) == std::string::npos) {
							ft_message(501);
							continue;
						}
					else
						channel_modes.erase(channel_modes.find(mode[i]), 1);
				}
			}
		} else
			std::cout << "Mode : error syntax" << std::endl;
	} else
		std::cout << "Mode : error syntax" << std::endl;
}

void Channel::set_user_mode(std::string mode, Client &client) {
	std::string modes = "iswo";
	std::map<Client&, std::string>::iterator it = users.find(client);
	if (users.end() == it)
		ft_message(401);
	else {
		if (mode.size() > 2) {
			if (mode[0] == '+') {
				for (size_t i = 1; i < mode.size(); i++) {
					if (modes.find(mode[i]) != std::string::npos) {
						if (it->second.find(mode[i]) != std::string::npos) {
							ft_message(501);
							continue;
						}
						else
							it->second.push_back(mode[i]);
					}
				}
			} else if (mode[0] == '-') {
				for (size_t i = 1; i < mode.size(); i++) {
					if (modes.find(mode[i]) != std::string::npos) {
						if (it->second.find(mode[i]) == std::string::npos) {
							ft_message(501);
							continue;
						}
						else
							it->second.erase(it->second.find(mode[i]), 1);
					}
				}
			} else
				std::cout << "Mode : error syntax" << std::endl;
		} else
			std::cout << "Mode : error syntax" << std::endl;
	}
}

// void Channel::remove_user(std::string username) {
// 	std::map<std::string, std::string>::iterator it = users.find(username);
// 	if (users.end() == it)
// 		ft_message(442);
// 	else {

// 	}
// }