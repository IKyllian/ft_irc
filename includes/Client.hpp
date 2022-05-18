#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>

class Client {
	public :
		Client();
		Client(const Client &client);
		Client(int &fd);
		~Client();

		std::string get_nickname() const;
		std::string get_username() const;
		std::string get_user_modes() const;
		int			get_fd() const;
		bool		get_logged() const;

		void set_nickname(std::string &val);
		void set_username(std::string &val);
		void set_user_modes(std::string &val);
		void set_fd(int &val);
		void set_logged(bool &val);

	private :
		std::string _nickname;
		std::string _username;
		std::string _user_modes;
		int			_fd;
		bool		_logged;
};

#endif