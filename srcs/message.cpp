#include "../includes/numerics.hpp"
#include "../includes/ft_irc.hpp"

void ft_message(/*User &user, Server &server, Channel &channel, Message &message*/int nb_message)
{
    //              Client VAR               //
    std::string username = "Kyllian";
    std::string user_account = "Kdolper";
    std::string realname = "Kyllian";
    std::string user_nick = "Ikyllian";
    std::string user_modes = "iorw";
//PAS DANS LA CLASSE
    std::string user_fingerprint = "fingerprint";
    std::string user_flags = "H*";                       //H for present, G for gone, OPTIONAL * for server operator, member prefix, usermode
    std::string away_message = "F*** this sh** i'm out";
    std::string hopcount = "5";                                 //nb of intermediate server 
    std::string sec_away = "353";                        // seconds since last active
    std::string sign_on = "666";                         // unix timestamp, when joined the network
//UPDATE 16/05
	std::string privilege = "Oper priv";

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
    std::string max_user = "53";
    std::string local_user = "10";
    std::string global_user = "23";
    std::string comment = "loul";
    std::string motd = "Bonjour";           //MESSAGE OF THE DAY
    std::string Rehashing_message = "Rehash";
	// Update 16/05
	std::string SASL_mechanisms = "Oui non Oui";


    //              CHAN VAR                //
    std::string channel_modes = "beI,kfL,lj,psmntirRcOAQKVCuzNSMTGZ";
    //PAS DANS LA CLASSE
    std::string channel_name = "J'aime les pommes";
    std::string client_count = "5";
    std::string channel_topic = "Les pommes";
    std::string channel_creationTime = "123";
    std::string channel_whoSetTopic = "acasunno";
    std::string channel_TimeSetTopic = "5623";
    std::string mask_InviteExeptionList = "Blablabla";  //cf: https://modern.ircdocs.horse/#invite-exception-channel-mode
    std::string mask_ExeptionList = "Blobloblo";        //cf: https://modern.ircdocs.horse/#exception-channel-mode
    std::string symbol = "=";                          // = Public channel                 @ Secret channel           * Private channel

    //              BAN VAR                 //
    std::string banMask = "Banmask";                     // BanMask ???? For 367
    std::string banner_nick = "Ikyllian";
    std::string banner_nickmask = "Ikyllian masked";
    std::string ban_timeSet = "22222";

    //              MESSAGE VAR             //
    std::string command = "NICK";
    std::string command_info = "Error Info of NICK";        //:example.com 400 dan!~d@n PACK :Could not process multiple invalid parameters
    std::string mask = "channel";
	std::string mode_string = "+a";             //cf: https://modern.ircdocs.horse/#mode-message        Je sais pas si c'est dans message
    std::string mode_arguments = "mode arguments";   //??? Je sais pas c'est quoi...                    Je sais pas si c'est dans message
	//	update 16/05
	std::string subject = "sujet";
	std::string target = "target";
	std::string	mode_char = "modechar";
	std::string	parameter = "Parametre du modechar";

    //              OTHERS                  //
    std::string actual_time = "22";             //Le temps actuel (Potentiellement a faire en dehors de la classe server)
	//update 16/05
	std::string	help_msg = "Help me";			//May differ if it's the start/mid/end of the help section
	std::string description = "Description";

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
        std::cout << username << RPL_ISUPPORT(token);           //Need to create token: cf https://modern.ircdocs.horse/#rplisupport-005
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
        std::cout << username << RPL_LUSEROP(nb_operator);
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
    case 265:
        std::cout << username << RPL_LOCALUSERS(local_user, max_user);
        break;
    case 266:
        std::cout << username << RPL_GLOBALUSERS(global_user, max_user);
        break;
    case 276:
        std::cout << username << RPL_WHOISCERTFP(user_nick, user_fingerprint);
        break;
    case 300:
        std::cout << username << STRINGIFY(RPL_NONE());
        break;
    case 301:
        std::cout << username << RPL_AWAY(user_nick, away_message);
        break;
    case 302:
        std::cout << username << RPL_USERHOST(command);         //NEED TO CREATE A MESSAGE cf: https://modern.ircdocs.horse/#rpluserhost-302
        break;
    case 305:
        std::cout << username << STRINGIFY(RPL_UNAWAY());
        break;
    case 306:
        std::cout << username << STRINGIFY(RPL_NOWAWAY());
        break;
    case 352:
        std::cout << username << RPL_WHOREPLY(channel_name, username, hostname, servername, user_nick, user_flags, hopcount, realname);
        break;
    case 315:
        std::cout << username << RPL_ENDOFWHO(mask);
        break;
    case 307:
        std::cout << username << RPL_WHOISREGNICK(user_nick);
        break;
    case 311:
        std::cout << username << RPL_WHOISUSER(user_nick, username, hostname, realname);
        break;
    case 312:
        std::cout << username << RPL_WHOISSERVER(user_nick, servername, infoServer);
        break;
    case 313:
        std::cout << username << RPL_WHOISOPERATOR(user_nick);
        break;
    case 314:
        std::cout << username << RPL_WHOWASUSER(user_nick, username, hostname, realname);
        break;
    case 317:
        std::cout << username << RPL_WHOISIDLE(user_nick, sec_away, sign_on);
        break;
    case 318:
        std::cout << username << RPL_ENDOFWHOIS(user_nick);
        break;
    case 319:
        // Potentiellement prefix sur channel_name
        std::cout << username << RPL_WHOISCHANNELS(user_nick, channel_name);
        break;
    case 320:
        std::cout << username << RPL_WHOISSPECIAL(user_nick);
        break;
    case 321:
        std::cout << username << STRINGIFY(RPL_LISTSTART());
        break;
    case 322:
        std::cout << username << RPL_LIST(channel_name, client_count, channel_topic);
        break;
    case 323:
        std::cout << username << STRINGIFY(RPL_LISTEND());
        break;
    case 324:
        std::cout << username << RPL_CHANNELMODEIS(channel_name, mode_string, mode_arguments);
        break;
    case 329:
        std::cout << username << RPL_CREATIONTIME(channel_name, channel_creationTime);
        break;
    case 330:
        std::cout << username << RPL_WHOISACCOUNT(user_nick, user_account);
        break;
    case 331:
        std::cout << username << RPL_NOTOPIC(channel_name);
        break;
    case 332:
        std::cout << username << RPL_TOPIC(channel_name, channel_topic);
        break;
    case 333:
        std::cout << username << RPL_TOPICWHOTIME(channel_name, channel_whoSetTopic, channel_TimeSetTopic);
        break;
    case 336:
        std::cout << username << RPL_INVITELIST(channel_name);
        break;
    case 337:
        std::cout << username << STRINGIFY(RPL_ENDOFINVITELIST());
        break;
    case 341:
        std::cout << username << RPL_INVITING(user_nick, channel_topic);
        break;
    case 346:
        std::cout << username << RPL_INVEXLIST(channel_name, mask_InviteExeptionList);
        break;
    case 347:
        std::cout << username << RPL_ENDOFINVEXLIST(channel_name);
        break;
    case 348:
        std::cout << username << RPL_EXCEPTLIST(channel_name, mask_ExeptionList);
        break;
    case 349:
        std::cout << username << RPL_ENDOFEXCEPTLIST(channel_name);
        break;
    case 351:
        std::cout << username << RPL_VERSION(version, servername, comment);
        break;
    case 353:
        std::cout << username << RPL_NAMREPLY(symbol, channel_name, user_nick);
        break;
    case 366:
        std::cout << username << RPL_ENDOFNAMES(channel_name);
        break;
    case 364:
        std::cout << username << RPL_LINKS(servername, hopcount, infoServer);
        break;
    case 365:
        std::cout << username << STRINGIFY(RPL_ENDOFLINKS());
        break;
    case 367:
        std::cout << username << RPL_BANLIST(channel_name, banMask, banner_nick, ban_timeSet);           //
        break;
    case 368:
        std::cout << username << RPL_ENDOFBANLIST(channel_name);
        break;
    case 369:
        std::cout << username << RPL_ENDOFWHOWAS(user_nick);
        break;
    case 371:
        std::cout << username << RPL_INFO(infoServer);          // Perharps other info
        break;
    case 374:
        std::cout << username << STRINGIFY(RPL_ENDOFINFO());
        break;
    case 375:
        std::cout << username << RPL_MOTDSTART(servername);
        break;
    case 372:
        std::cout << username << RPL_MOTD(motd);
        break;
    case 376:
        std::cout << username << STRINGIFY(RPL_ENDOFMOTD());
        break;
    case 378:
        std::cout << username << RPL_WHOISHOST(user_nick);          //Need to define ip ?
        break;
    case 379:
        std::cout << username << RPL_WHOISMODES(user_nick);         //Need to define available modes ?
        break;
    case 381:
        std::cout << username << STRINGIFY(RPL_YOUREOPER());
        break;
    case 382:
        std::cout << username << RPL_REHASHING(Rehashing_message);
        break;
    case 391:
        std::cout << username << RPL_TIME(servername, actual_time);
        break;
	case 670:
		std::cout << username << STRINGIFY(STARTTLS());
		break;
	case 671:
		std::cout << username << RPL_WHOISSECURE(user_nick);
		break;
	case 704:
		std::cout << username << RPL_HELPSTART(subject, help_msg);
		break;
	case 705:
		std::cout << username << RPL_HELPTXT(subject, help_msg);
		break;
	case 706:
		std::cout << username << RPL_ENDOFHELP(subject, help_msg);
		break;
	case 900:
		std::cout << username << RPL_LOGGEDIN(user_nick, username, hostname, user_account, username);		// User = username ???
		break;
	case 901:
		std::cout << username << RPL_LOGGEDOUT(user_nick, username, hostname, user_account);
		break;
	case 903:
		std::cout << username << STRINGIFY(RPL_SASLSUCCESS());
		break;
	case 908:
		std::cout << username << RPL_SASLMECHS(SASL_mechanisms);
		break;
	case 400:
        std::cout << username << ERR_UNKNOWNERROR(command, command_info);
        break;
	case 401:
		std::cout << username << ERR_NOSUCHNICK(user_nick);
		break;
	case 402:
		std::cout << username << ERR_NOSUCHSERVER(servername);
		break;
	case 403:
		std::cout << username << ERR_NOSUCHCHANNEL(channel_name);
		break;
	case 404:
		std::cout << username << ERR_CANNOTSENDTOCHAN(channel_name);
		break;
	case 405:
		std::cout << username << ERR_TOOMANYCHANNELS(channel_name);
		break;
	case 406:
		std::cout << username << STRINGIFY(ERR_WASNOSUCHNICK());
		break;
	case 409:
		std::cout << username << STRINGIFY(ERR_NOORIGIN());
		break;
	case 417:
		std::cout << username << STRINGIFY(ERR_INPUTTOOLONG());
		break;
	case 421:
		std::cout << username << ERR_UNKNOWNCOMMAND(command);
		break;
	case 422:
		std::cout << username << STRINGIFY(ERR_NOMOTD());
		break;
	case 432:
		std::cout << username << ERR_ERRONEUSNICKNAME(user_nick);
		break;
	case 433:
		std::cout << username << ERR_NICKNAMEINUSE(user_nick);
		break;
	case 441:
		std::cout << username << ERR_USERNOTINCHANNEL(user_nick, channel_name);
		break;
	case 442:
		std::cout << username << ERR_NOTONCHANNEL(channel_name);
		break;
	case 443:
        std::cout << username << ERR_UNKNOWNERROR(command, command_info);
        break;
	case 451:
		std::cout << username << STRINGIFY(ERR_NOTREGISTERED());
		break;
	case 461:
		std::cout << username << ERR_NEEDMOREPARAMS(command);
		break;
	case 462:
		std::cout << username << STRINGIFY(ERR_ALREADYREGISTERED());
		break;
	case 464:
		std::cout << username << STRINGIFY(ERR_PASSWDMISMATCH());
		break;
	case 465:
		std::cout << username << STRINGIFY(ERR_YOUREBANNEDCREEP());
		break;
	case 471:
		std::cout << username << ERR_CHANNELISFULL(channel_name);
		break;
	case 472:
		std::cout << username << ERR_UNKNOWNMODE(mode_char);
		break;
	case 473:
		std::cout << username << ERR_INVITEONLYCHAN(channel_name);
		break;
	case 474:
		std::cout << username << ERR_BANNEDFROMCHAN(channel_name);
		break;
	case 475:
		std::cout << username << ERR_BADCHANNELKEY(channel_name);
		break;
	case 476:
		std::cout << username << ERR_BADCHANMASK(channel_name);
		break;
	case 481:
		std::cout << username << STRINGIFY(ERR_NOPRIVILEGES());
		break;
	case 482:
		std::cout << username << ERR_CHANOPRIVSNEEDED(channel_name);
		break;
	case 483:
		std::cout << username << STRINGIFY(ERR_CANTKILLSERVER());
		break;
	case 491:
		std::cout << username << STRINGIFY(ERR_NOOPERHOST());
		break;
	case 501:
		std::cout << username << STRINGIFY(ERR_UMODEUNKNOWNFLAG());
		break;
	case 502:
		std::cout << username << STRINGIFY(ERR_USERSDONTMATCH());
		break;
	case 524:
		std::cout << username << ERR_HELPNOTFOUND(subject);
		break;
	case 525:
		std::cout << username << ERR_INVALIDKEY(target);
		break;
	case 691:
		std::cout << username << STRINGIFY(ERR_STARTTLS());
		break;
	case 696:
		std::cout << username << ERR_INVALIDMODEPARAM(target, mode_char, parameter, description);
		break;
	case 723:
		std::cout << username << ERR_NOPRIVS(privilege);
		break;
	case 902:
		std::cout << username << STRINGIFY(ERR_NICKLOCKED());
		break;
	case 904:
		std::cout << username << STRINGIFY(ERR_SASLFAIL());
		break;
	case 905:
		std::cout << username << STRINGIFY(ERR_SASLTOOLONG());
		break;
	case 906:
		std::cout << username << STRINGIFY(ERR_SASLABORTED());
		break;
	case 907:
		std::cout << username << STRINGIFY(ERR_SASLALREADY());
		break;

	default:
        break;
    }
}