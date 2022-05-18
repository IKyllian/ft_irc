#include "../includes/Server.hpp"

std::string Server::get_network_name() const { return (network_name); }
std::string Server::get_hostname() const { return (hostname); }
std::string Server::get_port() const { return (port); }
std::string Server::get_infoServer() const { return (infoServer); }
std::string Server::get_servername() const { return (servername); }
std::string Server::get_locationServer() const { return (locationServer); }
std::string Server::get_hostInfo() const { return (hostInfo); }
std::string Server::get_hostMail() const { return (hostMail); }
std::string Server::get_version() const { return (version); }
std::string Server::get_token() const { return (token); }
std::string Server::get_connexion() const { return (connexion); }
std::string Server::get_nb_user() const { return (nb_user); }
std::string Server::get_nb_clients() const { return (nb_clients); }
std::string Server::get_nb_operator() const { return (nb_operator); }
std::string Server::get_invisible_user() const { return (invisible_user); }
std::string Server::get_server_connected() const { return (server_connected); }
std::string Server::get_nb_channel() const { return (nb_channel); }
std::string Server::get_datetime() const { return (datetime); }

void Server::set_network_name(std::string &val) {
	network_name = val;
}

void Server::set_hostname(std::string &val) {
	hostname = val;
}

void Server::set_port(std::string &val) {
	port = val;
}

void Server::set_infoServer(std::string &val) {
	infoServer = val;
}

void Server::set_servername(std::string &val) {
	servername = val;
}

void Server::set_locationServer(std::string &val) {
	locationServer = val;
}

void Server::set_hostInfo(std::string &val) {
	hostInfo = val;
}

void Server::set_hostMail(std::string &val) {
	hostMail = val;
}

void Server::set_version(std::string &val) {
	version = val;
}

void Server::set_token(std::string &val) {
	token = val;
}

void Server::set_connexion(std::string &val) {
	connexion = val;
}

void Server::set_nb_user(std::string &val) {
	nb_user = val;
}

void Server::set_nb_clients(std::string &val) {
	nb_clients = val;
}

void Server::set_nb_operator(std::string &val) {
	nb_operator = val;
}

void Server::set_invisible_user(std::string &val) {
	invisible_user = val;
}

void Server::set_server_connected(std::string &val) {
	server_connected = val;
}

void Server::set_nb_channel(std::string &val) {
	nb_channel = val;
}

void Server::set_datetime(std::string &val) {
	datetime = val;
}
