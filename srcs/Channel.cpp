#include "../includes/Channel.hpp"

Channel::Channel(){}
Channel::Channel(std::string &name, Server *server) : _name(name), _user_limit(0), _server(server) {}
Channel::Channel(const Channel &channel) : _name(channel._name) {
	_users.clear();
	_users = channel._users;
	// users.insert(channel.users.begin(), channel.users.end());
	_channel_modes = channel._channel_modes;
	_server = channel._server;
}

Channel::~Channel() {
	_users.clear();
}

bool Channel::operator==(const Channel &channel) { return (get_name() == channel.get_name()); };

std::vector<std::string>::iterator Channel::search_user_invite(std::string name) {
	std::vector<std::string>::iterator it = _invite_list.begin();
	for (; it != _invite_list.end(); it++)
		if ((*it) == name)
			return (it);
	return (it);
}

std::vector<std::string>::iterator Channel::search_user_ban(std::string name) {
	std::vector<std::string>::iterator it = _users_ban.begin();
	for (; it != _users_ban.end(); it++)
		if ((*it) == name)
			return (it);
	return (it);
}

void 	Channel::erase_mode_arguments(std::string arg) {
	(void)arg;
};

std::string									Channel::get_name() const { return (_name); }
std::map<Client*, std::string>				&Channel::get_users() { return (_users); }
std::vector<std::string>					&Channel::get_users_ban() { return (_users_ban); };
std::vector<std::string>					&Channel::get_invite_list() { return (_invite_list); };
std::map<Client*, std::string>::iterator	Channel::get_user(Client* client) { return (_users.find(client)); }
std::string									Channel::get_channel_modes() const { return (_channel_modes); }
std::string 								Channel::get__mode_arguments() const { return (_mode_arguments); };
std::string 								Channel::get_password() const { return (_password); }
std::string 								Channel::get_topic() const { return (topic); };
int 										Channel::get_user_limit() const { return (_user_limit); }
Server 										&Channel::get_server() const { return (*_server); }

void Channel::set_name(std::string val) {
	_name = val;
}

void Channel::set_server(Server *server) {
	_server = server;
}

void Channel::set_password(std::string password) {
	this->_password = password;
}

void Channel::set_user_limit(int limit) {
	_user_limit = limit;
}

void Channel::set_topic(std::string new_topic) {
		topic = new_topic;
}

void Channel::set_user(Client* client, Message &message, std::string key) { // Fonction qui sert a add un user au channel
	std::map<Client*, std::string>::iterator user_it = get_user(client);
	std::vector<std::string>::iterator user_ban_it;
	std::vector<std::string>::iterator user_invite_it;

	if (user_it == _users.end()) {
		user_ban_it = search_user_ban(client->get_nickname());
		if ((_channel_modes.find('l') == std::string::npos) || (_channel_modes.find('l') != std::string::npos && _users.size() < _user_limit)) {
			if (_users_ban.end() == user_ban_it) {
				if (_channel_modes.find('k') != std::string::npos) {
					if (key != _password) {
						send_message(*client, _server->print_numerics(475, *client, *client, NULL, &message));
						return ;
					}
				}
				if (_channel_modes.find('i') != std::string::npos) {
					user_invite_it = search_user_invite(client->get_nickname());
					if (user_invite_it != _invite_list.end()) { // Check si le user a recu une invitation
						_users.insert(std::pair<Client*, std::string>(client, ""));
						client->get_channel().push_back(this);
						_invite_list.erase(user_invite_it);
						send_message(*client, build_command_message(client->get_nickname(), "", get_name(), "JOIN"));
						if (topic.size() > 0)
							send_message(*client, _server->build_response(332, *client, *client, this, &message));
						for (std::map<Client*, std::string>::iterator it2 = get_users().begin(); it2 != get_users().end(); it2++)
							send_message(*(it2->first), build_message2(353, message.get_sender(), "", this));
						send_message(*client, _server->build_response(366, *client, *client, this, &message));
					} else
						send_message(*client, _server->build_response(473, *client, *client, this, &message));
				} else {
					if (_users.size() == 0)
						_users.insert(std::pair<Client*, std::string>(client, "o"));
					else
						_users.insert(std::pair<Client*, std::string>(client, ""));
					client->get_channel().push_back(this);
					send_message(*client, build_command_message(client->get_nickname(), "", get_name(), "JOIN"));
					if (topic.size() > 0)
						send_message(*client, _server->build_response(332, *client, *client, this, &message));
					for (std::map<Client*, std::string>::iterator it2 = get_users().begin(); it2 != get_users().end(); it2++)
						send_message(*(it2->first), build_message2(353, message.get_sender(), "", this));
					send_message(*client, _server->build_response(366, *client, *client, this, &message));
				}
			} else
				send_message(*client, _server->print_numerics(474, *client, *client, NULL, &message));
		} else
			send_message(*client, _server->print_numerics(471, *client, *client, NULL, &message));
	} else
		send_message(*client, _server->print_numerics(443, *client, *client, this, &message));
}

