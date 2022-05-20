#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <map>
#include <vector>
#include <iostream>
#include "Client.hpp"
#include "ft_irc.hpp"

class Channel {
	public :
		Channel();
		Channel(std::string &name);
		Channel(const Channel &channel);
		~Channel();

		std::vector<Client*>::iterator search_user_invite(Client *client);
		std::vector<Client*>::iterator search_user_ban(Client *client);

		std::string get_name() const;
		std::map<Client*, std::string> &get_users() ;
		std::vector<Client*> &get_users_ban();
		std::vector<Client*> &get_invite_list();
		std::map<Client*, std::string>::iterator get_user(Client* client);
		std::string get_channel_modes() const;
		
		void set_name(std::string val);
		void set_user(Client *client);
		void set_channel_modes(std::string mode);
		void set_user_mode(std::string mode, Client *client);
		void add_invite(Client *client);
		
		void remove_user(Client *client);
		void remove_invite(Client *client);
		void ban_user(Client *client);

		void print_users();

	private :
		std::string name;
		std::map<Client*, std::string> users; // Stock Client et les modes du user sur le channel
		std::string channel_modes;
		std::vector<Client*> users_ban;
		std::vector<Client*> invite_list;
};

#endif