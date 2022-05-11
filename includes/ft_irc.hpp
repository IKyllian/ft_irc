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

//											LIBRAIRIE C++												//

#include <iostream>
#include <string>
#include <cerrno>
#endif