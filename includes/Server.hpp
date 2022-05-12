#ifndef SERVER_HPP
#define SERVER_HPP

#include <set>

class Server {
	public :
		Server() {}
		Server(const Server &server);
		~Server() {}

		std::string get_network_name()
		std::string get_hostname()
		std::string get_port()
		std::string get_infoServer()
		std::string get_servername()
		std::string get_locationServer()
		std::string get_hostInfo()
		std::string get_hostMail()
		std::string get_version()
		std::string get_token()
		std::string get_connexion()
		std::string get_nb_user()
		std::string get_nb_clients()
		std::string get_nb_operator()
		std::string get_invisible_user()
		std::string get_server_connected()
		std::string get_nb_channel()
		std::string get_datetime()

		void set_network_name(std::string &val) const
		void set_hostname(std::string &val) const
		void set_port(std::string &val) const
		void set_infoServer(std::string &val) const
		void set_servername(std::string &val) const
		void set_locationServer(std::string &val) const
		void set_hostInfo(std::string &val) const
		void set_hostMail(std::string &val) const
		void set_version(std::string &val) const
		void set_token(std::string &val) const
		void set_connexion(std::string &val) const
		void set_nb_user(std::string &val) const
		void set_nb_clients(std::string &val) const
		void set_nb_operator(std::string &val) const
		void set_invisible_user(std::string &val) const
		void set_server_connected(std::string &val) const
		void set_nb_channel(std::string &val) const
		void set_datetime(std::string &val) const

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
};

#endif