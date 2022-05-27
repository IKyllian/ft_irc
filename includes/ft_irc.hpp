#ifndef		FT_IRC_HPP
# define	FT_IRC_HPP

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

//                                             Class HPP                                                   //
#include "Channel.hpp"
#include "Client.hpp"
#include "Message.hpp"
#include "Server.hpp"

//                                              OTHERS                                                   //

#include "numerics.hpp"

std::string                 ft_print_numerics(/*User &user, Server &server, Channel &channel, Message &message*/ int nb_message)
Message                     *ft_create_message(std::string str);
std::vector<std::string>    ft_split_message(std::string str);
void                        do_parsing(Server &server, Client& expediteur, std::string message);

#endif