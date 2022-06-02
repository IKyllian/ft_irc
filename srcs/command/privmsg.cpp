#include "../../includes/Server.hpp"
#include "../../includes/ft_irc.hpp"

void    Server::command_PRIVMSG(Client &sender, Message &msg)
{
    (void)sender;
    switch (msg.get_nb_parameter())
    {
    case 0:
        send_message(*this, sender, ft_print_numerics(411), 411);
        break;
    case 1:
        send_message(*this, sender, ft_print_numerics(412), 412);
        break;
    default:
    
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