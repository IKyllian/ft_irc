/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:50:38 by kzennoun          #+#    #+#             */
/*   Updated: 2022/05/11 14:02:46 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_irc.hpp"

 #include <fcntl.h>


#define TRUE             1
#define FALSE            0

int main(int argc, char **argv)
{
	if (argc < 2 || argc > 3)
	{
		std::cout << "Wrong number of Arguments" << std::endl;
		return (0);
	}

	int socketFD;
	int on, rc = 1;

	socketFD = socket(AF_INET, SOCK_STREAM, 0);
	if (socketFD < 0)
	{
		perror("socket() failed");
		return(-1);
	}


	rc = setsockopt(socketFD, SOL_SOCKET,  SO_REUSEADDR,
	(char *)&on, sizeof(on));
	if (rc < 0)
	{
		perror("setsockopt() failed");
		close(socketFD);
		return(-1);
	}


	// int fcntl(int fd, int cmd, ... /* arg */ );

}