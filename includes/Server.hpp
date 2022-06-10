#ifndef SERVER_HPP
#define SERVER_HPP

#include <set>
#include <iostream>
#include <vector>
#include "Message.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "ft_irc.hpp"


class Channel;
class Client;
class Message;
class Command;

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
		// std::string get_token() const;
		// std::string get_connexion() const;
		// std::string get_nb_user() const;
		// std::string get_nb_clients() const;
		std::string get_nb_operator() const;
		std::string get_invisible_user() const;
		// std::string get_server_connected() const;
		// std::string get_nb_channel() const;
		// std::string get_datetime() const;

		std::vector<Client>	&get_clients();
		std::vector<Client>::iterator get_client(std::string to_search);
		std::vector<Channel> &get_channels();
		std::vector<Channel>::iterator get_channel(std::string to_search);
		std::vector<Command> &get_commands();
		std::vector<struct pollfd> &get_fds();
		std::string get_password() const;
		bool get_using_password() const;
		int get_server_fd() const;

		void set_network_name(std::string val);
		void set_hostname(std::string val);
		void set_port(std::string val);
		void set_infoServer(std::string &val);
		void set_servername(std::string val);
		void set_locationServer(std::string val);
		void set_hostInfo(std::string val);
		void set_hostMail(std::string val);
		void set_version(std::string val);
		//void set_token(std::string &val);
		//void set_connexion(std::string &val);
		//void set_nb_user(std::string &val);
		//void set_nb_clients(std::string &val);
		void set_nb_operator(std::string &val);
		void set_invisible_user(std::string &val);
		//void set_server_connected(std::string &val);
		//void set_nb_channel(std::string &val);
		//void set_datetime(std::string &val);

		void set_password(std::string val);
		void set_using_password(bool val);
		void set_user(Client client);

		
		
		std::string print_numerics(int num, Client &sender, Client &receiver, Channel *channel = NULL, Message *message = NULL);


		void command_NICK(Client &client, Message &message);
		void command_USER(Client &client, Message &message);
		void command_PASSWORD(Client &client, Message &message);

		// void command_JOIN(Client *client, std::vector<std::string> parameters);
		void command_JOIN(Client *client, Message &message, Server &server);

		// void command_PART(Client *client, std::vector<std::string> parameters);
		void command_PART(Client *client, Message &message);

		// void command_TOPIC(Client *client, std::vector<std::string> parameters);
		void command_TOPIC(Client *client, Message &message);

		// void command_NAMES(std::vector<std::string> parameters);
		void command_NAMES(Message &message);

		// void command_LIST(std::vector<std::string> parameters);
		void command_LIST(Message &message);

		// void command_INVITE(Client *sender, std::vector<std::string> parameters);
		void command_INVITE(Client *sender, Message &message);

		// void command_KICK(Client *sender, std::vector<std::string> parameters);
		void command_KICK(Client *sender, Message &message);

		// void command_MODE_CHAN(Client *sender, std::vector<std::string> parameters);
		void command_MODE_CHAN(Client *sender, Message &message);

		// void command_MODE_USER(Client *sender, std::vector<std::string> parameters);
		void command_MODE_USER(Client *sender, Message &message);

		void command_AWAY(Client &client, Message &message);
		void command_HELP(Client &sender, Message &msg);
		void command_PRIVMSG(Client &sender, Message &msg);
		void command_WHO(Client &client, Message &message);
		void command_WHOIS(Client &client, Message &message);

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
		std::vector<Command>		_commands;
		std::vector<struct pollfd>	_fds;
		std::string					_password;
		bool						_using_password;
		
		bool _nick_available(std::string nick) const;
		bool _nick_isvalid(std::string nick) const;
};

bool send_message(Server &server, Message &msg_data, std::string header, std::string message, std::string msgnum);
bool send_message(Client &client, std::string message);

#endif