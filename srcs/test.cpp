#include "../includes/ft_irc.hpp"

#include <fcntl.h>
#include <vector>
#include <cstdio>

#define TRUE             1
#define FALSE            0

int main(int ac, char **av)
{

	int							socketFD, clientFD, timeout;
	int							len, on, ret = 1;
	struct sockaddr_in			addr;
	std::vector<struct pollfd>	fds;
	struct pollfd				fd;
	bool						end_server = FALSE;
	bool						close_conn = FALSE;
	char						buffer[2048];
	unsigned long				i;

	if (ac < 2 || ac > 3)
	{
		std::cout << "Wrong number of Arguments" << std::endl;
		return (0);
	}
// Create an AF_INET stream socket to receive incoming connections on  
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
					ret = recv(fds[i].fd, buffer, sizeof(buffer), 0);

std::cout << "received: " << buffer << std::endl;

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