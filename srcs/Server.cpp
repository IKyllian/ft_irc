#include "../includes/Server.hpp"
// #include "../includes/Message.hpp"
// #include "../includes/ft_irc.hpp"

Server::Server() {}

Server::Server(const Server &server):
	_network_name(server._network_name),
	_hostname(server._hostname),
	_port(server._port),
	_infoServer(server._infoServer),
	_servername(server._servername),
	_locationServer(server._locationServer), 
	_hostInfo (server._hostInfo),
	_hostMail(server._hostMail),
	_version (server._version),
	_token(server._token),
	_connexion(server._connexion),
	_nb_user (server._nb_user),
	_nb_clients (server._nb_clients),
	_nb_operator (server._nb_operator),
	_invisible_user (server._invisible_user),
	_server_connected(server._server_connected),
	_nb_channel(server._nb_channel),
	_datetime (server._datetime)
{
}

Server::~Server() {}




std::string Server::get_network_name() const { return (_network_name); }
std::string Server::get_hostname() const { return (_hostname); }
std::string Server::get_port() const { return (_port); }
std::string Server::get_infoServer() const { return (_infoServer); }
std::string Server::get_servername() const { return (_servername); }
std::string Server::get_locationServer() const { return (_locationServer); }
std::string Server::get_hostInfo() const { return (_hostInfo); }
std::string Server::get_hostMail() const { return (_hostMail); }
std::string Server::get_version() const { return (_version); }
std::string Server::get_token() const { return (_token); }
std::string Server::get_connexion() const { return (_connexion); }
std::string Server::get_nb_user() const { return (_nb_user); }
std::string Server::get_nb_clients() const { return (_nb_clients); }
std::string Server::get_nb_operator() const { return (_nb_operator); }
std::string Server::get_invisible_user() const { return (_invisible_user); }
std::string Server::get_server_connected() const { return (_server_connected); }
std::string Server::get_nb_channel() const { return (_nb_channel); }
std::string Server::get_datetime() const { return (_datetime); }

std::vector<Client>	&Server::get_clients() { return (_clients); }
std::vector<Channel> &Server::get_channels() { return (_channels); }
std::vector<struct pollfd> &Server::get_fds() { return (_fds); };
std::string Server::get_password() const { return (_password); }
bool Server::get_using_password() const { return (_using_password); }
int Server::get_server_fd() const { return (_fds[0].fd); }

void Server::set_network_name(std::string &val) {
	_network_name = val;
}

void Server::set_hostname(std::string &val) {
	_hostname = val;
}

void Server::set_port(std::string &val) {
	_port = val;
}

void Server::set_infoServer(std::string &val) {
	_infoServer = val;
}

void Server::set_servername(std::string &val) {
	_servername = val;
}

void Server::set_locationServer(std::string &val) {
	_locationServer = val;
}

void Server::set_hostInfo(std::string &val) {
	_hostInfo = val;
}

void Server::set_hostMail(std::string &val) {
	_hostMail = val;
}

void Server::set_version(std::string &val) {
	_version = val;
}

void Server::set_token(std::string &val) {
	_token = val;
}

void Server::set_connexion(std::string &val) {
	_connexion = val;
}

void Server::set_nb_user(std::string &val) {
	_nb_user = val;
}

void Server::set_nb_clients(std::string &val) {
	_nb_clients = val;
}

void Server::set_nb_operator(std::string &val) {
	_nb_operator = val;
}

void Server::set_invisible_user(std::string &val) {
	_invisible_user = val;
}

void Server::set_server_connected(std::string &val) {
	_server_connected = val;
}

void Server::set_nb_channel(std::string &val) {
	_nb_channel = val;
}

void Server::set_datetime(std::string &val) {
	_datetime = val;
}

void Server::set_password(std::string val) {
	_password = val;
}

void Server::set_using_password(bool val) {
	_using_password = val;
}

void Server::command_JOIN(std::vector<std::string> parameters, Client *client) {
	std::vector<std::string>		channels_string;
	std::vector<std::string>		keys;
	std::vector<Channel>::iterator	it;

	channels_string = parse_comma(parameters[0]);
	if (parameters.size() > 1)
		keys = parse_comma(parameters[1]);
	for (size_t i = 0; i < channels_string.size(); i++) {
		for (it = _channels.begin(); it != _channels.end(); it++)
			if ((*it).get_name() ==  channels_string[i])
				break;
		if (it == _channels.end()) {
			_channels.push_back(Channel(channels_string[i]));
			it = _channels.begin();
			for (; it != _channels.end(); it++) {
				if ((*it).get_name() == channels_string[i])
					break;
			}
		}
		if (keys.size() - 1 > i) // A check
			(*it).set_user(client);
		else
			(*it).set_user(client, keys[i]);
		// if (keys.size() - 1 > i)
		// 	join_channel(_channels, client, channels_string[i]);
		// else
		// 	join_channel(_channels, client, channels_string[i], keys[i]);
	}
}

