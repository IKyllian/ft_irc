
#include "../includes/Client.hpp"
#include "../includes/Channel.hpp"
#include "../includes/Server.hpp"

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
#include <cerrno>
#include <sstream>

#include <vector>
#include <map>
#include <cstdio>

#define TIMEOUT			180000 // 180000 = 3 minutes
//#define HOSTNAME		"kikaro.42.fr"


int handle_incoming_message(Server& server, int fd)
{
	int				ret;
	size_t			pos;
	unsigned long	i;
	char			buffer[65535];
	std::string		message;

	for (i = 0; i < server.get_clients().size(); i++)
	{
		if (fd == server.get_clients()[i].get_fd())
			break;
	}
	if (i == server.get_clients().size())
	{
		std::cout << "Client " << fd << " is new, adding to client list" << std::endl;
		server.get_clients().push_back(Client(fd));
	}
	do
	{
		memset(&buffer, 0, sizeof(buffer));
		ret = recv(fd, buffer, sizeof(buffer), 0);
		server.get_clients()[i].append_buffer(buffer);
	}while(ret > 0);

	pos = server.get_clients()[i].get_buffer().rfind("\r\n");
	if (pos == std::string::npos || pos >= server.get_clients()[i].get_buffer().length())
	{
		std::cout << "from fd: "<< fd << " command incomplete, storing: " << std::endl 
				<< server.get_clients()[i].get_buffer() << std::endl
				<< "--------------" << std::endl;
		return ret;
	}
	
	message = server.get_clients()[i].extract_command(pos);

	// for (unsigned long k = 0; k < message.length(); k++)
	// {
	// 	std::cout << "i: " << k << " message[k]: " << message[k] << " (int): " << (int) message[k] << std::endl;
	// }
	std::cout << "command:" << std::endl
			<< message << std::endl;
	std::cout << "--------------" << std::endl;

	//AJOUTER CALL POUR LE PARSING
    std::string tmp = message;
	message += "\n";
	do_parsing(server, server.get_clients()[i], message);
	// do_parsing(server, server.get_clients()[i], message);
	return ret;
}

void display_cpp_ver()
{
	std::cout << "Check CPP Version: ";
    if (__cplusplus == 201703L) std::cout << "C++17\n";
    else if (__cplusplus == 201402L) std::cout << "C++14\n";
    else if (__cplusplus == 201103L) std::cout << "C++11\n";
    else if (__cplusplus == 199711L) std::cout << "C++98\n";
    else std::cout << "pre-standard C++\n";
}


bool init_socket(Server &server, char** av)
{
	struct sockaddr_in	addr;
	int 				on = 1; //TODO learn more about on
	int					ret, serverFD;
	struct pollfd		fd;

	// Create an AF_INET (ipv4)stream socket to receive incoming connections on  
	serverFD = socket(AF_INET, SOCK_STREAM, 0);
	if (serverFD < 0)
	{
		perror("socket() failed");
		return false;
	}

	// Allow socket descriptor to be reuseable  
	ret = setsockopt(serverFD, SOL_SOCKET,  SO_REUSEADDR,
	(char *)&on, sizeof(on));
	if (ret < 0)
	{
		perror("setsockopt() failed");
		close(serverFD);
		return false;
	}

	// Set socket to be nonblocking. All of the sockets for 
	//    the incoming connections will also be nonblocking since  
	//   they will inherit that state from the listening socket.   
	ret = fcntl(serverFD, F_SETFL, O_NONBLOCK);
	if (ret == -1)
	{
		perror("fcntl() failed");
		close(serverFD);
		return false;
	}

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(atoi(av[1]));

	//Bind the socket  
	ret = bind(serverFD, (struct sockaddr *)&addr, sizeof(addr));
	if (ret < 0)
	{
		perror("bind() failed");
		close(serverFD);
		return false;
	}

	// Set the listen back log
	//second arg (32) is size of the listen backlog
	ret = listen(serverFD, 32);
	if (ret == -1 )
	{
		perror("listen() failed");
		close(serverFD);
		return false;
	}

	//Initialize the pollfd structure  <<-- with vector not array
	memset(&fd, 0 , sizeof(fd));
	fd.fd = serverFD;
	fd.events = POLLIN;
	server.get_fds().push_back(fd);

	return true;
}

