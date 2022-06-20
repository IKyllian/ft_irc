#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include "ft_irc.hpp"

class Channel;
class Server;

class Client {
	public :
		Client();
		Client(std::string nickname);
		Client(const Client &client);
		Client(int &fd);
		~Client();

		bool operator==(const Client& rhs);

		std::string get_nickname() const;
		std::string get_username() const;
		std::string get_realname() const;
		std::string get_hostname() const;
		std::string get_fullidentity() const;
		std::string get_user_modes() const;
		int			get_fd() const;
		bool		get_logged() const;
		bool		get_registered() const;
		bool		get_authentified() const;
		bool		get_hasnick() const;
		bool 		get_away() const;
		bool		get_quitting() const;
		std::string get_away_msg() const;
		std::string	get_buffer() const;
		std::vector<Channel*>	&get_channel();
		std::vector<Channel*>::iterator	get_channel_by_name(std::string name);

		void set_nickname(std::string val);
		void set_username(std::string val);
		void set_realname(std::string val);
		void set_hostname(std::string val);
		void set_user_modes(std::string mode, Server &server);
		void set_fd(int val);
		void set_logged(bool val);
		void set_registered(bool val);
		void set_authentified(bool val);
		void set_hasnick(bool val);
		void set_away(bool val);
		void set_quitting(bool val);
		void set_away_msg(std::string msg);
		void append_buffer(char* buffer);

		std::string extract_command(size_t pos);

	private :
		std::vector<Channel*> _channel;
		std::string _nickname;
		std::string _username;
		std::string _realname;
		std::string _hostname;
		std::string _user_modes;
		int			_fd;
		bool		_logged; // USER + NICK (+ PASSWORD) set
		bool		_registered; //USER is set
		bool		_authentified; //PASSWORD is set
		bool		_hasnick; //NICK is set
		bool 		_away;
		bool		_quitting;
		std::string	_away_msg;
		std::string	_buffer;
};

#endif