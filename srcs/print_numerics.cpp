#include "../includes/ft_irc.hpp"

std::string Server::build_response(int num, Client &sender, Client &receiver, Channel *channel, Message *message)
{
	return ":" + sender.get_fullidentity() + " " + print_numerics(num, sender, receiver, channel, message);
}

std::string Server::build_response(Client &sender, std::string str)
{
	return ":" + sender.get_fullidentity() + " " + str;
}

std::string build_message2(int num, Client &sender, std::string target, Channel *channel) {
	std::string str;
	std::string symbol;
	std::string str_num;
  	std::stringstream ss;  
  
  	ss << num;  
  	ss >> str_num;  

	if (num == 401)
		return ":" + sender.get_fullidentity() + " 401 " + target + " :No such nick/channel";
	else if (num == 472)
		return ":" + sender.get_fullidentity() + " 472 " + target + " :is unknown mode char to me";
	else if (num == 461)
		return ":" + sender.get_fullidentity() + " 461 " + target + " :Not enough parameters";
	else if (num == 403)
		return ":" + sender.get_fullidentity() + " 403 " + target + " :No such channel";
	else {
		for (std::map<Client*, std::string>::iterator it = channel->get_users().begin(); it != channel->get_users().end(); it++) {
			if ((*it).second.size() > 0) {
				if ((*it).second.find("o") != std::string::npos)
					str += "@";
				else if ((*it).second.find("v") != std::string::npos)
					str += "+";
			}
			str += (*it).first->get_nickname();
			str += " ";
		}
		if ((*channel).get_channel_modes().find("s") != std::string::npos)
			symbol = "@";
		else if ((*channel).get_channel_modes().find("p") != std::string::npos)
			symbol = "*";
		else
			symbol = "=";
		return ":" + sender.get_fullidentity() + " " + str_num + " " + symbol + " " + channel->get_name() + " :" + str;
	}
}

