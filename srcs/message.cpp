#include "../includes/numerics.hpp"
#include "../includes/ft_irc.hpp"

void ft_message(/*User &user, Server &server, Channel &channel, Message message*/int nb_message)
{
    //              USERS VAR               //
    std::string username = "Kyllian";
    std::string user_nick = "Ikyllian";
    std::string user_modes = "iorw";

    //              SERVER VAR              //
    std::string network_name = NETWORK_NAME;
    std::string hostname = "KKR";
    std::string port = "127.0.0.1";
    std::string infoServer = "KKR info server";
    std::string servername = "Delire avec des gens chelou";
    std::string locationServer = "Lyon 42 Charbonnière";
    std::string hostInfo = "Some 42 students";
    std::string hostMail = "kkr@student.42.fr";
    std::string version = "5.3";
    std::string token = "13";
    std::string connexion = "7";
    std::string nb_user = "5";
    std::string nb_clients = "18";
    std::string nb_operator = "1";
    std::string invisible_user = "3";
    std::string server_connected = "6";
    std::string nb_channel = "6";
    std::string datetime = "20/05/2022";

    //              CHAN VAR                //
    std::string channel_modes = "beI,kfL,lj,psmntirRcOAQKVCuzNSMTGZ";

    //              MESSAGE VAR             //
    std::string command = "NICK"

    //              OTHERS                  //

    switch (nb_message)
    {
    case 1:
        std::cout << username << RPL_WELCOME(network_name, user_nick);
        break;
    case 2:
        std::cout << username << RPL_YOURHOST(network_name, user_nick);
        break;
    case 3:
        std::cout << username << RPL_CREATED(datetime);
        break;
    case 4:
        std::cout << username << RPL_MYINFO(servername, version, user_modes, channel_modes);
        break;
    case 5:
        std::cout << username << RPL_ISUPPORT(token);
        break;
    case 10:
        std::cout << username << RPL_BOUNCE(hostname, port, infoServer);
        break;
    case 221:
        std::cout << username << RPL_UMODEIS(user_modes);
        break;
    case 251:
        std::cout << username << RPL_LUSERCLIENT(nb_user, invisible_user, server_connected);
        break;
    case 252:
        std::cout << username << RPL_LUSEROP(number_operator);
        break;
    case 253:
        std::cout << username << RPL_LUSERUNKNOWN(connexion);
        break;
    case 254:
        std::cout << username << RPL_LUSERCHANNELS(nb_channel);
        break;
    case 255:
        std::cout << username << RPL_LUSERME(nb_clients, server_connected);
        break;
    case 256:
        std::cout << username << RPL_ADMINME(servername);
        break;
    case 257:
        std::cout << username << RPL_ADMINLOC1(locationServer);
        break;
    case 258:
        std::cout << username << RPL_ADMINLOC2(hostInfo);
        break;
    case 259:
        std::cout << username << RPL_ADMINEMAIL(hostMail);
        break;
    case 263:
        std::cout << username << RPL_TRYAGAIN(command);
        break;

    default:
        break;
    }
}