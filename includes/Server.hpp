#ifndef SERVER_HPP
#define SERVER_HPP

#include <set>
#include <iostream>
#include <vector>
#include "Client.hpp"
#include "Channel.hpp"

class Server {
	public :
		Server();
		Server(const Server &server);
		~Server();

		std::string get_network_name() const;
		std::string get_hostname() const;
		std::string get_port() const;
		std::string get_infoServer() const;
		std::string get_servername() const;
		std::string get_locationServer() const;
		std::string get_hostInfo() const;
		std::string get_hostMail() const;
		std::string get_version() const;
		std::string get_token() const;
		std::string get_connexion() const;
		std::string get_nb_user() const;
		std::string get_nb_clients() const;
		std::string get_nb_operator() const;
		std::string get_invisible_user() const;
		std::string get_server_connected() const;
		std::string get_nb_channel() const;
		std::string get_datetime() const;

		std::vector<Client>	&get_clients();
		std::vector<Channel> &get_channels();
		std::vector<struct pollfd> &get_fds();
		std::string get_password() const;
		bool get_using_password() const;
		int get_server_fd() const;

		void set_network_name(std::string &val);
		void set_hostname(std::string &val);
		void set_port(std::string &val);
		void set_infoServer(std::string &val);
		void set_servername(std::string &val);
		void set_locationServer(std::string &val);
		void set_hostInfo(std::string &val);
		void set_hostMail(std::string &val);
		void set_version(std::string &val);
		void set_token(std::string &val);
		void set_connexion(std::string &val);
		void set_nb_user(std::string &val);
		void set_nb_clients(std::string &val);
		void set_nb_operator(std::string &val);
		void set_invisible_user(std::string &val);
		void set_server_connected(std::string &val);
		void set_nb_channel(std::string &val);
		void set_datetime(std::string &val);

		void set_password(std::string val);
		void set_using_password(bool val);

		void command_JOIN(std::vector<std::string> parameters, Client *client);

	private :
		std::string _network_name;
		std::string _hostname;
		std::string _port;
		std::string _infoServer;
		std::string _servername;
		std::string _locationServer;
		std::string _hostInfo;
		std::string _hostMail;
		std::string _version;
		std::string _token;
		std::string _connexion;
		std::string _nb_user;
		std::string _nb_clients;
		std::string _nb_operator;
		std::string _invisible_user;
		std::string _server_connected;
		std::string _nb_channel;
		std::string _datetime;

		std::vector<Client>			_clients;
		std::vector<Channel>		_channels;
		std::vector<struct pollfd>	_fds;
		std::string					_password;
		bool						_using_password;
};

#endif