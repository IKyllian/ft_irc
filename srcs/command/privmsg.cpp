#include "../../includes/Server.hpp"
#include "../../includes/Channel.hpp"
#include "../../includes/ft_irc.hpp"

void    Server::command_PRIVMSG(Client &sender, Message &msg, Server &server, int is_notice)
{
    std::vector<std::string> targets;
    std::vector<Channel*>::iterator channel_it;
    std::vector<Client*>::iterator client_it;
    std::vector<std::string>::iterator ban_user_it;
    std::map<Client *, std::string>::iterator joined_chan_it;
    std::string chan = "";

    switch (msg.get_nb_parameter()) {
        case 0:
            send_message(sender, ft_print_numerics(411));
            break;
        case 1:
            send_message(sender, ft_print_numerics(412));
            break;
        default:
            targets = parse_comma(msg.get_tab_parameter()[0]);
            for (size_t i = 0; i < targets.size(); i++) {
                if (targets[i].find("#") != std::string::npos) {
                    chan = targets[i];
                    targets[i] = chan.substr(chan.find("#"));
                }
               if (targets[i].size() > 0 && (targets[i][0] == '#' || targets[i][0] == '&')) {
                    channel_it = get_channel(targets[i]);
                    client_it = _clients.end();
                } else {
                    channel_it = _channels.end();
                    client_it = get_client(targets[i]);
                }
                if (client_it == _clients.end() && channel_it == _channels.end()) {
                    if (targets[i].size() > 0 && (targets[i][0] == '#' || targets[i][0] == '&'))
                        send_message(msg.get_sender(), build_message2(403, msg.get_sender(), targets[i]));
                    else
                        send_message(msg.get_sender(), build_message2(401, msg.get_sender(), targets[i]));
                    continue ;
                }
                if (client_it != _clients.end()) {
                    if ((*client_it)->get_away())
                        send_message(sender, server.print_numerics(301, sender, *(*client_it), NULL, &msg));
                    if (is_notice)
                       send_message(*(*client_it), build_command_message(sender.get_nickname(), "", (*client_it)->get_nickname(), "NOTICE", msg.get_tab_parameter()));
                    else
                        send_message(*(*client_it), build_command_message(sender.get_nickname(), "", (*client_it)->get_nickname(), "PRIVMSG", msg.get_tab_parameter()));
                } else if (channel_it != _channels.end()) {
                    for (ban_user_it = (*channel_it)->get_users_ban().begin(); ban_user_it != (*channel_it)->get_users_ban().end(); ban_user_it++)
                        if (sender.get_nickname() == (*ban_user_it))
                            break ;
                    if ((*channel_it)->get_users_ban().size() > 0 && ban_user_it != (*channel_it)->get_users_ban().end())
                        continue ;
                    if ((*channel_it)->get_channel_modes().find("n") != std::string::npos && (*channel_it)->get_user(&sender) == (*channel_it)->get_users().end()) {
                        send_message(sender, server.print_numerics(404, sender, *(*client_it), (*channel_it), &msg));
                        continue ;
                    }
                    for (std::map<Client *, std::string>::iterator it = (*channel_it)->get_users().begin(); it != (*channel_it)->get_users().end(); it++) {
                        if (chan != "") {
                            if (chan.find("@") != std::string::npos && chan.find("@") < chan.find("#") && ((*it).second.find("o") == std::string::npos)) {   
                                send_message(sender, server.print_numerics(404, sender, *(*client_it), (*channel_it), &msg));
                                continue ;
                            }
                            else if (chan.find("+") != std::string::npos && chan.find("+") < chan.find("#") && ((*it).second.find("v") == std::string::npos && (*it).second.find("o") == std::string::npos)) {
                                send_message(sender, server.print_numerics(404, sender, *(*client_it), (*channel_it), &msg));
                                continue ;
                            } else {
                                if (sender.get_nickname() != (*it).first->get_nickname()) {
                                    if (is_notice)
                                        send_message(*(it->first), build_command_message(sender.get_nickname(), "", (*channel_it)->get_name(), "NOTICE", msg.get_tab_parameter()));
                                    else
                                        send_message(*(it->first), build_command_message(sender.get_nickname(), "", (*channel_it)->get_name(), "PRIVMSG", msg.get_tab_parameter()));
                                }
                            }
                        }
                    }
                }
                chan = "";
            }
            break;
    }
}