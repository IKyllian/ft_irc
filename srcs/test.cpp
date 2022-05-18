/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:50:38 by kzennoun          #+#    #+#             */
/*   Updated: 2022/05/18 14:16:08 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_HPP
#define TEST_HPP


#include "../includes/Client.hpp"

#include <string.h> //linux
#include <stdlib.h> //linux
//#include <iomanip>//test cpp 14
//#include "../includes/ft_irc.hpp"
//from ft_irc_hpp
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

#define TRUE             1
#define FALSE            0

//class Client;

bool add_new_client(std::vector<Client>& clients, int fd, char* buffer, size_t size)
{
	//(void) clients;
	(void) fd;
	//(void) buffer;
	(void) size;
	// char						buffer[2048];
	int		ret = 1;
	Client	new_client;
//	bool	complete = FALSE;
//	std::string str = buffer;
	int i = 0;

	new_client.set_fd(fd);
	std::cout << "received a message from a new client, fd " << new_client.get_fd() << std::endl;
//	std::cout << "buffer is: " << str << std::endl;
	std::cout << "buff pre loop: " << std::endl << buffer << std::endl;
	//nickname
	//username
	//usermod ??


	// ret = fcntl(fd, F_SETFL, O_NONBLOCK);
	// if (ret == -1)
	// {
	// 	perror("fcntl() failed");
	// 	close(fd);
	// 	return(false);
	// }

	
	ret = 1;
	while(ret > 0)
	{
		while(buffer[i])
			i++;
		std::cout << "i = " << i << std::endl;
		ret = recv(fd, buffer + i, sizeof(buffer - i), 0);
		std::cout << "ret " << ret << std::endl;
		std::cout << "TMPbuff: " << std::endl << buffer << std::endl << std::flush;
	}

	std::cout << "FINALbuff: " << std::endl << buffer << std::endl << std::flush;
//CAP LS 302
//PASS 123456
//NICK karim 
//USER karim 0* :realname 

	// while (!complete)
	// {



	// }

	// loop initial dialog

	// memset(&buffer, 0, sizeof(buffer));
	// ret = recv(fd, buffer, sizeof(buffer), 0);

	// if (ret < 0)
	// {
	// 	if (errno != EWOULDBLOCK)
	// 	{
	// 		perror("  recv() failed");
	// 	}
	// 	return FALSE;
	// }

	// if (ret == 0)
	// {
	// 	std::cout << "Connection closed " << std::endl;
	// 	return FALSE;
	// }





	// if (ret > 0)
	// {

	clients.push_back(new_client);
	// }



	return TRUE;
}



int handle_incoming_message(std::vector<Client>& clients, int fd)
{
	int ret;
	char buffer[65535];
	int len;
	unsigned long i;
	std::string str;
//	std::stringstream ss;
	

	str.clear();
	for (i = 0; i < clients.size(); i++)
	{
		std::cout << "HIM fd  " << fd  << " clients[i].get_fd() " << clients[i].get_fd() << " i " << i <<  std::endl;
		if (fd == clients[i].get_fd())
			break;
	}

	if (i == clients.size())
		clients.push_back(Client(fd));
	
	do
	{
		std::cout << "--------------" << std::endl;
		memset(&buffer, 0, sizeof(buffer));
		ret = recv(fd, buffer, sizeof(buffer), 0);

		str += buffer;




	//	ss.str(str);
		
		std::cout << "HIM ret: " << ret << std::endl;
		std::cout << "HIM buffer: " << buffer << std::endl;
		std::cout << "HIM str: " << str << std::endl;
	//	std::cout << "HIM ss: " << ss << std::endl;
		// if (ret <= 0)
		// {
		// 	std::cerr << "Something went very very wrong" << std::endl;
		// 	return ret;
		// }

		len = str.length();
		std::cout << "len " << len << std::endl;
		std::cout << "str[len - 1] != " << (str[len - 1] != '\n') << std::boolalpha << std::endl; 

		// int i = 0;
		// while (str[i])
		// {
		// 	std::cout << i << " - str[i]" << (int)str[i] << std::endl;
		// 	i++;
		// }

		if(str[len - 1] != '\n' && str[len - 2] != '\r')
		{
			std::cout << "coucou" << std::endl;
			break;
		}


		//envoyer une ligne

	}while(ret > 0);

std::cout << "HIM2 str:" << str << std::endl;

//AJOUTER CALL POUR LE PARSING

	return ret;
}


int main(int ac, char **av)
{

//var for basic commucation
	int							socketFD, clientFD, timeout;
	int							len, on, ret = 1;
	struct sockaddr_in			addr;
	std::vector<struct pollfd>	fds;
	struct pollfd				fd;
	bool						end_server = FALSE;
	bool						close_conn = FALSE;
	//char						buffer[65535];
	unsigned long				i, j;
	(void) j;
//var for client
	//std::map<int, Client>		m_fd_client;
	std::vector<Client>			clients;



    if (__cplusplus == 201703L) std::cout << "C++17\n";
    else if (__cplusplus == 201402L) std::cout << "C++14\n";
    else if (__cplusplus == 201103L) std::cout << "C++11\n";
    else if (__cplusplus == 199711L) std::cout << "C++98\n";
    else std::cout << "pre-standard C++\n";



	if (ac < 2 || ac > 3)
	{
		std::cout << "Wrong number of Arguments" << std::endl;
		return (0);
	}
// Create an AF_INET (ipv4)stream socket to receive incoming connections on  
	socketFD = socket(AF_INET, SOCK_STREAM, 0);
	if (socketFD < 0)
	{
		perror("socket() failed");
		return(-1);
	}

// Allow socket descriptor to be reuseable  
	ret = setsockopt(socketFD, SOL_SOCKET,  SO_REUSEADDR,
	(char *)&on, sizeof(on));
	if (ret < 0)
	{
		perror("setsockopt() failed");
		close(socketFD);
		return(-1);
	}

// Set socket to be nonblocking. All of the sockets for 
//    the incoming connections will also be nonblocking since  
//   they will inherit that state from the listening socket.   

	ret = fcntl(socketFD, F_SETFL, O_NONBLOCK);
	if (ret == -1)
	{
		perror("fcntl() failed");
		close(socketFD);
		return(-1);
	}

//Bind the socket  
	
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(atoi(av[1]));


	ret = bind(socketFD, (struct sockaddr *)&addr, sizeof(addr));
	if (ret < 0)
	{
		perror("bind() failed");
		close(socketFD);
		return(-1);
	}

 // Set the listen back log

	//second arg (32) is size of the listen backlog
	ret = listen(socketFD, 32);
	if (ret == -1 )
	{
		perror("listen() failed");
		close(socketFD);
		exit(-1);
	}

//Initialize the pollfd structure  <<-- with vector not array
	memset(&fd, 0 , sizeof(fd));
	fd.fd = socketFD;
	fd.events = POLLIN;
	fds.push_back(fd);

	timeout = (3 * 60 * 1000); // 3 mins


	do
	{
		std::cout << "Waiting on poll()..." << std::endl;
		ret = poll(&(fds[0]), fds.size(), timeout);
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

		for (i = 0; i < fds.size(); i++)
		{
			if(fds[i].revents == 0)
				continue;

			if(fds[i].revents != POLLIN)
			{
// Error! revents = 17
				std::cerr << "Error! revents = " << fds[i].revents << std::endl;
				end_server = TRUE;
				break;

			}
			
			if (fds[i].fd == socketFD)
			{
				do
				{
					/*****************************************************/
					/* Accept each incoming connection. If               */
					/* accept fails with EWOULDBLOCK, then we            */
					/* have accepted all of them. Any other              */
					/* failure on accept will cause us to end the        */
					/* server.                                           */
					/*****************************************************/
					clientFD = accept(socketFD, NULL, NULL);
					if (clientFD < 0)
					{
						if (errno != EWOULDBLOCK)
						{
							perror("  accept() failed");
							end_server = TRUE;
						}
						break;
					}

					/*****************************************************/
					/* Add the new incoming connection to the            */
					/* pollfd structure                                  */
					/*****************************************************/
					std::cout << "New incomig connection: " << clientFD << std::endl;

					fd.fd = clientFD;
					fd.events = POLLIN;
					fds.push_back(fd);
					// fds[nfds].fd = new_sd;
					// fds[nfds].events = POLLIN;
					// nfds++;

					/*****************************************************/
					/* Loop back up and accept another incoming          */
					/* connection                                        */
					/*****************************************************/
				} while (clientFD != -1);
			}
			else
			{
				std::cout << "Descriptor " << fds[i].fd << " is readable" << std::endl;
				close_conn = FALSE;
				/*******************************************************/
				/* Receive all incoming data on this socket            */
				/* before we loop back and call poll again.            */
				/*******************************************************/

				do
				{
					/*****************************************************/
					/* Receive data on this connection until the         */
					/* recv fails with EWOULDBLOCK. If any other         */
					/* failure occurs, we will close the                 */
					/* connection.                                       */
					/*****************************************************/


					ret = handle_incoming_message(clients, fds[i].fd);

					// memset(&buffer, 0, sizeof(buffer));
					// ret = recv(fds[i].fd, buffer, sizeof(buffer), 0);


// std::cout << "##############" << std::endl;
// std::cout << "received: " << buffer;

// 	//std::vector<Client>			clients;
// //TODO faire des choses
// // if fds[i].fd n'est PAS une key du map m_fd_client --> nouvelle connection
// // 			-> handle initial stuff()
// //			
// //if fds[i].fd est une key du map m_fd_client --> client existant
// // 			-> parse?()
// //					
// std::cout << "clients size " << clients.size() << std::endl;
// std::cout << "----------------" << std::endl;
					//j = 0;
					// for (j = 0; j < clients.size(); j++)
					// {
					// 	std::cout << "fds[i].fd  " << fds[i].fd  << " clients[j].get_fd() " << clients[j].get_fd() << " j " << j <<  std::endl;
					// 	if (fds[i].fd == clients[j].get_fd())
					// 	{
					// 		//found
							
					// 		if (!handle_incoming_message(clients[j], buffer, sizeof(buffer)))
					// 		{
					// 			std::cerr << "Failed to handle incoming message" << std::endl;
					// 			close_conn = TRUE;
					// 			//break;
					// 		}
					// 		break;
					// 	}
					// }

					// if (j == clients.size())
					// {
					// 	//not found
					// 	clients.push_back(Client(fds[i].fd));
					// 	if (!handle_incoming_message(clients[clients.size() - 1], buffer, sizeof(buffer)))
					// 	{
					// 		std::cerr << "Failed to handle incoming message" << std::endl;
					// 		close_conn = TRUE;
					// 		//break;
					// 	}
					// 	// if (!add_new_client(clients, fds[i].fd, buffer, sizeof(buffer)))
					// 	// {
					// 	// 	std::cerr << "Couldn't add new client" << std::endl;
					// 	// 	close_conn = TRUE;
					// 	// 	break;
					// 	// }
					// }




					if (ret < 0)
					{
						if (errno != EWOULDBLOCK)
						{
							perror("  recv() failed");
							close_conn = TRUE;
						}
						break;
					}

					/*****************************************************/
					/* Check to see if the connection has been           */
					/* closed by the client                              */
					/*****************************************************/
					if (ret == 0)
					{
						std::cout << "Connection closed " << std::endl;
						close_conn = TRUE;
						break;
					}

					/*****************************************************/
					/* Data was received                                 */
					/*****************************************************/
					len = ret;
					std::cout << len << " bytes received " << std::endl;
					std::cout << std::endl;





					// /*****************************************************/
					// /* Echo the data back to the client                  */
					// /*****************************************************/
					// ret = send(fds[i].fd, buffer, len, 0);
					// if (ret < 0)
					// {
					// 	perror("  send() failed");
					// 	close_conn = TRUE;
					// 	break;
					// }








				} while(TRUE);

				/*******************************************************/
				/* If the close_conn flag was turned on, we need       */
				/* to clean up this active connection. This            */
				/* clean up process includes removing the              */
				/* descriptor.                                         */
				/*******************************************************/
				if (close_conn)
				{
std::cout << "Closing fd " << fds[i].fd << std::endl;
					for (j = 0; j < clients.size(); j++)
					{
						if (fds[i].fd == clients[j].get_fd())
						{
							clients.erase(clients.begin() + j);
							break;
						}
					}
					close(fds[i].fd);
					fds[i].fd = -1;
				//	compress_array = TRUE;
				}


			}  /* End of existing connection is readable             */
		} /* End of loop through pollable descriptors              */

		/***********************************************************/
		/* If the compress_array flag was turned on, we need       */
		/* to squeeze together the array and decrement the number  */
		/* of file descriptors. We do not need to move back the    */
		/* events and revents fields because the events will always*/
		/* be POLLIN in this case, and revents is output.          */
		/***********************************************************/

			for (i = 0; i < fds.size(); i++)
			{
				if (fds[i].fd == -1)
				{
					fds.erase(fds.begin() + i);
				}
			}
		} while (end_server == FALSE); /* End of serving running.    */

		/*************************************************************/
		/* Clean up all of the sockets that are open                 */
		/*************************************************************/
		for (i = 0; i < fds.size(); i++)
		{
			if(fds[i].fd >= 0)
				close(fds[i].fd);
		}
}

#endif