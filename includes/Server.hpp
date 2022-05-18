#ifndef SERVER_HPP
#define SERVER_HPP

#include <set>
#include <iostream>
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
		std::vector<Client>		&get_clients() const;
		std::vector<Channel>	&get_channels() const;

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

	private :
		std::string network_name;
		std::string hostname;
		std::string port;
		std::string infoServer;
		std::string servername;
		std::string locationServer;
		std::string hostInfo;
		std::string hostMail;
		std::string version;
		std::string token;
		std::string connexion;
		std::string nb_user;
		std::string nb_clients;
		std::string nb_operator;
		std::string invisible_user;
		std::string server_connected;
		std::string nb_channel;
		std::string datetime;
		std::vector<Client>		clients;
		std::vector<Channel>	channels;
};

#endif