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
//											LIBRAIRIE RÉSEAU											//

#include <sys/socket.h>			// Socket Pour Linux/Mac
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <istream>

#include <poll.h>					// N'existe pas pour Windows, il faut utiliser select pour Windows...
//#include <winsock2.h>				//Pour Windows, ça fonctionne pas D:
//#include <ws2def.h>				//Pour Windows, ça fonctionne pas D:
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

//											  LIBRAIRIE C++												//

#include <iostream>
#include <string>
#include <cerrno>
#include <vector>
#include <cstdlib>
#include <sstream>

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

std::string                 ft_print_numerics(/*User &user, Server &server, Channel &channel, Message &message*/ int nb_message);
Message                     *ft_create_message(std::string str);
void                        ft_split_parameter(Message &msg);
std::vector<std::string>    ft_split_message(std::string str);
void                        do_parsing(Server &server, Client *sender, std::string message);
std::string build_command_message(std::string sender, std::string receiver, std::string target, std::string command, std::vector<std::string> message = std::vector<std::string>(), std::string params = std::string());


//bool send_message(Server &server, Client &receiver, std::string message, int msgnum);

// bool						send_message(Server &server, Message &msg_data, std::string header, std::string message, std::string msgnum);
// bool						send_message(Client &target, std::string message);
#endif