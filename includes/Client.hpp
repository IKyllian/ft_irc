#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include "ft_irc.hpp"

class Client {
	public :
		Client();
		Client(std::string nickname);
		Client(const Client &client);
		Client(int &fd);
		~Client();

		bool operator==(const Client& rhs);
		bool operator<(const Client &other) const;

		std::string get_nickname() const;
		std::string get_username() const;
		std::string get_user_modes() const;
		int			get_fd() const;
		bool		get_logged() const;
		std::string	get_buffer() const;

		void set_nickname(std::string val);
		void set_username(std::string val);
		void set_user_modes(std::string mode);
		void set_fd(int &val);
		void set_logged(bool &val);
		void append_buffer(char* buffer);

		std::string extract_command(size_t pos);

	private :
		std::string _nickname;
		std::string _username;
		std::string _user_modes;
		int			_fd;
		bool		_logged;
		std::string	_buffer;
};

#endif