bool init_server(Server &server, int ac, char** av)
{
	if (ac == 3)
	{
		server.set_using_password(true);
		server.set_password(av[2]);
	}
	else
		server.set_using_password(false);

	server.set_hostname(HOST_NAME);
	server.set_network_name(NETWORK_NAME);
	server.set_port(av[1]);
	return true;	
}


int main(int ac, char **av)
{
	display_cpp_ver();

	if (ac < 2 || ac > 3)
	{
		std::cout << "Wrong number of Arguments" << std::endl;
		return (0);
	}

	Server			server;
	bool			running = true;
	bool			removeFD = false;
	int				ret;
	struct pollfd	fd;
	unsigned long	i, j;

	if (!init_socket(server, av))
		return (-1);
	init_server(server, ac, av);

	while (running)
	{
		std::cout << "Waiting on poll()..." << std::endl;
		ret = poll( &server.get_fds()[0], server.get_fds().size(), TIMEOUT);

		if (ret < 0)
		{
			perror("  poll() failed");
			break;
		}
		if (ret == 0)
		{
			std::cerr << "poll() timed out.  End program." << std::endl;
			break;
		}

		for (i = 0; i < server.get_fds().size(); i++)
		{
			if(server.get_fds()[i].revents == 0)
				continue;

			if(server.get_fds()[i].revents != POLLIN)
			{
				// Error! revents = 17
				// connection severed
				std::cerr << "Error! revents = " << server.get_fds()[i].revents << std::endl;

				if (i == 0)
				{
					running = false;
					break;
				}
				removeFD = true;
				break;
			}

			if (i == 0) // server fd
			{
				while (true)
				{
					memset(&fd, 0 , sizeof(fd));
					fd.fd = accept(server.get_server_fd(), NULL, NULL);
					if (fd.fd < 0)
					{
						if (errno != EWOULDBLOCK)
						{
							perror("  accept() failed");
							running = false;
						}
						break;
					}
					std::cout << "New incomig connection: " << fd.fd << std::endl;
					fd.events = POLLIN;
					server.get_fds().push_back(fd);
				}
			}
			else // client fd
			{
				std::cout << "Descriptor " << server.get_fds()[i].fd << " is readable" << std::endl;
				while (true)
				{		
					ret = handle_incoming_message(server, server.get_fds()[i].fd);
					if (ret <= 0)
					{
						//EWOULDBLOCK 35
						if (errno == EWOULDBLOCK)
							break;
						removeFD = true;
						break;
					}
				} //end while reading incoming message		
			}
		} // end checking all fds in pollfd vector

		if (removeFD)
		{
			removeFD = false;
			std::cout << "Closing fd " << server.get_fds()[i].fd << std::endl;
			for (j = 0; j < server.get_clients().size(); j++)
			{
				if (server.get_fds()[i].fd == server.get_clients()[j].get_fd())
				{
					std::cout << "Removing Client: " << server.get_clients()[j].get_fd() << std::endl;
					server.get_clients().erase(server.get_clients().begin() + j);
					//TODO faire des trucs ? (enlever le user des channels ?)
					break;
				}
			}
			close(server.get_fds()[i].fd);
			server.get_fds().erase(server.get_fds().begin() + i);
		}
	} // end main loop
	std::cout << "Closing all remaining fd" << std::endl;
	for (i = 0; i < server.get_fds().size(); i++)
	{
		if(server.get_fds()[i].fd >= 0)
			close(server.get_fds()[i].fd);
	}
	return 0;
}