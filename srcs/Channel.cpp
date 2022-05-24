#include "../includes/Channel.hpp"

Channel::Channel() {}
Channel::Channel(std::string &name) : name(name), user_limit(0) {}
Channel::Channel(const Channel &channel) : name(channel.name) {
	users.clear();
	users = channel.users;
	// users.insert(channel.users.begin(), channel.users.end());
	channel_modes = channel.channel_modes;
}

Channel::~Channel() {
	users.clear();
}

bool Channel::operator==(const Channel &channel) { return (get_name() == channel.get_name()); };

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
std::string 								Channel::get_password() const { return (password); }
int 										Channel::get_user_limit() const { return (user_limit); }

void Channel::set_name(std::string val) {
	name = val;
}

void Channel::set_password(std::string password) {
	this->password = password;
}

void Channel::set_user_limit(int limit) {
	user_limit = limit;
}

void Channel::set_user(Client* client, std::string key) { // Fonction qui sert a add un user au channel
	std::vector<Client*>::iterator it = search_user_ban(client);
	std::vector<Client*>::iterator it2 = search_user_invite(client);
	if ((channel_modes.find('l') == std::string::npos) || (channel_modes.find('l') != std::string::npos && users.size() < user_limit)) {
		if (users_ban.end() == it) {
			if (channel_modes.find('k') != std::string::npos) {
				std::cout << "Password = " << password << " - Key = " << key << std::endl;
				if (key != password) {
					ft_print_numerics(475);
					return ;
				}
			}
			if (channel_modes.find('i') != std::string::npos) {
				if (it2 != invite_list.end()) { // Check si le user a recu une invitation
					users.insert(std::pair<Client*, std::string>(client, ""));
					invite_list.erase(it2);
				} else
					ft_print_numerics(473);
			} else {
				users.insert(std::pair<Client*, std::string>(client, ""));
			}
		} else
			ft_print_numerics(474);
	} else
		ft_print_numerics(471);
}

void Channel::set_mode(char mode, std::string parameter) {
	size_t nb;
	if (mode == 'o') {
		if (parameter == "")
			ft_print_numerics(461);
		else {
			set_user_mode(mode, parameter);
			channel_modes.push_back(mode);
		}
	} else if (mode == 'p')
		channel_modes.push_back(mode);
	else if (mode == 's')
		channel_modes.push_back(mode);
	else if (mode == 'i')
		channel_modes.push_back(mode);
	else if (mode == 't')
		channel_modes.push_back(mode);
	else if (mode == 'n')
		channel_modes.push_back(mode);
	else if (mode == 'm')
		channel_modes.push_back(mode);
	else if (mode == 'l') {
		if (parameter == "")
			ft_print_numerics(461);
		std::istringstream(parameter) >> nb; // Pas de gestion d'erreur pour l'instant (ex: 45qwef)
		if (nb < 0 || nb > SIZE_MAX)
			ft_print_numerics(461);
		else {
			channel_modes.push_back(mode);
			set_user_limit(nb);
		}
	} else if (mode == 'b') {
		std::map<Client*, std::string>::iterator it = users.begin();
		for (; it != users.end(); it++)
		if ((*it).first->get_nickname() == parameter)
			break;
		if (it == users.end())
			ft_print_numerics(401);
		else
			ban_user((*it).first);
	} else if (mode == 'v') {
		if (parameter == "")
			ft_print_numerics(461);
		else
			set_user_mode(mode, parameter);
	} else if (mode == 'k') {
		if (parameter == "")
			ft_print_numerics(461);
		else {
			set_password(parameter);
			channel_modes.push_back(mode);
		}
	}
	else
		ft_print_numerics(472);
}

void Channel::unset_mode(char mode, std::string parameter) {
	if (mode == 'o') {
		if (parameter == "")
			ft_print_numerics(461);
		else {
			unset_user_mode(mode, parameter);
			channel_modes.erase(channel_modes.find(mode), 1);
		}
	} else if (mode == 'p')
		channel_modes.erase(channel_modes.find(mode), 1);
	else if (mode == 's')
		channel_modes.erase(channel_modes.find(mode), 1);
	else if (mode == 'i')
		channel_modes.erase(channel_modes.find(mode), 1);
	else if (mode == 't')
		channel_modes.erase(channel_modes.find(mode), 1);
	else if (mode == 'n')
		channel_modes.erase(channel_modes.find(mode), 1);
	else if (mode == 'm')
		channel_modes.erase(channel_modes.find(mode), 1);
	else if (mode == 'l') {
		channel_modes.erase(channel_modes.find(mode), 1);
		set_user_limit(0);
	} else if (mode == 'b') {
		std::map<Client*, std::string>::iterator it = users.begin();
		for (; it != users.end(); it++)
		if ((*it).first->get_nickname() == parameter)
			break;
		if (it == users.end())
			ft_print_numerics(401);
		else
			unban_user((*it).first);
	} else if (mode == 'v') {
		if (parameter == "")
			ft_print_numerics(461);
		else
			unset_user_mode(mode, parameter);
	} else if (mode == 'k') {
		if (parameter == "")
			ft_print_numerics(461);
		else {
			set_password();
			channel_modes.erase(channel_modes.find(mode), 1);
		}
	}
	else
		ft_print_numerics(472);
}

