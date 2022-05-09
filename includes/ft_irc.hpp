#ifndef		FT_IRC_HPP
# define	FT_IRC_HPP

//											LIBRAIRIE RÉSEAU											//

//#include <sys/socket.h>			// Socket Pour Linux/Mac
//#include <netdb.h>
//#include <arpa/inet.h>
//#include <netinet/in.h>
//#include <poll.h>					// N'existe pas pour Windows, il faut utiliser select pour Windows...
#include <WinSock2.h>				//Pour Windows
#include <ws2def.h>					//Pour Windows
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

//											LIBRAIRIE C++												//

#include <iostream>
#include <string>

#endif