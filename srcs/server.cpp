#include "../includes/ft_irc.hpp"

int main(int argc, char **argv)
{
    //												SERVER SIDE												//
    // socket(domain, type, protocol)
    // domain: AF_INET = IPV4, AF_INET6 = IPV6
    // type:	SOCK_STREAM = TCP, SOCK_DGRAM = UDP
    // protocol: Internet Protocol ou 0	(man protocols, http://web.deu.edu.tr/doc/oreily/networking/tcpip/ch02_07.htm)
    int socketFD = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFD < 0)
    {
        perror("socket() failed");
        return(-1);
    }
    int socketFDNew;

    argv = &argv[1]; // ARGV[0] = port, ARGV[1] = password

    /*
    La structure sockaddr_in:

    struct sockaddr_in
    {
        short sin_family;
        u_short sin_port;
        struct in_addr sin_addr;
        char sin_zero[8];
    };

    */
    struct sockaddr_in socketaddr; // sockaddr_in = Socket Internet

    if (argc < 2 || argc > 3)
    {
        std::cout << "Wrong number of Arguments" << std::endl;
        return (0);
    }

    socketaddr.sin_family = AF_INET;
    socketaddr.sin_addr.s_addr = INADDR_ANY;
    socketaddr.sin_port = htons(atoi(argv[0]));

    if (bind(socketFD, (struct sockaddr *)&socketaddr, sizeof(socketaddr)) == -1)
        std::cout << "Error bind" << std::endl;

    if (listen(socketFD, 0) == -1)
        std::cout << "Error listen" << std::endl;

    socketFDNew = accept(socketFD, (struct sockaddr *)&socketaddr, (socklen_t *)&socketaddr);

    return (0);
}
