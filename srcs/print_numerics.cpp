#include "../includes/numerics.hpp"
#include "../includes/ft_irc.hpp"
#include "../includes/Server.hpp"
#include "../includes/Client.hpp"
#include "../includes/Message.hpp"
#include "../includes/Channel.hpp"

std::string Server::build_response(int num, Client &sender, Client &receiver, Channel *channel, Message *message)
{
	return ":" + sender.get_fullidentity() + " " + print_numerics(num, sender, receiver, channel, message);
}

std::string Server::build_response(Client &sender, std::string str)
{
	return ":" + sender.get_fullidentity() + " " + str;
}

std::string ft_print_numerics(/*User &user, Server &server, Channel &channel, Message &message*/ int nb_message)
{
	(void) nb_message;
	std::cout << "Nb message = " << nb_message << std::endl;
	return "fonction juste pour que ca compile en attendant d'avoir tout modif";
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
	(void) num;
	(void) sender;
	(void) receiver;
	(void) channel;
	(void) message;

	std::string str_num;
  	std::stringstream ss;  
  
  	ss << num;  
  	ss >> str_num;  

//TODO
// + TODO channel
	std::string user_flags = "H*";                       //H for present, G for gone, OPTIONAL * for server operator, member prefix, usermode
	std::string user_fingerprint = "fingerprint"; //wtf is this shit ?
	std::string hopcount = "0";                                 //nb of intermediate server 
	std::string sec_away = "353";                        // seconds since last active
	std::string sign_on = "666";                         // unix timestamp, when joined the network
	std::string privilege = "Oper priv";
	//              BAN VAR                 //
	std::string banMask = "Banmask";                     // BanMask ???? For 367
	std::string banner_nick = "Ikyllian";
	std::string banner_nickmask = "Ikyllian masked";
	std::string ban_timeSet = "22222";
	//              MESSAGE VAR             //
 	std::string mask = "channel";
	//	update 16/05
	std::string subject = "sujet";
	std::string target = "target";
	std::string	mode_char = "modechar";
	std::string	parameter = "Parametre du modechar";
	//              OTHERS                  //
	std::string	help_msg = "aled";			//May differ if it's the start/mid/end of the help section
	std::string description = "Description";
	std::string null = "";
	//				SERVER					//
	std::string Rehashing_message = "Rehash";
	std::string SASL_mechanisms = "Oui non Oui";
	std::string infoServer = "KKR info server";
	std::string token = "13";
	std::string max_user = "53"; // max fd ?
	std::string comment = "loul";
	std::string motd = "Bonjour"; 

	std::string nb_operator = "1"; // loop sur les clients et les compter?
	std::string invisible_user = "3"; // loop sur les clients et les compter?
	std::string connexion = "7"; // nombre de user connect au server mais qui ont pas fini de register ?
	//ajout gestion time ?
	std::string datetime = "20/05/2022";
	std::string actual_time = "22";             //Le temps actuel (Potentiellement a faire en dehors de la classe server)
//FIN TODO


	//              user VAR               //
	std::string realname =  sender.get_realname();
	std::string user_modes = sender.get_user_modes();
	std::string away_message = sender.get_away_msg();

	std::string username = sender.get_username();;
	std::string user_account = sender.get_username();

	std::string client_name = sender.get_nickname();
	/*if (message)
	{
		client_name += message->get_command() + " ";
	}*/
	std::string user_nick = sender.get_nickname();

	//              SERVER VAR              //
	std::string server_connected = "1";
	std::string network_name = get_network_name();
	std::string hostname = get_hostname();
	std::string port = get_port();
	std::string nb_channel = std::to_string(get_channels().size());
	std::string servername = get_servername();
	std::string version = get_version();
	std::string locationServer = get_locationServer();
	std::string hostInfo = get_hostInfo();
	std::string hostMail = get_hostMail();


	std::string global_user = std::to_string(get_clients().size());
	std::string nb_user = std::to_string(get_clients().size());
	std::string nb_clients = std::to_string(get_clients().size());
	std::string local_user = std::to_string(get_clients().size());

	std::string full_identity = sender.get_fullidentity();


	//              MESSAGE VAR              //
	std::string command;
	std::string command_info = "Unknown error";

	if (!message)
	{
		command = "ERROR message not set";

	//	std::cerr << "ERROR message not set when calling print numerics" << std::endl;
	}
	else
	{
		command = (*message).get_command();
	}

	//              CHAN VAR                //
	std::string channel_modes;
	std::string channel_name;
	std::string client_count;
	std::string channel_topic;
	std::string mode_string;
	std::string mode_arguments;
	//PAS DANS LA CLASSE
	std::string channel_creationTime;
	std::string channel_whoSetTopic;
	std::string channel_TimeSetTopic;
	std::string mask_InviteExeptionList;  //cf: https://modern.ircdocs.horse/#invite-exception-channel-mode
	std::string mask_ExeptionList;        //cf: https://modern.ircdocs.horse/#exception-channel-mode
	std::string symbol;    
		
	if (!channel)
	{
		channel_modes = "ERROR channel not set";
		channel_name = "*";
		client_count = "ERROR channel not set";
		channel_topic = "ERROR channel not set";
		mode_string = "ERROR channel not set";
		mode_arguments = "ERROR channel not set";
		//PAS DANS LA CLASSE
		channel_creationTime = "ERROR channel not set";
		channel_whoSetTopic = "ERROR channel not set";
		channel_TimeSetTopic = "ERROR channel not set";
		mask_InviteExeptionList = "ERROR channel not set";
		mask_ExeptionList = "ERROR channel not set";
		symbol = "ERROR channel not set";

	//	std::cerr << "ERROR channel not set when calling print numerics" << std::endl;
	}
	else
	{
		channel_modes = (*channel).get_channel_modes();
		channel_name = (*channel).get_name();
		client_count = std::to_string((*channel).get_users().size());
		channel_topic = (*channel).get_topic();
		mode_string = (*channel).get_channel_modes();
		mode_arguments = (*channel).get_mode_arguments();
		//PAS DANS LA CLASSE
		channel_creationTime = "123";
		channel_whoSetTopic = "acasunno";
		channel_TimeSetTopic = "5623";
		mask_InviteExeptionList = "Blablabla";
		mask_ExeptionList = "Blobloblo";
		if ((*channel).get_channel_modes().find("s") != std::string::npos)
			symbol = "@";
		else if ((*channel).get_channel_modes().find("p") != std::string::npos)
			symbol = "*";
		else
			symbol = "=";
	}

	switch (num)
	{
	case 1:
		return ("00" + str_num + " " + client_name + RPL_WELCOME(network_name, full_identity));
		// "Welcome to the Internet Relay Network
        //        <nick>!<user>@<host>"
		
	case 2:
		return (str_num + " " + client_name + RPL_YOURHOST(network_name, user_nick));
		
	case 3:
		return (str_num + " " + client_name + RPL_CREATED(datetime));
		
	case 4:
		return (str_num + " " + client_name + RPL_MYINFO(servername, version, user_modes, channel_modes));
		
	case 5:
		return (str_num + " " + client_name + RPL_ISUPPORT(token));           //Need to create token: cf https://modern.ircdocs.horse/#rplisupport-005
		
	case 10:
		return (str_num + " " + client_name + RPL_BOUNCE(hostname, port, infoServer));
		
	case 221:
		return (str_num + " " + client_name + RPL_UMODEIS(user_modes));
		
	case 251:
		return (str_num + " " + client_name + RPL_LUSERCLIENT(nb_user, invisible_user, server_connected));
		
	case 252:
		return (str_num + " " + client_name + RPL_LUSEROP(nb_operator));
		
	case 253:
		return (str_num + " " + client_name + RPL_LUSERUNKNOWN(connexion));
		
	case 254:
		return (str_num + " " + client_name + RPL_LUSERCHANNELS(nb_channel));
		
	case 255:
		return (str_num + " " + client_name + RPL_LUSERME(nb_clients, server_connected));
		
	case 256:
		return (str_num + " " + client_name + RPL_ADMINME(servername));
		
	case 257:
		return (str_num + " " + client_name + RPL_ADMINLOC1(locationServer));
		
	case 258:
		return (str_num + " " + client_name + RPL_ADMINLOC2(hostInfo));
		
	case 259:
		return (str_num + " " + client_name + RPL_ADMINEMAIL(hostMail));
		
	case 263:
		return (str_num + " " + client_name + RPL_TRYAGAIN(command));
		
	case 265:
		return (str_num + " " + client_name + RPL_LOCALUSERS(local_user, max_user));
		
	case 266:
		return (str_num + " " + client_name + RPL_GLOBALUSERS(global_user, max_user));
		
	case 276:
		return (str_num + " " + client_name + RPL_WHOISCERTFP(user_nick, user_fingerprint));
		
	case 300:
		return (str_num + " " + client_name + RPL_NONE(null));
		
	case 301:
		return (str_num + " " + client_name + RPL_AWAY(user_nick, away_message));
		
	case 302:
		return (str_num + " " + client_name + RPL_USERHOST(command));         //NEED TO CREATE A MESSAGE cf: https://modern.ircdocs.horse/#rpluserhost-302
		
	case 305:
		return (str_num + " " + client_name + RPL_UNAWAY(null));
		
	case 306:
		return (str_num + " " + client_name + RPL_NOWAWAY(null));
		
	case 352:
		return (str_num + " " + client_name + RPL_WHOREPLY(channel_name, username, hostname, servername, user_nick, user_flags, hopcount, realname));

		
	case 315:
		if (message->get_tab_parameter().size() > 0)
			return (str_num + " " + client_name + RPL_ENDOFWHO(message->get_tab_parameter()[0]));
		else
			return (str_num + " " + client_name + RPL_ENDOFWHO(channel_name));
	case 307:
		return (str_num + " " + client_name + RPL_WHOISREGNICK(user_nick));
		
	case 311:
		return (str_num + " " + client_name + RPL_WHOISUSER(user_nick, username, hostname, realname));
		
	case 312:
		return (str_num + " " + client_name + RPL_WHOISSERVER(user_nick, servername, infoServer));
		
	case 313:
		return (str_num + " " + client_name + RPL_WHOISOPERATOR(user_nick));
		
	case 314:
		return (str_num + " " + client_name + RPL_WHOWASUSER(user_nick, username, hostname, realname));
		
	case 317:
		return (str_num + " " + client_name + RPL_WHOISIDLE(user_nick, sec_away, sign_on));
		
	case 318:
		return (str_num + " " + client_name + RPL_ENDOFWHOIS(user_nick));
		
	case 319:
		// Potentiellement prefix sur channel_name
		return (str_num + " " + client_name + RPL_WHOISCHANNELS(user_nick, channel_name));
		
	case 320:
		return (str_num + " " + client_name + RPL_WHOISSPECIAL(user_nick));
		
	case 321:
		return (str_num + " " + client_name + RPL_LISTSTART(null));
		
	case 322:
		return (str_num + " " + client_name + RPL_LIST(channel_name, client_count, channel_topic));
		
	case 323:
		return (str_num + " " + client_name + RPL_LISTEND(null));
		
	case 324:
		return (str_num + " " + client_name + RPL_CHANNELMODEIS(channel_name, mode_string, mode_arguments));
		
	case 329:
		return (str_num + " " + client_name + RPL_CREATIONTIME(channel_name, channel_creationTime));
		
	case 330:
		return (str_num + " " + client_name + RPL_WHOISACCOUNT(user_nick, user_account));
		
	case 331:
		return (str_num + " " + client_name + RPL_NOTOPIC(channel_name));
		
	case 332:
		return (str_num + " " + client_name + RPL_TOPIC(channel_name, channel_topic));
		
	case 333:
		return (str_num + " " + client_name + RPL_TOPICWHOTIME(channel_name, channel_whoSetTopic, channel_TimeSetTopic));
		
	case 336:
		return (str_num + " " + client_name + RPL_INVITELIST(channel_name));
		
	case 337:
		return (str_num + " " + client_name + RPL_ENDOFINVITELIST(null));
		
	case 341:
		return (str_num + " " + client_name + RPL_INVITING(user_nick, channel_topic));
		
	case 346:
		return (str_num + " " + client_name + RPL_INVEXLIST(channel_name, mask_InviteExeptionList));
		
	case 347:
		return (str_num + " " + client_name + RPL_ENDOFINVEXLIST(channel_name));
		
	case 348:
		return (str_num + " " + client_name + RPL_EXCEPTLIST(channel_name, mask_ExeptionList));
		
	case 349:
		return (str_num + " " + client_name + RPL_ENDOFEXCEPTLIST(channel_name));
		
	case 351:
		return (str_num + " " + client_name + RPL_VERSION(version, servername, comment));
		
	case 353:
		return (str_num + " " + client_name + RPL_NAMREPLY(symbol, channel_name, user_nick));
		
	case 366:
		return (str_num + " " + client_name + RPL_ENDOFNAMES(channel_name));
		
	case 364:
		return (str_num + " " + client_name + RPL_LINKS(servername, hopcount, infoServer));
		
	case 365:
		return (str_num + " " + client_name + RPL_ENDOFLINKS(null));
		
	case 367:
		return (str_num + " " + client_name + RPL_BANLIST(channel_name, banMask, banner_nick, ban_timeSet));           //
		
	case 368:
		return (str_num + " " + client_name + RPL_ENDOFBANLIST(channel_name));
		
	case 369:
		return (str_num + " " + client_name + RPL_ENDOFWHOWAS(user_nick));
		
	case 371:
		return (str_num + " " + client_name + RPL_INFO(infoServer));          // Perharps other info
		
	case 374:
		return (str_num + " " + client_name + RPL_ENDOFINFO(null));
		
	case 375:
		return (str_num + " " + client_name + RPL_MOTDSTART(servername));
		
	case 372:
		return (str_num + " " + client_name + RPL_MOTD(motd));
		
	case 376:
		return (str_num + " " + client_name + RPL_ENDOFMOTD(null));
		
	case 378:
		return (str_num + " " + client_name + RPL_WHOISHOST(user_nick));          //Need to define ip ?
		
	case 379:
		return (str_num + " " + client_name + RPL_WHOISMODES(user_nick));         //Need to define available modes ?
		
	case 381:
		return (str_num + " " + client_name + RPL_YOUREOPER(null));
		
	case 382:
		return (str_num + " " + client_name + RPL_REHASHING(Rehashing_message));
		
	case 391:
		return (str_num + " " + client_name + RPL_TIME(servername, actual_time));
		
	case 670:
		return (str_num + " " + client_name + RPL_STARTTLS(null));
		
	case 671:
		return (str_num + " " + client_name + RPL_WHOISSECURE(user_nick));
		
	case 704:
		return (str_num + " " + client_name + RPL_HELPSTART(subject, help_msg));
		
	case 705:
		return (str_num + " " + client_name + RPL_HELPTXT(subject, help_msg));
		
	case 706:
		return (str_num + " " + client_name + RPL_ENDOFHELP(subject, help_msg));
		
	case 900:
		return (str_num + " " + client_name + RPL_LOGGEDIN(user_nick, username, hostname, user_account, username));		// User = username ???
		
	case 901:
		return (str_num + " " + client_name + RPL_LOGGEDOUT(user_nick, username, hostname, user_account));
		
	case 903:
		return (str_num + " " + client_name + RPL_SASLSUCCESS(null));
		
	case 908:
		return (str_num + " " + client_name + RPL_SASLMECHS(SASL_mechanisms));
		
	case 400:
		return (str_num + " " + client_name + ERR_UNKNOWNERROR(command, command_info));
		
	case 401:
		return (str_num + " " + client_name + ERR_NOSUCHNICK(user_nick));
		
	case 402:
		return (str_num + " " + client_name + ERR_NOSUCHSERVER(servername));
		
	case 403:
		return (str_num + " " + client_name + ERR_NOSUCHCHANNEL(message->get_tab_parameter()[0]));
		
	case 404:
		return (str_num + " " + client_name + ERR_CANNOTSENDTOCHAN(channel_name));
		
	case 405:
		return (str_num + " " + client_name + ERR_TOOMANYCHANNELS(channel_name));
		
	case 406:
		return (str_num + " " + client_name + ERR_WASNOSUCHNICK(null));
		
	case 409:
		return (str_num + " " + client_name + ERR_NOORIGIN(null));

	case 411:
		return (str_num + " " + client_name + ERR_NORECIPIENT(command));

	case 412:
		return (str_num + " " + client_name + ERR_NOTEXTTOSEND(null));

	case 417:
		return (str_num + " " + client_name + ERR_INPUTTOOLONG(null));
		
	case 421:
		return (str_num + " " + client_name + ERR_UNKNOWNCOMMAND(command));
		
	case 422:
		return (str_num + " " + client_name + ERR_NOMOTD(null));
		
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
		
	case 451:
		return (str_num + " " + client_name + ERR_NOTREGISTERED(null));
		
	case 461:
		return (str_num + " " + client_name + ERR_NEEDMOREPARAMS(command));
		
	case 462:
		return (str_num + " " + client_name + ERR_ALREADYREGISTERED(null));
		
	case 464:
		return (str_num + " " + client_name + ERR_PASSWDMISMATCH(null));
		
	case 465:
		return (str_num + " " + client_name + ERR_YOUREBANNEDCREEP(null));
		
	case 471:
		return (str_num + " " + client_name + ERR_CHANNELISFULL(channel_name));
		
	case 472:
		return (str_num + " " + client_name + ERR_UNKNOWNMODE(mode_char));
		
	case 473:
		return (str_num + " " + client_name + ERR_INVITEONLYCHAN(channel_name));
		
	case 474:
		return (str_num + " " + client_name + ERR_BANNEDFROMCHAN(channel_name));
		
	case 475:
		return (str_num + " " + client_name + ERR_BADCHANNELKEY(channel_name));
		
	case 476:
		return (str_num + " " + client_name + ERR_BADCHANMASK(channel_name));
		
	case 481:
		return (str_num + " " + client_name + ERR_NOPRIVILEGES(null));
		
	case 482:
		return (str_num + " " + client_name + ERR_CHANOPRIVSNEEDED(channel_name));
		
	case 483:
		return (str_num + " " + client_name + ERR_CANTKILLSERVER(null));
		
	case 491:
		return (str_num + " " + client_name + ERR_NOOPERHOST(null));
		
	case 501:
		return (str_num + " " + client_name + ERR_UMODEUNKNOWNFLAG(null));
		
	case 502:
		return (str_num + " " + client_name + ERR_USERSDONTMATCH(null));
		
	case 524:
		return (str_num + " " + client_name + ERR_HELPNOTFOUND(subject));
		
	case 525:
		return (str_num + " " + client_name + ERR_INVALIDKEY(target));
		
	case 691:
		return (str_num + " " + client_name + ERR_STARTTLS(null));
		
	case 696:
		return (str_num + " " + client_name + ERR_INVALIDMODEPARAM(target, mode_char, parameter, description));
		
	case 723:
		return (str_num + " " + client_name + ERR_NOPRIVS(privilege));
		
	case 902:
		return (str_num + " " + client_name + ERR_NICKLOCKED(null));
		
	case 904:
		return (str_num + " " + client_name + ERR_SASLFAIL(null));
		
	case 905:
		return (str_num + " " + client_name + ERR_SASLTOOLONG(null));
		
	case 906:
		return (str_num + " " + client_name + ERR_SASLABORTED(null));
		
	case 907:
		return (str_num + " " + client_name + ERR_SASLALREADY(null));
	default:
		std::cout << "Numeric not found" << std::endl;
		break;
		
	}
	return ("");
}