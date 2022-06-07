#include "../../includes/Server.hpp"
#include "../../includes/Channel.hpp"
#include "../../includes/ft_irc.hpp"

void    Server::command_PRIVMSG(Client &sender, Message &msg)
{
    std::vector<std::string> targets;
    std::vector<Channel>::iterator channel_it;
    std::vector<Client>::iterator client_it;
    std::string chan = "";

    switch (msg.get_nb_parameter())
    {
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
                targets[i] = chan.substr(targets[i].find("#") + 1);
            }
            client_it = get_client(targets[i]);
            if (client_it == _clients.end())
                channel_it = get_channel(targets[i]);
            if (client_it == _clients.end() && channel_it == _channels.end()) {
                ft_print_numerics(401); // ERR_NOSUCHNICK (401) 
                ft_print_numerics(402); // ERR_NOSUCHSERVER (402) 
                // Si target n'est ni un user ni un channel, quelle erreur envoyé ? les deux ou une autre erreurs que celles-ci ?
                continue ;
            }
            if (client_it != _clients.end()) {
                if ((*client_it).get_away())
                    ft_print_numerics(301);
                //send message
            } else if (channel_it != _channels.end()) {
                for (std::map<Client *, std::string>::iterator it = (*channel_it).get_users().begin(); it != (*channel_it).get_users().begin(); it++) {
                    if (chan != "") {
                        if (targets[i].find("@") != std::string::npos && targets[i].find("@") < targets[i].find("#") && ((*it).second.find("o") == std::string::npos))
                            continue ;
                        else if (targets[i].find("+") != std::string::npos && targets[i].find("+") < targets[i].find("#") && ((*it).second.find("v") == std::string::npos || (*it).second.find("o") == std::string::npos))
                            continue ;
                        // send message
                    }
                }
            }
            chan = "";
        }
        // Split sur ',' qui va créer un tableau de string
        // Check potentiel préfix dans les strings et agir en conséquence
        // Check sur la classe Server tout les CHANNEL et tout les USERS
        // si # au debut, channel name, sinon nickname
        // Si le string ne trouve pas un channel ou nickname, envoyer numeric 401 ou 402 (Comment differencier un channel name d'un nickname ???)
        // Si le string est un channel, pushback sur le vector<channel> dans la classe message (vector A CREER)
        // Si le string est un USER, pushback sur le vector<User> dans la classe message (vector A CREER)
        // Pour chaque Channel, check si le sender est dans la liste de ban exception (on fait tout normalement) ou qu'il est ban (on envoie rien) if (ban && !banexeption)
        // Si le sender n'a pas rejoint le Channel ou que le channel a le mode +m et que le sender n'a pas le channel privilège, envoyer numeric 404
        // Si prefix, n'envoyer le message que au user qui ont les droits pour l'avoir (droit égal ou supérieur)
        // Pour chaque USER, check si le user est away (get_away()), si il est away envoyer ft_print_numerics(receiver, 301) 
        break;
    }
}