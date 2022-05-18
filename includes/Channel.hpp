#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <map>
#include <iostream>
#include "Client.hpp"
#include "ft_irc.hpp"

class Channel {
	public :
		Channel();
		Channel(std::string &name);
		Channel(const Channel &channel);
		~Channel();

		std::string get_name() const;
		std::map<Client&, std::string> &get_users() ;
		std::map<Client&, std::string>::iterator get_user(Client& client);
		std::string get_channel_modes() const;
		
		void set_name(std::string val);
		void set_users(Client &user);
		void set_channel_modes(std::string mode);
		void set_user_mode(std::string mode, Client &client);
		
		void remove_user(std::string username);

	private :
		std::string name;
		std::map<Client&, std::string> users; // Stock username et les modes du user sur le channel
		std::string channel_modes;
};

#endif