#include "../includes/Client.hpp"
#include "../includes/Server.hpp"
#include "../includes/ft_irc.hpp"

#include <sys/types.h>
#include <sys/socket.h>
#include <string>
#include <sstream>
#include <cstring>


bool send_message(Server &server, Message &msg_data, std::string header, std::string message, std::string msgnum)
{
	int					ret, len;
	char				buffer[65535];
	std::string			str;
	// std::stringstream	ss;

	// ss << msgnum;


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