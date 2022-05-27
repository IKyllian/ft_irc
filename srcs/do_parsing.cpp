#include "../includes/ft_irc.hpp"

static void do_command(/*Server &server, Client &receiver,*/ Message &msg)
{
    /*(void)server;
    (void)receiver;*/
    if (msg.get_command() == "CAP")
    {
        //  do_CAP();
    }
    else if (msg.get_command() == "AUTHENTICATE")
    {
        //  do_AUTHENTICATE();
    }
    else if (msg.get_command() == "PASS")
    {
        //  do_PASS ();
    }
    else if (msg.get_command() == "NICK")
    {
        //  do_NICK ();
    }
    else if (msg.get_command() == "USER")
    {
        //  do_USER();
    }
    else if (msg.get_command() == "PING")
    {
        //  do_PING();
    }
    else if (msg.get_command() == "PONG")
    {
        //  do_PONG();
    }
    else if (msg.get_command() == "OPER")
    {
        //  do_OPER();
    }
    else if (msg.get_command() == "QUIT")
    {
        //  do_QUIT();
    }
    else if (msg.get_command() == "ERROR")
    {
        //  do_ERROR();
    }
    else if (msg.get_command() == "JOIN")
    {
        //  do_PART();
    }
    else if (msg.get_command() == "TOPIC")
    {
        //  do_TOPIC();
    }
    else if (msg.get_command() == "NAMES")
    {
        //  do_NAMES();
    }
    else if (msg.get_command() == "LIST")
    {
        //  do_LIST();
    }
    else if (msg.get_command() == "INVITE")
    {
        //  do_INVITE();
    }
    else if (msg.get_command() == "KICK")
    {
        //  do_KICK();
    }
    else if (msg.get_command() == "MOTD")
    {
        //  do_MOTD();
    }
    else if (msg.get_command() == "VERSION")
    {
        //  do_VERSION();
    }
    else if (msg.get_command() == "ADMIN")
    {
        //  do_ADMIN();
    }
    else if (msg.get_command() == "CONNECT")
    {
        //  do_CONNECT();
    }
    else if (msg.get_command() == "LUSERS")
    {
        //  do_LUSERS();
    }
    else if (msg.get_command() == "TIME")
    {
        //  do_TIME();
    }
    else if (msg.get_command() == "STATS")
    {
        //  do_STATS();
    }
    else if (msg.get_command() == "HELP")
    {
        //  do_HELP();
    }
    else if (msg.get_command() == "INFO")
    {
        //  do_INFO();
    }
    else if (msg.get_command() == "MODE")
    {
        //  do_MODE();
    }
    else if (msg.get_command() == "PRIVMSG")
    {
        //  do_PRIVMSG();
    }
    else if (msg.get_command() == "NOTICE")
    {
        //  do_NOTICE();
    }
    else if (msg.get_command() == "WHO")
    {
        //  do_WHO();
    }
    else if (msg.get_command() == "WHOIS")
    {
        //  do_WHOIS();
    }
    else if (msg.get_command() == "WHOWAS")
    {
        //  do_WHOWAS();
    }
    else if (msg.get_command() == "KILL")
    {
        //  do_KILL();
    }
    else if (msg.get_command() == "RESTART")
    {
        //  do_RESTART();
    }
    else if (msg.get_command() == "SQUIT")
    {
        //  do_SQUIT();
    }
    else if (msg.get_command() == "AWAY")
    {
        //  do_AWAY();
    }
    else if (msg.get_command() == "LINKS")
    {
        //  do_LINKS();
    }
    else if (msg.get_command() == "USERHOST")
    {
        //  do_USERHOST();
    }
    else if (msg.get_command() == "WALLOPS")
    {
        //  do_WALLOPS();
    }
    else
    {
        std::cout << "Command not found" << std::endl;
    }
}

void do_parsing(/*Server &server, Client &expediteur,*/ std::string message)
{
    std::vector<Message*> msg;
    std::vector<std::string> msg_list;

    msg_list = ft_split_message(message);
    for (size_t i = 0; i < msg_list.size(); i++)
        msg.push_back(ft_create_message(msg_list[i]));
    for (size_t i = 0; i < msg.size(); i++)
        do_command(/*server, expediteur, */*msg[i]);
    for (size_t i = 0; i < msg.size(); i++)
        delete msg[i];
    return;
}