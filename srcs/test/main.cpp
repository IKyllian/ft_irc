#include "../../includes/ft_irc.hpp"

int main(int argc, char **argv)
{

    /*                      TEST MESSAGE            */
    std::vector<Message*> msg;
    Message msg2;
    std::vector<std::string> msg_list;
    std::string str = "\r\n\r\n:Tracey`^!me@68.178.52.73 PRIVMSG #game1 :She's dead. Keep laughing.\r\nPRIVMSG2 #game2 :She's dead. Keep laughing.";
    msg_list = ft_split_message(str);
    for (size_t i = 0; i < msg_list.size(); i++)
    {
        msg.push_back(ft_create_message(msg_list[i]));
        std::cout << "prefix = " << msg[i]->get_prefix() << std::endl;
        std::cout << "command = " << msg[i]->get_command() << std::endl;
        std::cout << "parameter = " << msg[i]->get_parameter() << std::endl;
        std::cout << "first = " << msg[i]->get_nb_parameter() << std::endl;
        for (int j = 0; j < msg[i]->get_nb_parameter(); j++)
            std::cout << "splited parameter = " << msg[i]->get_tab_parameter()[j] << std::endl;        
    }
    for (size_t i = 0; i < msg_list.size(); i++)
    {
        delete msg[i];
    }

    /*               END TEST MESSAGE              */


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
