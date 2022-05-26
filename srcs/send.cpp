#include "../includes/Client.hpp"
#include "../includes/Server.hpp"

#include <sys/types.h>
#include <sys/socket.h>
#include <string>
#include <sstream>
#include <cstring>


bool send_message(Server &server, Client &receiver, std::string message, int msgnum)
{
	int					ret, len;
	char				buffer[65535];
	std::string			str;
	std::stringstream	ss;

	ss << msgnum;

	str = ":";
	str += server.get_hostname(); 
	str += " ";
	str += ss.str();
	str += " ";
	str += message;
	//str += "\r\n";

    len = str.length();
	memset(&buffer, 0, sizeof(buffer));
	strcpy(buffer, str.c_str());

	ret = send(receiver.get_fd(), buffer, len, 0);
	if (ret < 0)
	{
		perror("  send() failed");
		return false;
	}
	return true;
}