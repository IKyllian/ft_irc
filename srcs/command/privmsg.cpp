#include "../../includes/Server.hpp"
#include "../../includes/Channel.hpp"
#include "../../includes/ft_irc.hpp"

void    Server::command_PRIVMSG(Client &sender, Message &msg)
{
    std::vector<std::string> targets;
    std::vector<Channel>::iterator channel_it;
    std::vector<Client>::iterator client_it;
    std::vector<Client*>::iterator ban_user_it;
    std::map<Client *, std::string>::iterator joined_chan_it;
    std::string chan = "";

    switch (msg.get_nb_parameter()) {
        case 0:
            send_message(sender, ft_print_numerics(411) + "\n");
            break;
        case 1:
            send_message(sender, ft_print_numerics(412) + "\n");
            break;
        default:
            targets = parse_comma(msg.get_tab_parameter()[0]);
            for (size_t i = 0; i < targets.size(); i++) {
                if (targets[i].find("#") != std::string::npos) {
                    chan = targets[i];
                    targets[i] = chan.substr(chan.find("#") + 1);
                }
                client_it = get_client(targets[i]);
                if (client_it == _clients.end())
                    channel_it = get_channel(targets[i]);
                if (client_it == _clients.end() && channel_it == _channels.end()) {
                    send_message(sender, ft_print_numerics(401)); // ERR_NOSUCHNICK (401) 
                    send_message(sender, ft_print_numerics(402)); // ERR_NOSUCHSERVER (402)
                    // Si target n'est ni un user ni un channel, quelle erreur envoyé ? les deux ou une autre erreurs que celles-ci ?
                    continue ;
                }
                if (client_it != _clients.end()) {
                    if ((*client_it).get_away())
                        send_message(sender, ft_print_numerics(301));
                    send_message(sender, build_command_message(sender.get_nickname(), "", (*client_it).get_nickname(), "PRIVMSG", msg.get_tab_parameter()[1], 0));
                    // std::cout << ":" << sender.get_nickname() << " PRIVMSG " << (*client_it).get_nickname() << " :" << msg.get_tab_parameter()[1] << std::endl;
                    //send message
                } else if (channel_it != _channels.end()) {
                    for (std::vector<Client*>::iterator ban_user_it = (*channel_it).get_users_ban().begin(); ban_user_it != (*channel_it).get_users_ban().end(); ban_user_it++)
                        if (sender.get_nickname() == (*ban_user_it)->get_nickname())
                            break ;
                    if ((*channel_it).get_users_ban().size() > 0 && ban_user_it != (*channel_it).get_users_ban().end())
                        continue ;
                    if ((*channel_it).get_channel_modes().find("n") != std::string::npos && (*channel_it).get_user(&sender) == (*channel_it).get_users().end()) {
                        send_message(sender, ft_print_numerics(404));
                        continue ;
                    }
                    for (std::map<Client *, std::string>::iterator it = (*channel_it).get_users().begin(); it != (*channel_it).get_users().end(); it++) {
                        if (chan != "") {
                            if (chan.find("@") != std::string::npos && chan.find("@") < chan.find("#") && ((*it).second.find("o") == std::string::npos)) {   
                                send_message(sender, ft_print_numerics(404));
                                continue ;
                            }
                            else if (chan.find("+") != std::string::npos && chan.find("+") < chan.find("#") && ((*it).second.find("v") == std::string::npos && (*it).second.find("o") == std::string::npos)) {
                                send_message(sender, ft_print_numerics(404));
                                continue ;
                            } else
                                send_message(sender, build_command_message(sender.get_nickname(), (*it).first->get_nickname(), "PRIVMSG", msg.get_tab_parameter()[1], 0));
                                std::cout << ":" << sender.get_nickname() << " PRIVMSG " << (*it).first->get_nickname() << " :" << msg.get_tab_parameter()[1] << std::endl;
                            // send message
                        }
                    }
                    send_message(sender, build_command_message(sender.get_nickname(), "", (*channel_it).get_name(), "PRIVMSG", msg.get_tab_parameter()[1], 0));
                    // send_message(sender,  build_message(sender.get_nickname(), (*it).first->get_nickname(), msg.get_tab_parameter()[1], 1));
                    //  std::cout << ":" << sender.get_nickname() << " PRIVMSG #" << (*channel_it).get_name() << " :" << msg.get_tab_parameter()[1] << std::endl;
                }
                chan = "";
            }
            // Check potentiel préfix dans les strings et agir en conséquence
            // Si le string ne trouve pas un channel ou nickname, envoyer numeric 401 ou 402 (Comment differencier un channel name d'un nickname ???)
            // Si le sender n'a pas rejoint le Channel ou que le channel a le mode +m et que le sender n'a pas le channel privilège, envoyer numeric 404
            break;
    }
}