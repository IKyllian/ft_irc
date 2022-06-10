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

		bool operator==(const Channel &channel);

		std::vector<Client*>::iterator search_user_invite(Client *client);
		std::vector<Client*>::iterator search_user_ban(Client *client);

		std::string get_name() const;
		std::map<Client*, std::string> &get_users() ;
		std::vector<Client*> &get_users_ban();
		std::vector<Client*> &get_invite_list();
		std::map<Client*, std::string>::iterator get_user(Client* client);
		std::string get_channel_modes() const;
		std::string get_password() const;
		std::string get_topic() const;
		int get_user_limit() const;
		Server& get_server() const;
		
		void set_name(std::string val);
		void set_user(Client *client, Message &message, std::string key = std::string());
		void set_channel_modes(std::vector<std::string> parameters);
		void set_mode(char mode, std::string parameter = std::string());
		void set_user_mode(char mode, std::string parameter);
		void add_invite(Client *client);
		void set_password(std::string password = std::string());
		void set_topic(std::string new_topic = std::string());
		void set_user_limit(int limit);
		void set_server(Server *server);
		
		void remove_user(Client *client, std::vector<Channel> *channels);
		void remove_invite(Client *client);
		void ban_user(Client *client);
		void unban_user(Client *client);
		void unset_mode(char mode, std::string parameter = std::string());
		void unset_user_mode(char mode, std::string parameter);

		void print_users();

	private :
		std::string _name;
		std::string _password;
		size_t _user_limit;
		std::string topic;
		std::map<Client*, std::string> _users; // Stock Client et les modes du user sur le channel
		std::string _channel_modes;
		std::vector<Client*> _users_ban;
		std::vector<Client*> _invite_list;
		Server *_server;
};

std::vector<std::string> parse_comma(std::string parameter);

#endif