std::string Server::print_numerics(int num, Client &sender, Client &receiver, Channel *channel, Message *message)
{
	(void) receiver;

	std::string str_num;
  	std::stringstream ss;  

  	ss << num;  
  	ss >> str_num;

	std::string hopcount = "0";
	std::string null = "";

	std::string user_flags;//352 H for present, G for gone, OPTIONAL * for server operator, member prefix, usermode
	if (sender.get_away() == true)
		user_flags = "G";
	else
		user_flags = "H";


	//              user VAR               //
	std::string realname =  sender.get_realname();
	std::string user_modes = sender.get_user_modes();
	std::string full_identity = sender.get_fullidentity();
	std::string username = sender.get_username();

	std::string client_name = sender.get_nickname();
	std::string user_nick = sender.get_nickname();

	//              SERVER VAR             //
	std::string network_name = get_network_name();
	std::string hostname = get_hostname();
	std::string servername = get_servername();

	//              MESSAGE VAR            //
	std::string command = "ERROR message not set";
	std::string no_such_channel = "ERROR message not set";
	if (message)
	{
		command = (*message).get_command();
		if (message->get_tab_parameter().size() >= 1)
			no_such_channel = message->get_tab_parameter()[0];
	}

	//              CHAN VAR               //
	std::string channel_name = "*";
	std::string client_count = "ERROR channel not set";
	std::string channel_topic = "ERROR channel not set";
	std::string mode_string = "ERROR channel not set";
	std::string mode_arguments = "ERROR channel not set";
		
	if (channel)
	{
		channel_name = (*channel).get_name();
		client_count = std::to_string((*channel).get_users().size());
		channel_topic = (*channel).get_topic();
		mode_string = (*channel).get_channel_modes();
		mode_arguments = (*channel).get_mode_arguments();
	}

	switch (num)
	{
	case 1:
		return ("00" + str_num + " " + client_name + RPL_WELCOME(network_name, full_identity));

	case 221:
		return (str_num + " " + client_name + RPL_UMODEIS(user_modes));

	case 301: {
		std::string receiver_nick = receiver.get_nickname();
		std::string away_message = receiver.get_away_msg();
		return (str_num + " " + client_name + RPL_AWAY(receiver_nick, away_message));
	}
	
	case 305:
		return (str_num + " " + client_name + RPL_UNAWAY(null));
		
	case 306:
		return (str_num + " " + client_name + RPL_NOWAWAY(null));

	case 311:
		return (str_num + " " + client_name + RPL_WHOISUSER(user_nick, username, hostname, realname));

	case 313:
		return (str_num + " " + client_name + RPL_WHOISOPERATOR(user_nick));

	case 315:
		if (message->get_tab_parameter().size() > 0)
			return (str_num + " " + client_name + RPL_ENDOFWHO(message->get_tab_parameter()[0]));
		else
			return (str_num + " " + client_name + RPL_ENDOFWHO(channel_name));

	case 318:
		return (str_num + " " + client_name + RPL_ENDOFWHOIS(user_nick));
		
	case 319:
		// Potentiellement prefix sur channel_name
		return (str_num + " " + client_name + RPL_WHOISCHANNELS(user_nick, channel_name));

	case 321:
		return (str_num + " " + client_name + RPL_LISTSTART(null));
		
	case 322:
		return (str_num + " " + client_name + RPL_LIST(channel_name, client_count, channel_topic));
		
	case 323:
		return (str_num + " " + client_name + RPL_LISTEND(null));
		
	case 324:
		return (str_num + " " + client_name + RPL_CHANNELMODEIS(channel_name, mode_string, mode_arguments));

	case 331:
		return (str_num + " " + client_name + RPL_NOTOPIC(channel_name));
		
	case 332:
		return (str_num + " " + client_name + RPL_TOPIC(channel_name, channel_topic));

	case 336:
		return (str_num + " " + client_name + RPL_INVITELIST(channel_name));
		
	case 337:
		return (str_num + " " + client_name + RPL_ENDOFINVITELIST(null));

	case 352:
		return (str_num + " " + client_name + RPL_WHOREPLY(channel_name, username, hostname, servername, user_nick, user_flags, hopcount, realname));

	case 366:
		return (str_num + " " + client_name + RPL_ENDOFNAMES(channel_name));
		
	// case 401:
	// 	return (str_num + " " + client_name + ERR_NOSUCHNICK(user_nick));
		
	case 402:
		return (str_num + " " + client_name + ERR_NOSUCHSERVER(servername));
		
	case 403:
		return (str_num + " " + client_name + ERR_NOSUCHCHANNEL(no_such_channel));
		
	case 404:
		std::cout << "QWEQWEQWEQWEQw" << std::endl;
		return (str_num + " " + client_name + ERR_CANNOTSENDTOCHAN(channel_name));

	case 411:
		return (str_num + " " + client_name + ERR_NORECIPIENT(command));

	case 412:
		return (str_num + " " + client_name + ERR_NOTEXTTOSEND(null));

	case 431:
		return (str_num + " " + client_name + ERR_NONICKNAMEGIVEN(null));
		
	case 432:
		return (str_num + " " + client_name + ERR_ERRONEUSNICKNAME(user_nick));
		
	case 433:
		return (str_num + " " + client_name + ERR_NICKNAMEINUSE(user_nick));
		
	case 441:
		return (str_num + " " + client_name + ERR_USERNOTINCHANNEL(user_nick, channel_name));
		
	case 442:
		return (str_num + " " + client_name + ERR_NOTONCHANNEL(channel_name));
		
	case 443:
		return (str_num + " " + client_name + ERR_USERONCHANNEL(client_name, channel_name));

	case 461:
		return (str_num + " " + client_name + ERR_NEEDMOREPARAMS(command));
		
	case 462:
		return (str_num + " " + client_name + ERR_ALREADYREGISTERED(null));

	case 471:
		return (str_num + " " + client_name + ERR_CHANNELISFULL(channel_name));
		
	case 473:
		return (str_num + " " + client_name + ERR_INVITEONLYCHAN(channel_name));
		
	case 474:
		return (str_num + " " + client_name + ERR_BANNEDFROMCHAN(channel_name));
		
	case 475:
		return (str_num + " " + client_name + ERR_BADCHANNELKEY(channel_name));
	
	case 482:
		return (str_num + " " + client_name + ERR_CHANOPRIVSNEEDED(channel_name));

	case 501:
		return (str_num + " " + client_name + ERR_UMODEUNKNOWNFLAG(null));
		
	case 502:
		return (str_num + " " + client_name + ERR_USERSDONTMATCH(null));

	default:
		std::cout << "Numeric " << num << " not found" << std::endl;
		break;
	}
	return ("");
}