#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <map>
#include <vector>
#include <iostream>
#include "Client.hpp"
#include "ft_irc.hpp"
#include "Server.hpp"
#include "Message.hpp"
#include <sstream> // pour convertir string en int 

class Client;
class Message;
class Server;

class Channel {
	public :
		Channel();
		Channel(std::string &name,Server *server);
		Channel(const Channel &channel);
		~Channel();

		Channel& operator=(const Channel& rhs);

		std::vector<std::string>::iterator search_user_invite(std::string name);
		std::vector<std::string>::iterator search_user_ban(std::string name);
		std::vector<std::string>::iterator search_mode_argument(std::string arg);

		std::string get_name() const;
		std::map<Client*, std::string> &get_users();
		std::vector<std::string> &get_users_ban();
		std::vector<std::string> &get_invite_list();
		std::map<Client*, std::string>::iterator get_user(Client* client);
		std::string get_channel_modes() const;
		std::string get_mode_arguments() const;
		std::string get_password() const;
		std::string get_topic() const;
		int get_user_limit() const;
		Server& get_server() const;
		
		void 	set_name(std::string val);
		void 	set_user(Client *client, Message &message, std::string key = std::string());
		void 	set_channel_modes(Client *sender, std::vector<std::string> parameters);
		int 	set_mode(Client *sender, char mode, std::string parameter = std::string());
		void 	set_user_mode(Client *sender, char mode, std::string parameter);
		void	add_invite(std::string name);
		void 	set_password(std::string password = std::string());
		void 	set_topic(std::string new_topic = std::string());
		void 	set_user_limit(int limit);
		void 	set_server(Server *server);
		
		int 	remove_user(Client *client, std::vector<Channel*> *channels);
		void 	ban_user(std::string name);
		void 	unban_user(std::string name);
		int 	unset_mode(Client *sender, char mode, std::string parameter = std::string());
		void 	unset_user_mode(Client *sender, char mode, std::string parameter);
		void 	erase_mode_arguments(char mode);
		void 	add_mode_arguments(char mode, std::string parameter);
		void 	print_users();

	private :
		std::string _name;
		std::string _password;
		size_t _user_limit;
		std::string topic;
		std::map<Client*, std::string> _users;
		std::string _channel_modes;
		std::string _mode_arguments;
		std::vector<std::string> _users_ban;
		std::vector<std::string> _invite_list;
		Server *_server;
};

std::vector<std::string> parse_comma(std::string parameter);

#endif