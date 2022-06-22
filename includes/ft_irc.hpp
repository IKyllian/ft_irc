#ifndef		FT_IRC_HPP
# define	FT_IRC_HPP

//                                              DEFINES                                                   //

#define NETWORK_NAME "KIKIKAKARORO"
#define HOST_NAME "kikaro.42.fr"
#define SERVER_NAME "Delire"
#define VERSION "1.0"
#define SERVER_LOCATION "Lyon 42 Charbounnière"
#define SERVER_LOCATION2 "78 Rte de Paris"
#define HOSTMAIL "skritch@jemenbatlescouilles.fr"
#define TIMEOUT	1800000 // 180000 = 3 minutes
//											LIBRAIRIE RÉSEAU											//

#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <istream>

#include <poll.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#include <iostream>
#include <string>
#include <set>
#include <map>
#include <cerrno>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <cstdio>

//                                             Class HPP                                                   //
#include "Channel.hpp"
#include "Client.hpp"
#include "Message.hpp"
#include "Server.hpp"

//                                              OTHERS                                                   //

#include "numerics.hpp"

class Server;
class Channel;
class Message;
class Server;

std::vector<std::string> parse_comma(std::string parameter);
Message                     *ft_create_message(std::string str);
void                        ft_split_parameter(Message &msg);
std::vector<std::string>    ft_split_message(std::string str);
void                        do_parsing(Server &server, Client *sender, std::string message);
std::string build_command_message(std::string sender, std::string receiver, std::string target, std::string command, std::vector<std::string> message = std::vector<std::string>(), std::string params = std::string());

bool send_message(Server &server, Message &msg_data, std::string header, std::string message, std::string msgnum);
bool send_message(Client &client, std::string message);
std::string build_message2(int num, Client &sender, std::string target, Channel *channel = NULL);

#endif