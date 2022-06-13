
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


void debug_print_client(Client &client)
{
	std::cout << std::boolalpha
	<< "nickname " << client.get_nickname() 
	// << " username " << client.get_username()
	// << " realname " << client.get_realname()
	// << " hostname " << client.get_hostname()
	// << " usermodes " << client.get_user_modes()
	<< " fd " << client.get_fd()
	// << " logged " << client.get_logged()
	// << " registered " << client.get_registered()
	// << " auth " << client.get_authentified()
	// << " has nick " << client.get_hasnick()
	// << " away " << client.get_away()
	<< " quitting " << client.get_quitting()
	// << " away msg " << client.get_away_msg()
	// << " buffer " << client.get_buffer()
	<< std::endl;
}

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
		std::cerr << "### Something went very wrong, client not in list ###" << std::endl;
	}

// 	if (i == server.get_clients().size())
// 	{
// 		std::cout << "Client " << fd << " is new, adding to client list" << std::endl;
// 		server.get_clients().push_back(Client(fd));

// struct sockaddr_in *addr_in = (struct sockaddr_in *)res;
// 		char *s = inet_ntoa(addr_in->sin_addr);
// 		char *s = inet_ntoa(server.get_fds()[i + 1].);
// printf("IP address: %s\n", s);
// 	}


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
	server.set_servername(SERVER_NAME);
	server.set_version(VERSION);
	server.set_locationServer(SERVER_LOCATION);
	server.set_hostInfo(SERVER_LOCATION2);
	server.set_hostMail(HOSTMAIL);
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
	//bool			removeFD = false;
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
				//removeFD = true;
				server.get_client_by_fd(server.get_fds()[i].fd)->set_quitting(true);
				break;
			}

			if (i == 0) // server fd
			{
				while (true)
				{
					struct sockaddr	addr;
					struct sockaddr_in *addr_in;
					socklen_t socklen = 0;
					char *s;

					memset(&fd, 0 , sizeof(fd));
//remplacer le check errno par un try/catch ?
					fd.fd = accept(server.get_server_fd(), &addr, &socklen);
//std::cout << "fd.fd: " << fd.fd << std::endl;
					if (fd.fd < 0)
					{

						// if (fd.fd == -1)
						// {
						// }
						// if (errno != EWOULDBLOCK)
						// {
						// 	perror("  accept() failed");
						// 	running = false;
						// }
						break;
					}
					std::cout << "New incomig connection: " << fd.fd << std::endl;
					fd.events = POLLIN;
					//send(fd.fd, ":127.0.0.1 001 kzennoun :Welcome to the Internet Relay Network nick!user@host\r\n", 79, 0);
					server.get_fds().push_back(fd);
					server.get_clients().push_back(Client(fd.fd));
debug_print_client(server.get_clients()[server.get_clients().size() - 1]); 
					addr_in = (struct sockaddr_in *)&addr;
					s = inet_ntoa(addr_in->sin_addr);
//std::cout << "hostname is: " << s << "|" << std::endl;
					server.get_clients()[server.get_clients().size() - 1].set_hostname(s);
std::cout << "hostname in class: " << server.get_clients()[server.get_clients().size() - 1].get_hostname() << "|" << std::endl;
// std::cout << std::boolalpha 
// << " register: " << server.get_clients()[server.get_clients().size() - 1].get_registered() << std::endl
// << " hasnick: " << server.get_clients()[server.get_clients().size() - 1].get_hasnick() << std::endl
// << " serv using pw: " << server.get_using_password() << std::endl
// << " client gave pw: " << server.get_clients()[server.get_clients().size() - 1].get_authentified() << std::endl
// << std::endl;
				}
			}
			else // client fd
			{
				std::cout << "Descriptor " << server.get_fds()[i].fd << " is readable" << std::endl;
				while (true)
				{	
std::cout << " start handle incoming message" << std::endl;	
					ret = handle_incoming_message(server, server.get_fds()[i].fd);
					if (ret <= 0)
					{
std::cout << "L306 ret: " << ret << std::endl;
						//EWOULDBLOCK 35
						if (ret == -1)
							break;
						// if (errno == EWOULDBLOCK)
						// 	break;
						//removeFD = true;
						//server.get_client_by_fd(server.get_fds()[i].fd)->set_fd(-1);
						server.get_client_by_fd(server.get_fds()[i].fd)->set_quitting(true);
						break;
					}
				} //end while reading incoming message		
			}
		} // end checking all fds in pollfd vector
			for (j = 0; j < server.get_clients().size(); j++)
			{
				if (server.get_clients()[j].get_quitting())
				{
					std::cout << "Removing Client: " << server.get_clients()[j].get_nickname() << std::endl;
//debug_print_client(server.get_clients()[j]);
					server.get_clients().erase(server.get_clients().begin() + j);
					//TODO faire des trucs ? (enlever le user des channels ?)
					std::cout << "Closing fd " << server.get_fds()[j + 1].fd << std::endl;
					close(server.get_fds()[j + 1].fd);
					server.get_fds().erase(server.get_fds().begin() + j + 1);
				}
			}
std::cout << "nb clients: " << server.get_clients().size() << std::endl;
std::cout << "nb pollfd: " << server.get_fds().size() << std::endl;

	} // end main loop
	std::cout << "Closing all remaining fd" << std::endl;
	for (i = 0; i < server.get_fds().size(); i++)
	{
		if(server.get_fds()[i].fd >= 0)
			close(server.get_fds()[i].fd);
	}
	return 0;
}