bool Server::_nick_available(std::string nick) const {
	for (unsigned long i = 0; i < _clients.size(); i++)
	{
		if (_clients[i].get_nickname() == nick)
			return false;
	}
	return true;
}

bool Server::_nick_isvalid(std::string nick) const {
	std::string valid = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789`|^_-{}[]\\";

	if (nick.find_first_not_of(valid) != std::string::npos)
		return false;
	return true;

}

void Server::command_NICK(Client &client, Message &message) {
std::cout << "message.get_tab_parameter()[0]" << message.get_tab_parameter()[0] << std::endl;
	std::string new_nick = message.get_tab_parameter()[0];
std::cout << "alive 1" << std::endl;
std::cout << "###inside command_NICK" << std::endl;
	if (message.get_tab_parameter().size() == 0)
	{
	    //    431    ERR_NONICKNAMEGIVEN
        //       ":No nickname given"
        //  - Returned when a nickname parameter expected for a
        //    command and isn't found.

		// send_message(*this, client, /* print numerics demander a Romain */, 431);

	}
	else if (!_nick_available(new_nick))
	{
		//    433    ERR_NICKNAMEINUSE
		//           "<nick> :Nickname is already in use"
		//      - Returned when a NICK message is processed that results
		//        in an attempt to change to a currently existing
		//        nickname.

		// send_message(*this, client, /* print numerics demander a Romain */, 433);

	}
	else if (!_nick_isvalid(new_nick))
	{
		//        432    ERR_ERRONEUSNICKNAME
        //       "<nick> :Erroneous nickname"
        //  - Returned after receiving a NICK message which contains
        //    characters which do not fall in the defined set.  See
        //    section 2.3.1 for details on valid nicknames.

		// send_message(*this, client, /* print numerics demander a Romain */, 432);
	}
	//else if (/* is restricted, demander a Kyllian pour les user modes*/)
	//{
		//    484    ERR_RESTRICTED
		//           ":Your connection is restricted!"
		//      - Sent by the server to a user upon connection to indicate
		//        the restricted nature of the connection (user mode "+r").
		// send_message(*this, client, /* print numerics demander a Romain */, 484);
	//}
	else 
	{
std::cout << "alive 2" << std::endl;
		//set nickname
		client.set_nickname(new_nick);

		    //    001    RPL_WELCOME
            //   "Welcome to the Internet Relay Network
            //    <nick>!<user>@<host>"
			std::string a = "<header>";
			std::string b = "Welcome to the Internet Relay Network <nick>!<user>@<host>";
			std::string c = "001";
	//	send_message(*this, message, a, b, c);
		send_message(*this, message, "<header>", "Welcome to the Internet Relay Network <nick>!<user>@<host>", "001");
		//send_message(); //for valid nick change
		//response
	}

	    //    437    ERR_UNAVAILRESOURCE
        //       "<nick/channel> :Nick/channel is temporarily unavailable"
        //  - Returned by a server to a user trying to join a channel
        //    currently blocked by the channel delay mechanism.
        //  - Returned by a server to a user trying to change nickname
        //    when the desired nickname is blocked by the nick delay
        //    mechanism.

		//        436    ERR_NICKCOLLISION
        //       "<nick> :Nickname collision KILL from <user>@<host>"
        //  - Returned by a server to a client when it detects a
        //    nickname collision (registered of a NICK that
        //    already exists by another server).



// "send_message
// (Server&,
// Message&,
// std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >,
// std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >,
// std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >)
// ", referenced from:


}


bool Server::send_message(Server &server, Message &msg_data, std::string header, std::string message, std::string msgnum)
{
	int					ret, len;
	char				buffer[65535];
	std::string			str;
	// std::stringstream	ss;
std::cout << "###inside send_message" << std::endl;
	// ss << msgnum;
(void) server;

	str = ":";
	str += header;
	str += " ";
	str += msgnum;
	str += " ";
	str += message;
	str += "\r\n";

    len = str.length();
	memset(&buffer, 0, sizeof(buffer));
	strcpy(buffer, str.c_str());
std::cout << "sending: " << std::endl;
std::cout << buffer << std::endl;
	ret = send(msg_data.get_receiver().get_fd(), buffer, len, 0);
	if (ret < 0)
	{
		perror("  send() failed");
		return false;
	}
	return true;
}