void Channel::set_channel_modes(std::string mode, std::vector<std::string> parameters) {
	std::string modes = "opsitnmlbvk";
	if (mode.size() > 1) {
		if (mode[0] == '+') {
			for (size_t i = 1; i < mode.size(); i++) {
				if (modes.find(mode[i]) != std::string::npos) {
					if (channel_modes.find(mode[i]) != std::string::npos) {
							ft_print_numerics(501); //Check si c'est bien cette erreur
							continue;
					} else {
						if (parameters.size() > 0 && i - 1 < parameters.size())
							set_mode(mode[i], parameters[i - 1]);
						else
							set_mode(mode[i]);
					}
				} else
					ft_print_numerics(472);
			}
		} else if (mode[0] == '-') {
			for (size_t i = 1; i < mode.size(); i++) {
				if (modes.find(mode[i]) != std::string::npos) {
					if (channel_modes.find(mode[i]) == std::string::npos) {
							ft_print_numerics(501);
							continue;
					} else {
						if (parameters.size() > 0 && i - 1 < parameters.size())
							unset_mode(mode[i], parameters[i - 1]);
						else
							unset_mode(mode[i]);
					}
				}
			}
		} else
			std::cout << "Mode : error syntax" << std::endl;
	} else
		std::cout << "Mode : error syntax" << std::endl;
}

void Channel::set_user_mode(char mode, std::string parameter) {
	std::map<Client*, std::string>::iterator it = users.begin();
	for (; it != users.end(); it++)
		if ((*it).first->get_nickname() == parameter)
			break;
	if (it == users.end())
		ft_print_numerics(401);
	else {
		if (it->second.find(mode) == std::string::npos)
			it->second.push_back(mode);
	}
}

void Channel::unset_user_mode(char mode, std::string parameter) {
	std::map<Client*, std::string>::iterator it = users.begin();
	for (; it != users.end(); it++)
		if ((*it).first->get_nickname() == parameter)
			break;
	if (it == users.end())
		ft_print_numerics(401);
	else {
		if (it->second.find(mode) != std::string::npos)
			it->second.erase(channel_modes.find(mode), 1);
	}
}

// void Channel::set_user_mode(std::string mode, Client *client) {
// 	std::string modes = "iswo";
// 	std::map<Client*, std::string>::iterator it = users.find(client);
// 	if (users.end() == it)
// 		ft_print_numerics(401);
// 	else {
// 		if (mode.size() > 1) {
// 			if (mode[0] == '+') {
// 				for (size_t i = 1; i < mode.size(); i++) {
// 					if (modes.find(mode[i]) != std::string::npos) {
// 						if (it->second.find(mode[i]) != std::string::npos) {
// 							ft_print_numerics(501);
// 							continue;
// 						} else
// 							it->second.push_back(mode[i]);
// 					}
// 				}
// 			} else if (mode[0] == '-') {
// 				for (size_t i = 1; i < mode.size(); i++) {
// 					if (modes.find(mode[i]) != std::string::npos) {
// 						if (it->second.find(mode[i]) == std::string::npos) {
// 							ft_print_numerics(501);
// 							continue;
// 						} else
// 							it->second.erase(it->second.find(mode[i]), 1);
// 					}
// 				}
// 			} else
// 				std::cout << "Mode : error syntax" << std::endl;
// 		} else
// 			std::cout << "Mode : error syntax" << std::endl;
// 	}
// }

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


void Channel::unban_user(Client *client) {
	std::vector<Client*>::iterator it = search_user_ban(client);
	if (users_ban.end() != it)
		users_ban.erase(it);
}

void Channel::print_users() {
	for (std::map<Client*, std::string>::iterator it = users.begin(); it != users.end(); it++)
		std::cout << it->first->get_nickname() << std::endl;
}

std::vector<std::string> parse_comma(std::string parameter) {
	std::vector<std::string> strings_parse;
	int idx = 0;
	size_t pos = parameter.find(",", idx);
	while (pos != std::string::npos) {
		strings_parse.push_back(parameter.substr(idx, pos - idx));
		idx = pos + 1;
		pos = parameter.find(",", idx);
	}
	strings_parse.push_back(parameter.substr(idx, parameter.size() - idx));
	return (strings_parse);
}

void join_command(std::vector<std::string> parameters, std::vector<Channel> *channels, Client *client) {
	std::vector<std::string> channels_string;
	std::vector<std::string> keys;
	channels_string = parse_comma(parameters[0]);
	if (parameters.size() > 1)
		keys = parse_comma(parameters[1]);
	for (size_t i = 0; i < channels_string.size(); i++) {
		if (keys.size() - 1 > i)
			join_channel(channels, client, channels_string[i]);
		else
			join_channel(channels, client, channels_string[i], keys[i]);
	}
}

void join_channel(std::vector<Channel> *channels, Client *client, std::string channel, std::string key) {
	std::vector<Channel>::iterator it = channels->begin();
	for (; it != channels->end(); it++) {
		if ((*it).get_name() == channel)
			break;
	}
	if (it == channels->end())
		channels->push_back(Channel(channel));
	it = channels->begin();
	for (; it != channels->end(); it++) {
		if ((*it).get_name() == channel)
			break;
	}
	(*it).set_user(client, key);
}