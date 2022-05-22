
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
		server.get_clients().push_back(Client(fd));
	do
	{
		memset(&buffer, 0, sizeof(buffer));
		ret = recv(fd, buffer, sizeof(buffer), 0);
		server.get_clients()[i].append_buffer(buffer);
	}while(ret > 0);

	pos = server.get_clients()[i].get_buffer().rfind("\r\n");
	if (pos == -1 || pos >= server.get_clients()[i].get_buffer().length())
	{
		std::cout << "from fd: "<< fd << " command incomplete, storing: " << std::endl 
				<< server.get_clients()[i].get_buffer() << std::endl
				<< "--------------" << std::endl;
		return ret;
	}
	
	message = server.get_clients()[i].extract_command(pos);
	std::cout << "command:" << std::endl
			<< message 
			<< "--------------" << std::endl;
//AJOUTER CALL POUR LE PARSING
// do_parsing(Server &server, Client& expediteur, std::string message);
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
	int 				on = 1;
	int					ret;
	struct pollfd		fd;

	// Create an AF_INET (ipv4)stream socket to receive incoming connections on  
	server.set_serverFD(socket(AF_INET, SOCK_STREAM, 0));
	if (server.get_serverFD() < 0)
	{
		perror("socket() failed");
		return false;
	}

	// Allow socket descriptor to be reuseable  
	ret = setsockopt(server.get_serverFD(), SOL_SOCKET,  SO_REUSEADDR,
	(char *)&on, sizeof(on));
	if (ret < 0)
	{
		perror("setsockopt() failed");
		close(server.get_serverFD());
		return false;
	}

	// Set socket to be nonblocking. All of the sockets for 
	//    the incoming connections will also be nonblocking since  
	//   they will inherit that state from the listening socket.   
	ret = fcntl(server.get_serverFD(), F_SETFL, O_NONBLOCK);
	if (ret == -1)
	{
		perror("fcntl() failed");
		close(server.get_serverFD());
		return false;
	}

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(atoi(av[1]));


	//Bind the socket  
	ret = bind(server.get_serverFD(), (struct sockaddr *)&addr, sizeof(addr));
	if (ret < 0)
	{
		perror("bind() failed");
		close(server.get_serverFD());
		return false;
	}

	// Set the listen back log
	//second arg (32) is size of the listen backlog
	ret = listen(server.get_serverFD(), 32);
	if (ret == -1 )
	{
		perror("listen() failed");
		close(server.get_serverFD());
		return false;
	}

	//Initialize the pollfd structure  <<-- with vector not array
	memset(&fd, 0 , sizeof(fd));
	fd.fd = server.get_serverFD();
	fd.events = POLLIN;
	server.set_server_pollfd(fd);

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

	Server	server;
	bool	running = true;
	int		ret;

	if (!init_socket(server, av))
		return (-1);
	if (ac == 3)
	{
		server.set_using_password(true);
		server.set_password(av[2]);
	}
	else
		server.set_using_password(false);

	//main loop
	while (running)
	{
		std::cout << "Waiting on poll()..." << std::endl;
		ret = poll( , fds.size(), TIMEOUT);
	}

	// TODO clean all fd
	return 0;
}