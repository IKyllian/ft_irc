#include "../includes/numerics.hpp"
#include "../includes/ft_irc.hpp"
#include "../includes/Server.hpp"
#include "../includes/Client.hpp"
#include "../includes/Message.hpp"
#include "../includes/Channel.hpp"

std::string ft_print_numerics(/*User &user, Server &server, Channel &channel, Message &message*/ int nb_message)
{
    (void) nb_message;
    return "fonction juste pour que ca compile en attendant d'avoir tout modif";
}


std::string Server::print_numerics(int num, Client &sender, Client &receiver, Channel *channel, Message *message)
{
    (void) num;
    (void) sender;
    (void) receiver;
    (void) channel;
    (void) message;



    std::string client_name = "weechat";
    std::string user_flags = "H*";                       //H for present, G for gone, OPTIONAL * for server operator, member prefix, usermode
    std::string user_fingerprint = "fingerprint"; //wtf is this shit ?
    std::string hopcount = "5";                                 //nb of intermediate server 
    std::string sec_away = "353";                        // seconds since last active
    std::string sign_on = "666";                         // unix timestamp, when joined the network
	std::string privilege = "Oper priv";


    //              user VAR               //
    std::string username = sender.get_username(); //"Kyllian";
    std::string user_account = sender.get_username();//"Kdolper";
    std::string realname =  sender.get_realname();//"Kyllian";
    std::string user_nick = sender.get_nickname();//"Ikyllian";
    std::string user_modes = sender.get_user_modes();// "iorw";
//PAS DANS LA CLASSE
    std::string away_message = sender.get_away_msg(); // "F*** this sh** i'm out";
//UPDATE 16/05

    //              SERVER VAR              //
    std::string network_name = get_network_name();//NETWORK_NAME;
    std::string hostname = get_hostname();//"KKR";
    std::string port = get_port();//"127.0.0.1";
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

    switch (num)
    {
    case 1:
        return (client_name + RPL_WELCOME(network_name, user_nick));
        
    case 2:
        return (client_name + RPL_YOURHOST(network_name, user_nick));
        
    case 3:
        return (client_name + RPL_CREATED(datetime));
        
    case 4:
        return (client_name + RPL_MYINFO(servername, version, user_modes, channel_modes));
        
    case 5:
        return (client_name + RPL_ISUPPORT(token));           //Need to create token: cf https://modern.ircdocs.horse/#rplisupport-005
        
    case 10:
        return (client_name + RPL_BOUNCE(hostname, port, infoServer));
        
    case 221:
        return (client_name + RPL_UMODEIS(user_modes));
        
    case 251:
        return (client_name + RPL_LUSERCLIENT(nb_user, invisible_user, server_connected));
        
    case 252:
        return (client_name + RPL_LUSEROP(nb_operator));
        
    case 253:
        return (client_name + RPL_LUSERUNKNOWN(connexion));
        
    case 254:
        return (client_name + RPL_LUSERCHANNELS(nb_channel));
        
    case 255:
        return (client_name + RPL_LUSERME(nb_clients, server_connected));
        
    case 256:
        return (client_name + RPL_ADMINME(servername));
        
    case 257:
        return (client_name + RPL_ADMINLOC1(locationServer));
        
    case 258:
        return (client_name + RPL_ADMINLOC2(hostInfo));
        
    case 259:
        return (client_name + RPL_ADMINEMAIL(hostMail));
        
    case 263:
        return (client_name + RPL_TRYAGAIN(command));
        
    case 265:
        return (client_name + RPL_LOCALUSERS(local_user, max_user));
        
    case 266:
        return (client_name + RPL_GLOBALUSERS(global_user, max_user));
        
    case 276:
        return (client_name + RPL_WHOISCERTFP(user_nick, user_fingerprint));
        
    case 300:
        return (client_name + RPL_NONE(null));
        
    case 301:
        return (client_name + RPL_AWAY(user_nick, away_message));
        
    case 302:
        return (client_name + RPL_USERHOST(command));         //NEED TO CREATE A MESSAGE cf: https://modern.ircdocs.horse/#rpluserhost-302
        
    case 305:
        return (client_name + RPL_UNAWAY(null));
        
    case 306:
        return (client_name + RPL_NOWAWAY(null));
        
    case 352:
        return (client_name + RPL_WHOREPLY(channel_name, username, hostname, servername, user_nick, user_flags, hopcount, realname));
        
    case 315:
        return (client_name + RPL_ENDOFWHO(mask));
        
    case 307:
        return (client_name + RPL_WHOISREGNICK(user_nick));
        
    case 311:
        return (client_name + RPL_WHOISUSER(user_nick, username, hostname, realname));
        
    case 312:
        return (client_name + RPL_WHOISSERVER(user_nick, servername, infoServer));
        
    case 313:
        return (client_name + RPL_WHOISOPERATOR(user_nick));
        
    case 314:
        return (client_name + RPL_WHOWASUSER(user_nick, username, hostname, realname));
        
    case 317:
        return (client_name + RPL_WHOISIDLE(user_nick, sec_away, sign_on));
        
    case 318:
        return (client_name + RPL_ENDOFWHOIS(user_nick));
        
    case 319:
        // Potentiellement prefix sur channel_name
        return (client_name + RPL_WHOISCHANNELS(user_nick, channel_name));
        
    case 320:
        return (client_name + RPL_WHOISSPECIAL(user_nick));
        
    case 321:
        return (client_name + RPL_LISTSTART(null));
        
    case 322:
        return (client_name + RPL_LIST(channel_name, client_count, channel_topic));
        
    case 323:
        return (client_name + RPL_LISTEND(null));
        
    case 324:
        return (client_name + RPL_CHANNELMODEIS(channel_name, mode_string, mode_arguments));
        
    case 329:
        return (client_name + RPL_CREATIONTIME(channel_name, channel_creationTime));
        
    case 330:
        return (client_name + RPL_WHOISACCOUNT(user_nick, user_account));
        
    case 331:
        return (client_name + RPL_NOTOPIC(channel_name));
        
    case 332:
        return (client_name + RPL_TOPIC(channel_name, channel_topic));
        
    case 333:
        return (client_name + RPL_TOPICWHOTIME(channel_name, channel_whoSetTopic, channel_TimeSetTopic));
        
    case 336:
        return (client_name + RPL_INVITELIST(channel_name));
        
    case 337:
        return (client_name + RPL_ENDOFINVITELIST(null));
        
    case 341:
        return (client_name + RPL_INVITING(user_nick, channel_topic));
        
    case 346:
        return (client_name + RPL_INVEXLIST(channel_name, mask_InviteExeptionList));
        
    case 347:
        return (client_name + RPL_ENDOFINVEXLIST(channel_name));
        
    case 348:
        return (client_name + RPL_EXCEPTLIST(channel_name, mask_ExeptionList));
        
    case 349:
        return (client_name + RPL_ENDOFEXCEPTLIST(channel_name));
        
    case 351:
        return (client_name + RPL_VERSION(version, servername, comment));
        
    case 353:
        return (client_name + RPL_NAMREPLY(symbol, channel_name, user_nick));
        
    case 366:
        return (client_name + RPL_ENDOFNAMES(channel_name));
        
    case 364:
        return (client_name + RPL_LINKS(servername, hopcount, infoServer));
        
    case 365:
        return (client_name + RPL_ENDOFLINKS(null));
        
    case 367:
        return (client_name + RPL_BANLIST(channel_name, banMask, banner_nick, ban_timeSet));           //
        
    case 368:
        return (client_name + RPL_ENDOFBANLIST(channel_name));
        
    case 369:
        return (client_name + RPL_ENDOFWHOWAS(user_nick));
        
    case 371:
        return (client_name + RPL_INFO(infoServer));          // Perharps other info
        
    case 374:
        return (client_name + RPL_ENDOFINFO(null));
        
    case 375:
        return (client_name + RPL_MOTDSTART(servername));
        
    case 372:
        return (client_name + RPL_MOTD(motd));
        
    case 376:
        return (client_name + RPL_ENDOFMOTD(null));
        
    case 378:
        return (client_name + RPL_WHOISHOST(user_nick));          //Need to define ip ?
        
    case 379:
        return (client_name + RPL_WHOISMODES(user_nick));         //Need to define available modes ?
        
    case 381:
        return (client_name + RPL_YOUREOPER(null));
        
    case 382:
        return (client_name + RPL_REHASHING(Rehashing_message));
        
    case 391:
        return (client_name + RPL_TIME(servername, actual_time));
        
	case 670:
		return (client_name + RPL_STARTTLS(null));
		
	case 671:
		return (client_name + RPL_WHOISSECURE(user_nick));
		
	case 704:
		return (client_name + RPL_HELPSTART(subject, help_msg));
		
	case 705:
		return (client_name + RPL_HELPTXT(subject, help_msg));
		
	case 706:
		return (client_name + RPL_ENDOFHELP(subject, help_msg));
		
	case 900:
		return (client_name + RPL_LOGGEDIN(user_nick, username, hostname, user_account, username));		// User = username ???
		
	case 901:
		return (client_name + RPL_LOGGEDOUT(user_nick, username, hostname, user_account));
		
	case 903:
		return (client_name + RPL_SASLSUCCESS(null));
		
	case 908:
		return (client_name + RPL_SASLMECHS(SASL_mechanisms));
		
	case 400:
        return (client_name + ERR_UNKNOWNERROR(command, command_info));
        
	case 401:
		return (client_name + ERR_NOSUCHNICK(user_nick));
		
	case 402:
		return (client_name + ERR_NOSUCHSERVER(servername));
		
	case 403:
		return (client_name + ERR_NOSUCHCHANNEL(channel_name));
		
	case 404:
		return (client_name + ERR_CANNOTSENDTOCHAN(channel_name));
		
	case 405:
		return (client_name + ERR_TOOMANYCHANNELS(channel_name));
		
	case 406:
		return (client_name + ERR_WASNOSUCHNICK(null));
		
	case 409:
		return (client_name + ERR_NOORIGIN(null));

    case 411:
        return (client_name + ERR_NORECIPIENT(command));

    case 412:
        return (client_name + ERR_NOTEXTTOSEND(null));

    case 417:
        return (client_name + ERR_INPUTTOOLONG(null));
		
	case 421:
		return (client_name + ERR_UNKNOWNCOMMAND(command));
		
	case 422:
		return (client_name + ERR_NOMOTD(null));
		
    case 431:
		return (client_name + ERR_NONICKNAMEGIVEN(null));
        
	case 432:
		return (client_name + ERR_ERRONEUSNICKNAME(user_nick));
		
	case 433:
		return (client_name + ERR_NICKNAMEINUSE(user_nick));
		
	case 441:
		return (client_name + ERR_USERNOTINCHANNEL(user_nick, channel_name));
		
	case 442:
		return (client_name + ERR_NOTONCHANNEL(channel_name));
		
	case 443:
        return (client_name + ERR_UNKNOWNERROR(command, command_info));
        
	case 451:
		return (client_name + ERR_NOTREGISTERED(null));
		
	case 461:
		return (client_name + ERR_NEEDMOREPARAMS(command));
		
	case 462:
		return (client_name + ERR_ALREADYREGISTERED(null));
		
	case 464:
		return (client_name + ERR_PASSWDMISMATCH(null));
		
	case 465:
		return (client_name + ERR_YOUREBANNEDCREEP(null));
		
	case 471:
		return (client_name + ERR_CHANNELISFULL(channel_name));
		
	case 472:
		return (client_name + ERR_UNKNOWNMODE(mode_char));
		
	case 473:
		return (client_name + ERR_INVITEONLYCHAN(channel_name));
		
	case 474:
		return (client_name + ERR_BANNEDFROMCHAN(channel_name));
		
	case 475:
		return (client_name + ERR_BADCHANNELKEY(channel_name));
		
	case 476:
		return (client_name + ERR_BADCHANMASK(channel_name));
		
	case 481:
		return (client_name + ERR_NOPRIVILEGES(null));
		
	case 482:
		return (client_name + ERR_CHANOPRIVSNEEDED(channel_name));
		
	case 483:
		return (client_name + ERR_CANTKILLSERVER(null));
		
	case 491:
		return (client_name + ERR_NOOPERHOST(null));
		
	case 501:
		return (client_name + ERR_UMODEUNKNOWNFLAG(null));
		
	case 502:
		return (client_name + ERR_USERSDONTMATCH(null));
		
	case 524:
		return (client_name + ERR_HELPNOTFOUND(subject));
		
	case 525:
		return (client_name + ERR_INVALIDKEY(target));
		
	case 691:
		return (client_name + ERR_STARTTLS(null));
		
	case 696:
		return (client_name + ERR_INVALIDMODEPARAM(target, mode_char, parameter, description));
		
	case 723:
		return (client_name + ERR_NOPRIVS(privilege));
		
	case 902:
		return (client_name + ERR_NICKLOCKED(null));
		
	case 904:
		return (client_name + ERR_SASLFAIL(null));
		
	case 905:
		return (client_name + ERR_SASLTOOLONG(null));
		
	case 906:
		return (client_name + ERR_SASLABORTED(null));
		
	case 907:
		return (client_name + ERR_SASLALREADY(null));
		

	default:
        std::cout << "Numeric not found" << std::endl;
        break;
        
    }
    return ("");
}