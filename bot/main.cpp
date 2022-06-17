/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 15:19:22 by kzennoun          #+#    #+#             */
/*   Updated: 2022/06/17 16:46:00 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>	
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <strings.h>


//temp
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
//temp end

void display_cpp_ver()
{
	std::cout << "Check CPP Version: ";
    if (__cplusplus == 201703L) std::cout << "C++17\n";
    else if (__cplusplus == 201402L) std::cout << "C++14\n";
    else if (__cplusplus == 201103L) std::cout << "C++11\n";
    else if (__cplusplus == 199711L) std::cout << "C++98\n";
    else std::cout << "pre-standard C++\n";
}

// args
// av[1] username
// av[2] IP
// av[3] port
// av[4] password(optional)

int main(int ac, char **av)
{
	display_cpp_ver();

	if (ac < 4 || ac > 5)
	{
		std::cout << "Wrong number of Arguments" << std::endl;
        std::cout << "Usage: ./" << av[0]
		<< " <username> <server IP> <server port> <server password(optional)>"
		<< std::endl;
		return (0);
	}

	Bot bot;
	int serverFD, ret;
	struct sockaddr_in	addr;
	std::string message;
	struct hostent *server;
	bool password = false;
	
	if (ac == 5)
		password = true;

/*
    create a socket.
    bind* - this is probably be unnecessary because you're the client, not the server.
    connect to a server.
    send/recv - repeat until we have or receive data
    shutdown to end read/write.
    close to releases data.
*/
	server = gethostbyname(av[2]);
    if (server == NULL) {
        perror("ERROR, no such host\n");
        return (-1);
    }

	serverFD = socket(AF_INET, SOCK_STREAM, 0);
	if (serverFD < 0)
	{
		perror("socket() failed");
		return (-1);
	}
	bot.set_serverFD(serverFD);


	// //Bind the socket  
	// ret = bind(serverFD, (struct sockaddr *)&addr, sizeof(addr));
	// if (ret < 0)
	// {
	// 	perror("bind() failed");
	// 	close(serverFD);
	// 	return false;
	// }

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&addr.sin_addr.s_addr, server->h_length);
	addr.sin_port = htons(atoi(av[3]));



	// addr.sin_addr.s_addr = ;
//int connect(int sockfd, const struct sockaddr *serv_addr, socklen_t addrlen);
	ret = connect (serverFD, (struct sockaddr *) &addr, sizeof(addr));
	if (ret < 0)
	{
        perror("connect() failed");
		close(serverFD);
		return (-1);
	}

	if (password)
	{
		message = "";
		message += "PASSWORD ";
		message += av[4];
		bot.send_message(message);
	}

	message = "";
	message += "NICK ";
	message += av[1];
	bot.send_message(message);
	message = "";
	message += "USER ";
	message += av[1];
	message += " * * :";
	message += av[1];
	bot.send_message(message);
//ajouter un check sur le welcome 
	while (true)
	{
		ret = bot.handle_incoming_message();
		if (ret < 0)
			break;
	}
	close(serverFD);
}