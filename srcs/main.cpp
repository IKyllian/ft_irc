#include "../includes/ft_irc.hpp"

int main(int argc, char **argv)
{

    int socketFD = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFD < 0)
    {
        perror("socket() failed");
        return(-1);
    }
    int socketFDNew;
    char buffer[512];

    argv = &argv[1]; // ARGV[0] = port, ARGV[1] = password

    struct sockaddr_in socketaddr; // sockaddr_in = Socket Internet

    if (argc < 2 || argc > 3)
    {
        std::cout << "Wrong number of Arguments" << std::endl;
        return (0);
    }

    socketaddr.sin_family = AF_INET;
    socketaddr.sin_addr.s_addr = INADDR_ANY;
    socketaddr.sin_port = htons(atoi(argv[0]));

    if (bind(socketFD, (struct sockaddr *)&socketaddr, sizeof(socketaddr)) == -1) {
        std::cout << "Error bind" << errno << std::endl;
        close(socketFD);
        return(0);
    }

    if (listen(socketFD, 0) == -1)
        std::cout << "Error listen" << std::endl;

    socketFDNew = accept(socketFD, (struct sockaddr *)&socketaddr, (socklen_t *)&socketaddr);
    int size;
    for (;  (size = recv(socketFDNew, buffer, 512, 0)) != 0; ) {
        std::cout << socketFDNew << " - " << size << " - " << buffer << std::endl;
    }
    close(socketFD);
    close(socketFDNew);
    return (0);
}
