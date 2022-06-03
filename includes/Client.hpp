#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include "ft_irc.hpp"

class Channel;

class Client {
	public :
		Client();
		Client(std::string nickname);
		Client(const Client &client);
		Client(int &fd);
		~Client();

		bool operator==(const Client& rhs);
		// bool operator<(const Client &other) const;

		std::string get_nickname() const;
		std::string get_username() const;
		std::string get_user_modes() const;
		int			get_fd() const;
		bool		get_logged() const;
		bool		get_hasnick() const;
		bool 		get_away() const;
		std::string get_away_msg() const;
		std::string	get_buffer() const;
		std::vector<Channel*>	&get_channel();

		void set_nickname(std::string val);
		void set_username(std::string val);
		void set_user_modes(std::string mode);
		void set_fd(int &val);
		void set_logged(bool &val);
		void set_hasnick(bool &val);
		void set_away(bool val);
		void set_away_msg(std::string msg);
		void append_buffer(char* buffer);

		std::string extract_command(size_t pos);

	private :
		std::vector<Channel*> _channel;
		std::string _nickname;
		std::string _username;
		std::string _user_modes;
		int			_fd;
		bool		_logged;
		bool		_hasnick;
		bool 		_away;
		std::string	_away_msg;
		std::string	_buffer;
};

#endif