int Channel::set_mode(Client *sender, char mode, std::string parameter) {
	size_t nb;

	if (mode == 'o') {
		if (parameter == "") {
			send_message(*sender, build_message2(461, *sender, "MODE", this));
			return (-1);
		}
		else
			set_user_mode(sender, mode, parameter);
		return (1);
	} else if (mode == 'i') {
		// for (std::map<Client*, std::string>::iterator it = get_users().begin(); it != get_users().end(); it++)
		// 	send_message(*(it->first), print_numerics(336, *sender, *sender, this));
		// send_message(*sender, print_numerics(337, *sender, *sender, this));

		//check RPL_INVEXLIST (346)
		// RPL_INVITELIST (336)
		// RPL_ENDOFINVITELIST (337)
	} else if (mode == 'l') {
		if (parameter == "") {
			send_message(*sender, build_message2(461, *sender, "MODE", this));
			return (-1);
		}
		for (size_t i = 0; i < parameter.size(); i++) {
			if ((parameter[i] < 48 || parameter[i] > 57) && parameter[i] != ' ') {
				std::cout << "Mode l : Parse Error" << std::endl;
				return (-1);
			}
		}
		std::istringstream(parameter) >> nb;
		if (nb > SIZE_MAX)
			send_message(*sender, build_message2(461, *sender, "MODE", this));
		else {
			set_user_limit(nb);
			_mode_arguments += parameter;
		}
	} else if (mode == 'b') {
		if (parameter == "") {
			send_message(*sender, build_message2(461, *sender, "MODE", this));
			return (-1);
		}
		ban_user(parameter);
		// for (std::map<Client*, std::string>::iterator it = get_users().begin(); it != get_users().end(); it++)
		// 	send_message(*(it->first), print_numerics(367, *sender, *sender, this));
		// send_message(*(it->first), print_numerics(368, *sender, *sender, this));
		// ft_print_numerics(367); // RPL_BANLIST
		// ft_print_numerics(368); // RPL_ENDOFBANLIST
	} else if (mode == 'v') {
		if (parameter == "") {
			send_message(*sender, build_message2(461, *sender, "MODE", this));
			return (-1);
		}
		else
			set_user_mode(sender, mode, parameter);
	} else if (mode == 'k') {
		if (parameter == "") {
			send_message(*sender, build_message2(461, *sender, "MODE", this));
			return (-1);
		}
		else {
			set_password(parameter);
			_mode_arguments += parameter;
		}
	}
	if (_channel_modes.find(mode) == std::string::npos)
		_channel_modes.push_back(mode);
	return (1);
}

int Channel::unset_mode(Client *sender, char mode, std::string parameter) {
	if (mode == 'o') {
		if (parameter == "") {
			ft_print_numerics(461);
			return (-1);
		}
		else {
			unset_user_mode(sender, mode, parameter);
			return (1);
		}
	} else if (mode == 'b') {
		if (parameter == "") {
			send_message(*sender, build_message2(461, *sender, "MODE", this));
			return (-1);
		}
		unban_user(parameter);
	} else if (mode == 'v') {
		if (parameter == "") {
			send_message(*sender, build_message2(461, *sender, "MODE", this));
			return (-1);
		}
		else
			unset_user_mode(sender, mode, parameter);
	} else if (mode == 'k') {
		if (parameter == "") {
			send_message(*sender, build_message2(461, *sender, "MODE", this));
			return (-1);
		}
		else {
			set_password();
			_channel_modes.erase(_channel_modes.find(mode), 1);
		}
	}
	if (_channel_modes.find(mode) != std::string::npos)
		_channel_modes.erase(_channel_modes.find(mode), 1);
	return (1);
}

