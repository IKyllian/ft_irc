#include "../includes/Channel.hpp"

Channel::Channel() {}
Channel::Channel(std::string &name) : name(name) {}
Channel::Channel(const Channel &channel) : name(channel.name) {
	users.clear();
	users = channel.users;
	// users.insert(channel.users.begin(), channel.users.end());
	channel_modes = channel.channel_modes;
}

Channel::~Channel() {
	users.clear();
}

std::vector<Client*>::iterator Channel::search_user_invite(Client *client) {
	std::vector<Client*>::iterator it = invite_list.begin();
	for (; it != invite_list.end(); it++)
		if (*it == client)
			return (it);
	return (it);
}

std::vector<Client*>::iterator Channel::search_user_ban(Client *client) {
	std::vector<Client*>::iterator it = users_ban.begin();
	for (; it != users_ban.end(); it++)
		if (*it == client)
			return (it);
	return (it);
}

std::string									Channel::get_name() const { return (name); }
std::map<Client*, std::string>				&Channel::get_users()  { return (users); }
std::vector<Client*>						&Channel::get_users_ban() { return (users_ban); };
std::vector<Client*>						&Channel::get_invite_list() { return (invite_list); };
std::map<Client*, std::string>::iterator	Channel::get_user(Client* client) { return (users.find(client)); }
std::string									Channel::get_channel_modes() const { return (channel_modes); }

void Channel::set_name(std::string val) {
	name = val;
}

void Channel::set_user(Client* client) { // Fonction qui sert a add un user au channel
	std::vector<Client*>::iterator it = search_user_ban(client);
	std::vector<Client*>::iterator it2 = search_user_invite(client);
	if (users_ban.end() == it) {
		if (channel_modes.find('i') == std::string::npos)
			users.insert(std::pair<Client*, std::string>(client, ""));
		else {
			if (it2 != invite_list.end()) { // Check si le user a recu une invitation
				users.insert(std::pair<Client*, std::string>(client, ""));
				invite_list.erase(it2);
			}
			else
				ft_print_numerics(473);
		}
	}
	//else
		//Check l'erreur a mettre si un client essaie de join un channel où il est ban
}

void Channel::set_channel_modes(std::string mode) {
	std::string modes = "opsitnmlbvk";
	if (mode.size() > 1) {
		if (mode[0] == '+') {
			for (size_t i = 1; i < mode.size(); i++) {
				if (modes.find(mode[i]) != std::string::npos) {
					if (channel_modes.find(mode[i]) != std::string::npos) {
							ft_print_numerics(501);
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
							ft_print_numerics(501);
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

void Channel::set_user_mode(std::string mode, Client *client) {
	std::string modes = "iswo";
	std::map<Client*, std::string>::iterator it = users.find(client);
	if (users.end() == it)
		ft_print_numerics(401);
	else {
		if (mode.size() > 1) {
			if (mode[0] == '+') {
				for (size_t i = 1; i < mode.size(); i++) {
					if (modes.find(mode[i]) != std::string::npos) {
						if (it->second.find(mode[i]) != std::string::npos) {
							ft_print_numerics(501);
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
							ft_print_numerics(501);
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

void Channel::add_invite(Client *client) {
	std::vector<Client*>::iterator it = search_user_invite(client);
	std::vector<Client*>::iterator it2 = search_user_ban(client);
	if (it2 == users_ban.end()) {
		if (it == invite_list.end())
			invite_list.push_back(client);
	}
}

void Channel::remove_user(Client *client) {
	std::map<Client*, std::string>::iterator it = users.find(client);
	if (users.end() == it)
		ft_print_numerics(442);
	else {
		users.erase(it);
		remove_invite(client);
	}
}

void Channel::remove_invite(Client *client) {
	std::vector<Client*>::iterator it = search_user_invite(client);
	if (invite_list.end() != it)
		invite_list.erase(it);
}

void Channel::ban_user(Client *client) {
	std::map<Client*, std::string>::iterator it = users.find(client);
	std::vector<Client*>::iterator it2 = search_user_ban(client);
	if (users.end() != it)
		users.erase(it);
	if (users_ban.end() == it2)
		users_ban.push_back(client);
	remove_invite(client);
}

void Channel::print_users() {
	for (std::map<Client*, std::string>::iterator it = users.begin(); it != users.end(); it++)
		std::cout << it->first->get_nickname() << std::endl;
}