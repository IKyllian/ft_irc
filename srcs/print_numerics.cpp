#include "../includes/numerics.hpp"
#include "../includes/ft_irc.hpp"

std::string ft_print_numerics(/*Client &user, Server &server, Channel &channel, Message &message*/int nb_message)
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
    std::string null = "";

    switch (nb_message)
    {
    case 1:
        return (username + RPL_WELCOME(network_name, user_nick));
        break;
    case 2:
        return (username + RPL_YOURHOST(network_name, user_nick));
        break;
    case 3:
        return (username + RPL_CREATED(datetime));
        break;
    case 4:
        return (username + RPL_MYINFO(servername, version, user_modes, channel_modes));
        break;
    case 5:
        return (username + RPL_ISUPPORT(token));           //Need to create token: cf https://modern.ircdocs.horse/#rplisupport-005
        break;
    case 10:
        return (username + RPL_BOUNCE(hostname, port, infoServer));
        break;
    case 221:
        return (username + RPL_UMODEIS(user_modes));
        break;
    case 251:
        return (username + RPL_LUSERCLIENT(nb_user, invisible_user, server_connected));
        break;
    case 252:
        return (username + RPL_LUSEROP(nb_operator));
        break;
    case 253:
        return (username + RPL_LUSERUNKNOWN(connexion));
        break;
    case 254:
        return (username + RPL_LUSERCHANNELS(nb_channel));
        break;
    case 255:
        return (username + RPL_LUSERME(nb_clients, server_connected));
        break;
    case 256:
        return (username + RPL_ADMINME(servername));
        break;
    case 257:
        return (username + RPL_ADMINLOC1(locationServer));
        break;
    case 258:
        return (username + RPL_ADMINLOC2(hostInfo));
        break;
    case 259:
        return (username + RPL_ADMINEMAIL(hostMail));
        break;
    case 263:
        return (username + RPL_TRYAGAIN(command));
        break;
    case 265:
        return (username + RPL_LOCALUSERS(local_user, max_user));
        break;
    case 266:
        return (username + RPL_GLOBALUSERS(global_user, max_user));
        break;
    case 276:
        return (username + RPL_WHOISCERTFP(user_nick, user_fingerprint));
        break;
    case 300:
        return (username + RPL_NONE(null));
        break;
    case 301:
        return (username + RPL_AWAY(user_nick, away_message));
        break;
    case 302:
        return (username + RPL_USERHOST(command));         //NEED TO CREATE A MESSAGE cf: https://modern.ircdocs.horse/#rpluserhost-302
        break;
    case 305:
        return (username + RPL_UNAWAY(null));
        break;
    case 306:
        return (username + RPL_NOWAWAY(null));
        break;
    case 352:
        return (username + RPL_WHOREPLY(channel_name, username, hostname, servername, user_nick, user_flags, hopcount, realname));
        break;
    case 315:
        return (username + RPL_ENDOFWHO(mask));
        break;
    case 307:
        return (username + RPL_WHOISREGNICK(user_nick));
        break;
    case 311:
        return (username + RPL_WHOISUSER(user_nick, username, hostname, realname));
        break;
    case 312:
        return (username + RPL_WHOISSERVER(user_nick, servername, infoServer));
        break;
    case 313:
        return (username + RPL_WHOISOPERATOR(user_nick));
        break;
    case 314:
        return (username + RPL_WHOWASUSER(user_nick, username, hostname, realname));
        break;
    case 317:
        return (username + RPL_WHOISIDLE(user_nick, sec_away, sign_on));
        break;
    case 318:
        return (username + RPL_ENDOFWHOIS(user_nick));
        break;
    case 319:
        // Potentiellement prefix sur channel_name
        return (username + RPL_WHOISCHANNELS(user_nick, channel_name));
        break;
    case 320:
        return (username + RPL_WHOISSPECIAL(user_nick));
        break;
    case 321:
        return (username + RPL_LISTSTART(null));
        break;
    case 322:
        return (username + RPL_LIST(channel_name, client_count, channel_topic));
        break;
    case 323:
        return (username + RPL_LISTEND(null));
        break;
    case 324:
        return (username + RPL_CHANNELMODEIS(channel_name, mode_string, mode_arguments));
        break;
    case 329:
        return (username + RPL_CREATIONTIME(channel_name, channel_creationTime));
        break;
    case 330:
        return (username + RPL_WHOISACCOUNT(user_nick, user_account));
        break;
    case 331:
        return (username + RPL_NOTOPIC(channel_name));
        break;
    case 332:
        return (username + RPL_TOPIC(channel_name, channel_topic));
        break;
    case 333:
        return (username + RPL_TOPICWHOTIME(channel_name, channel_whoSetTopic, channel_TimeSetTopic));
        break;
    case 336:
        return (username + RPL_INVITELIST(channel_name));
        break;
    case 337:
        return (username + RPL_ENDOFINVITELIST(null));
        break;
    case 341:
        return (username + RPL_INVITING(user_nick, channel_topic));
        break;
    case 346:
        return (username + RPL_INVEXLIST(channel_name, mask_InviteExeptionList));
        break;
    case 347:
        return (username + RPL_ENDOFINVEXLIST(channel_name));
        break;
    case 348:
        return (username + RPL_EXCEPTLIST(channel_name, mask_ExeptionList));
        break;
    case 349:
        return (username + RPL_ENDOFEXCEPTLIST(channel_name));
        break;
    case 351:
        return (username + RPL_VERSION(version, servername, comment));
        break;
    case 353:
        return (username + RPL_NAMREPLY(symbol, channel_name, user_nick));
        break;
    case 366:
        return (username + RPL_ENDOFNAMES(channel_name));
        break;
    case 364:
        return (username + RPL_LINKS(servername, hopcount, infoServer));
        break;
    case 365:
        return (username + RPL_ENDOFLINKS(null));
        break;
    case 367:
        return (username + RPL_BANLIST(channel_name, banMask, banner_nick, ban_timeSet));           //
        break;
    case 368:
        return (username + RPL_ENDOFBANLIST(channel_name));
        break;
    case 369:
        return (username + RPL_ENDOFWHOWAS(user_nick));
        break;
    case 371:
        return (username + RPL_INFO(infoServer));          // Perharps other info
        break;
    case 374:
        return (username + RPL_ENDOFINFO(null));
        break;
    case 375:
        return (username + RPL_MOTDSTART(servername));
        break;
    case 372:
        return (username + RPL_MOTD(motd));
        break;
    case 376:
        return (username + RPL_ENDOFMOTD(null));
        break;
    case 378:
        return (username + RPL_WHOISHOST(user_nick));          //Need to define ip ?
        break;
    case 379:
        return (username + RPL_WHOISMODES(user_nick));         //Need to define available modes ?
        break;
    case 381:
        return (username + RPL_YOUREOPER(null));
        break;
    case 382:
        return (username + RPL_REHASHING(Rehashing_message));
        break;
    case 391:
        return (username + RPL_TIME(servername, actual_time));
        break;
	case 670:
		return (username + RPL_STARTTLS(null));
		break;
	case 671:
		return (username + RPL_WHOISSECURE(user_nick));
		break;
	case 704:
		return (username + RPL_HELPSTART(subject, help_msg));
		break;
	case 705:
		return (username + RPL_HELPTXT(subject, help_msg));
		break;
	case 706:
		return (username + RPL_ENDOFHELP(subject, help_msg));
		break;
	case 900:
		return (username + RPL_LOGGEDIN(user_nick, username, hostname, user_account, username));		// User = username ???
		break;
	case 901:
		return (username + RPL_LOGGEDOUT(user_nick, username, hostname, user_account));
		break;
	case 903:
		return (username + RPL_SASLSUCCESS(null));
		break;
	case 908:
		return (username + RPL_SASLMECHS(SASL_mechanisms));
		break;
	case 400:
        return (username + ERR_UNKNOWNERROR(command, command_info));
        break;
	case 401:
		return (username + ERR_NOSUCHNICK(user_nick));
		break;
	case 402:
		return (username + ERR_NOSUCHSERVER(servername));
		break;
	case 403:
		return (username + ERR_NOSUCHCHANNEL(channel_name));
		break;
	case 404:
		return (username + ERR_CANNOTSENDTOCHAN(channel_name));
		break;
	case 405:
		return (username + ERR_TOOMANYCHANNELS(channel_name));
		break;
	case 406:
		return (username + ERR_WASNOSUCHNICK(null));
		break;
	case 409:
		return (username + ERR_NOORIGIN(null));
		break;
	case 417:
		return (username + ERR_INPUTTOOLONG(null));
		break;
	case 421:
		return (username + ERR_UNKNOWNCOMMAND(command));
		break;
	case 422:
		return (username + ERR_NOMOTD(null));
		break;
    case 431:
		return (username + ERR_NONICKNAMEGIVEN(null));
        break;
	case 432:
		return (username + ERR_ERRONEUSNICKNAME(user_nick));
		break;
	case 433:
		return (username + ERR_NICKNAMEINUSE(user_nick));
		break;
	case 441:
		return (username + ERR_USERNOTINCHANNEL(user_nick, channel_name));
		break;
	case 442:
		return (username + ERR_NOTONCHANNEL(channel_name));
		break;
	case 443:
        return (username + ERR_UNKNOWNERROR(command, command_info));
        break;
	case 451:
		return (username + ERR_NOTREGISTERED(null));
		break;
	case 461:
		return (username + ERR_NEEDMOREPARAMS(command));
		break;
	case 462:
		return (username + ERR_ALREADYREGISTERED(null));
		break;
	case 464:
		return (username + ERR_PASSWDMISMATCH(null));
		break;
	case 465:
		return (username + ERR_YOUREBANNEDCREEP(null));
		break;
	case 471:
		return (username + ERR_CHANNELISFULL(channel_name));
		break;
	case 472:
		return (username + ERR_UNKNOWNMODE(mode_char));
		break;
	case 473:
		return (username + ERR_INVITEONLYCHAN(channel_name));
		break;
	case 474:
		return (username + ERR_BANNEDFROMCHAN(channel_name));
		break;
	case 475:
		return (username + ERR_BADCHANNELKEY(channel_name));
		break;
	case 476:
		return (username + ERR_BADCHANMASK(channel_name));
		break;
	case 481:
		return (username + ERR_NOPRIVILEGES(null));
		break;
	case 482:
		return (username + ERR_CHANOPRIVSNEEDED(channel_name));
		break;
	case 483:
		return (username + ERR_CANTKILLSERVER(null));
		break;
	case 491:
		return (username + ERR_NOOPERHOST(null));
		break;
	case 501:
		return (username + ERR_UMODEUNKNOWNFLAG(null));
		break;
	case 502:
		return (username + ERR_USERSDONTMATCH(null));
		break;
	case 524:
		return (username + ERR_HELPNOTFOUND(subject));
		break;
	case 525:
		return (username + ERR_INVALIDKEY(target));
		break;
	case 691:
		return (username + ERR_STARTTLS(null));
		break;
	case 696:
		return (username + ERR_INVALIDMODEPARAM(target, mode_char, parameter, description));
		break;
	case 723:
		return (username + ERR_NOPRIVS(privilege));
		break;
	case 902:
		return (username + ERR_NICKLOCKED(null));
		break;
	case 904:
		return (username + ERR_SASLFAIL(null));
		break;
	case 905:
		return (username + ERR_SASLTOOLONG(null));
		break;
	case 906:
		return (username + ERR_SASLABORTED(null));
		break;
	case 907:
		return (username + ERR_SASLALREADY(null));
		break;

	default:
        std::cout << "Numeric not found" << std::endl;
        break;
    }
    return ("");
}