void Channel::set_channel_modes(Client *sender, std::vector<std::string> parameters) {
	const std::string modes = "opsitnmlbvk";
	std::string mode = parameters[1];
	std::vector<std::string> params;
	std::string string_mode;
	char symbol;
	int ret;

	if (parameters.size() > 2)
		params = parse_comma(parameters[2]);
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
						if (params.size() > 0 && i - 1 < params.size())
							ret = set_mode(sender, mode[i], params[i - 1]);
						else
							ret = set_mode(sender, mode[i]);
						if (ret > 0)
							send_message(*sender, build_command_message(sender->get_nickname(), "", get_name(), "MODE", parameters, params));
					} else {
						string_mode += mode[i];
						send_message(*sender, build_message2(472, *sender, string_mode, this));
						string_mode = "";
					}
				} else if (symbol == '-') {
					std::cout << "Channel mode = " << _channel_modes << std::endl;
					if (modes.find(mode[i]) != std::string::npos) {
						if (params.size() > 0 && i - 1 < params.size())
							ret = unset_mode(sender, mode[i], params[i - 1]);
						else
							ret = unset_mode(sender, mode[i]);
						if (ret > 0)
							send_message(*sender, build_command_message(sender->get_nickname(), "", get_name(), "MODE", parameters, params));
					} else {
						string_mode += mode[i];
						send_message(*sender, build_message2(472, *sender, string_mode, this));
						string_mode = "";
					}
				}
			}
		}
	} else
		send_message(*sender, _server->print_numerics(324, *sender, *sender, this, NULL));
}

void Channel::set_user_mode(Client *sender, char mode, std::string parameter) {
	std::map<Client*, std::string>::iterator it = _users.begin();
	for (; it != _users.end(); it++)
		if ((*it).first->get_nickname() == parameter)
			break;
	if (it == _users.end())
		send_message(*sender, build_message2(401, *sender, parameter, this));
	else {
		if (it->second.find(mode) == std::string::npos)
			it->second.push_back(mode);
	}
}

void Channel::unset_user_mode(Client *sender, char mode, std::string parameter) {
	std::map<Client*, std::string>::iterator it = _users.begin();
	for (; it != _users.end(); it++)
		if ((*it).first->get_nickname() == parameter)
			break;
	if (it == _users.end())
		send_message(*sender, build_message2(401, *sender, parameter, this));
	else {
		if (it->second.find(mode) != std::string::npos)
			it->second.erase(_channel_modes.find(mode), 1);
	}
}

void Channel::add_invite(std::string name) {
	std::vector<std::string>::iterator it = search_user_invite(name);

	if (it == _invite_list.end())
		_invite_list.push_back(name);
}

int Channel::remove_user(Client *client, std::vector<Channel*> *channels) {
	std::map<Client*, std::string>::iterator it;
	std::vector<Channel*>::iterator it2;
	std::vector<Channel*>::iterator chan_serv_it;

	for (it = _users.begin(); it != _users.end(); it++)
		if ((*it).first->get_nickname() == client->get_nickname())
			break ;
	_users.erase(it);
	client->get_channel().erase(client->get_channel_by_name(this->get_name()));
	if (_users.size() == 0) {
		for (it2 = channels->begin(); it2 != channels->end(); it2++)
			if ((*it2)->get_name() == get_name())
				break ;			
		if (it2 != channels->end()) {
			chan_serv_it = _server->get_channel(get_name());
			channels->erase(it2);
			delete *chan_serv_it;
		}
	}
	return (0);
}

void Channel::ban_user(std::string name) {
	std::vector<std::string>::iterator it = search_user_ban(name);

	if (_users_ban.end() == it)
		_users_ban.push_back(name);
}

void Channel::unban_user(std::string name) {
	std::vector<std::string>::iterator it = search_user_ban(name);

	if (_users_ban.end() != it)
		_users_ban.erase(it);
}

void Channel::print_users() {
	for (std::map<Client*, std::string>::iterator it = _users.begin(); it != _users.end(); it++)
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