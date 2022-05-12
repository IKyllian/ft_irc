#include "../includes/Server.hpp"

std::string get_network_name() const { return (network_name); }
std::string get_hostname() const { return (hostname); }
std::string get_port() const { return (port); }
std::string get_infoServer() const { return (infoServer); }
std::string get_servername() const { return (servername); }
std::string get_locationServer() const { return (locationServer); }
std::string get_hostInfo() const { return (hostInfo); }
std::string get_hostMail() const { return (hostMail); }
std::string get_version() const { return (version); }
std::string get_token() const { return (token); }
std::string get_connexion() const { return (connexion); }
std::string get_nb_user() const { return (nb_user); }
std::string get_nb_clients() const { return (nb_clients); }
std::string get_nb_operator() const { return (nb_operator); }
std::string get_invisible_user() const { return (invisible_user); }
std::string get_server_connected() const { return (server_connected); }
std::string get_nb_channel() const { return (nb_channel); }
std::string get_datetime() const { return (datetime); }

void set_network_name(std::string &val) {
	network_name = val;
}

void set_hostname(std::string &val) {
	hostname = val;
}

void set_port(std::string &val) {
	port = val;
}

void set_infoServer(std::string &val) {
	infoServer = val;
}

void set_servername(std::string &val) {
	servername = val;
}

void set_locationServer(std::string &val) {
	locationServer = val;
}

void set_hostInfo(std::string &val) {
	hostInfo = val;
}

void set_hostMail(std::string &val) {
	hostMail = val;
}

void set_version(std::string &val) {
	version = val;
}

void set_token(std::string &val) {
	token = val;
}

void set_connexion(std::string &val) {
	onnexion = val;
}

void set_nb_user(std::string &val) {
	nb_user = val;
}

void set_nb_clients(std::string &val) {
	nb_clients = val;
}

void set_nb_operator(std::string &val) {
	nb_operator = val;
}

void set_invisible_user(std::string &val) {
	invisible_user = val;
}

void set_server_connected(std::string &val) {
	server_connected = val;
}

void set_nb_channel(std::string &val) {
	nb_channel = val;
}

void set_datetime(std::string &val) {
	datetime = val;
}
