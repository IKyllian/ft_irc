#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <map>
#include <vector>
#include <iostream>
#include "Client.hpp"
#include "ft_irc.hpp"
#include <sstream> // pour convertir string en int 

class Channel {
	public :
		Channel();
		Channel(std::string &name);
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
		int get_user_limit() const;
		
		void set_name(std::string val);
		void set_user(Client *client, std::string key);
		void set_channel_modes(std::string mode, std::vector<std::string> parameters);
		void set_mode(char mode, std::string parameter = std::string());
		void set_user_mode(char mode, std::string parameter);
		void add_invite(Client *client);
		void set_password(std::string password = std::string());
		void set_user_limit(int limit);
		
		void remove_user(Client *client);
		void remove_invite(Client *client);
		void ban_user(Client *client);
		void unban_user(Client *client);
		void unset_mode(char mode, std::string parameter = std::string());
		void unset_user_mode(char mode, std::string parameter);

		void print_users();

	private :
		std::string name;
		std::string password;
		size_t user_limit;
		std::map<Client*, std::string> users; // Stock Client et les modes du user sur le channel
		std::string channel_modes;
		std::vector<Client*> users_ban;
		std::vector<Client*> invite_list;
};

std::vector<std::string> parse_comma(std::string parameter);
void join_command(std::vector<std::string> parameters, std::vector<Channel> *channels, Client *client);
void join_channel(std::vector<Channel> *channels, Client *client, std::string channel, std::string key = std::string());

#endif