#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>

class Client {
	public :
		Client();
		Client(const Client &client);
		~Client();

		std::string get_nickname() const;
		std::string get_username() const;
		std::string get_user_modes() const;
		int			get_fd() const;

		void set_nickname(std::string &val);
		void set_username(std::string &val);
		void set_user_modes(std::string &val);
		void set_fd(int &val);

	private :
		std::string nickname;
		std::string username;
		std::string user_modes;
		int			fd;
};

#endif