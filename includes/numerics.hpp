#ifndef     NUMERICS_HPP
# define    NUMERICS_HPP

#define NETWORK_NAME "KIKIKAKARORO"

//												RPL MESSAGES												//

#define RPL_WELCOME(networkname, nick)(" :Welcome to the " + networkname + " Network, " + nick + "\n")																															// 001
#define RPL_YOURHOST(servername, version)(" :Your host is " + servername + ", running version " + version + "\n")																												// 002
#define RPL_CREATED(datetime)(" :This server was created " + datetime + "\n")																																					// 003
#define RPL_MYINFO(servername, version, user_modes, channel_modes)(" " + servername + " " + version + " " + user_modes + " " + channel_modes + "\n")																			// 004
#define RPL_ISUPPORT(tokens)(" " + tokens + " :are supported by this server" + "\n")																																			// 005

#define RPL_BOUNCE(hostname, port, info)(" " + hostname + " " + port + " :" + info + "\n")																																		// 010
#define RPL_UMODEIS(user_modes)(" " + user_modes + "\n")																																										// 221
#define RPL_LUSERCLIENT(u, i, s)(" :There are " + u + " users and , " + i + " invisible on " + s + " servers" + "\n")																											// 251
#define RPL_LUSEROP(ops)(" " + ops + " :operator(s) online" + "\n")																																							// 252
#define RPL_LUSERUNKNOWN(connections)(" " + connections + " :unknown connection(s)" + "\n")																																	// 253
#define RPL_LUSERCHANNELS(channels)(" " + channels + " :channels formed" + "\n")																																				// 254
#define RPL_LUSERME(c, s)(" :I have " + c + " clients and " + s + "servers" + "\n")																																			// 255
#define RPL_ADMINME(server)(" " + server + " :Administrative info" + "\n")																																						// 256
#define RPL_ADMINLOC1(info)(" :" + info + "\n")																																												// 257
#define RPL_ADMINLOC2(info)(" :" + info + "\n")																																												// 258
#define RPL_ADMINEMAIL(info)(" :" + info + "\n")																																												// 259
#define RPL_TRYAGAIN(command)(" " + command + " :Please wait a while and try again." + "\n")																																	// 263
#define RPL_LOCALUSERS(u, m)(" " + u + " " + m + " :Current local users " + u + ", max " + m + "\n")																															// 265
#define RPL_GLOBALUSERS(u, m)(" " + u + " " + m + " :Current global users " + u + ", max " + m + "\n")																															// 266
#define RPL_WHOISCERTFP(nick, fingerprint)(" " + nick + " :has client certificate fingerprint " + fingerprint + "\n")																											// 276
#define RPL_NONE()("Undefined format" + "\n")																																													// 300
#define RPL_AWAY(nick, message)(" " + nick + " :" + message + "\n")																																							// 301
#define RPL_USERHOST(reply)(" :" + reply + "\n")																																												// 302
#define RPL_UNAWAY()(" :You are no longer marked as being away" + "\n")																																						// 305
#define RPL_NOWAWAY()(" :You have been marked as being away" + "\n")																																							// 306
#define RPL_WHOREPLY(channel, username, host, server, nick, flags, hopcount, realname)(" " + channel + " " + username + " " + host + " " + server + " " + nick + " " + flags + " :" + hopcount + " " + realname + "\n")		// 352
#define RPL_ENDOFWHO(mask)(" " + mask + " :End of WHO list" + "\n")																																							// 315
#define RPL_WHOISREGNICK(nick)(" " + nick + " :has identified for this nick" + "\n")																																			// 307
#define RPL_WHOISUSER(nick, username, host, realname)(" " + nick + " " + username + " " + host + " * :" + realname + "\n")																										// 311
#define RPL_WHOISSERVER(nick, server, server_info)(" " + nick + " " + server + " :" + server_info + "\n")																														// 312
#define RPL_WHOISOPERATOR(nick)(" " + nick + " :is an IRC operator" + "\n")																																					// 313
#define RPL_WHOWASUSER(nick, username, host, realname)(" " + nick + " " + username + " " + host + " * :" + realname + "\n")																									// 314
#define RPL_WHOISIDLE(nick, secs, signon)(" " + nick + " " + secs + " " + signon + " :seconds idle, signon time" + "\n")																										// 317
#define RPL_ENDOFWHOIS(nick)(" " + nick + " :End of /WHOIS list" + "\n")																																						// 318
#define RPL_WHOISCHANNELS(nick, channel)(" " + nick + " :" + channel + "\n")																																					// 319
#define RPL_WHOISSPECIAL(nick)(" " + nick + " :blah blah blah" + "\n")																																							// 320
#define RPL_LISTSTART()(" " + "Channel" + " :Users  Name" + "\n")					// SKIPPED BY THE SERVER !																													// 321
#define RPL_LIST(channel, client_count, topic)(" " + channel + " " + client_count + " :" + topic + "\n")																														// 322
#define RPL_LISTEND()(" :End of /LIST" + "\n")																																													// 323
#define RPL_CHANNELMODEIS(channel, modestring, mode_arguments)(" " + channel + " " + modestring + " " + mode_arguments + "\n")																									// 324
#define RPL_CREATIONTIME(channel, creationtime)(" " + channel + " " + creationtime + "\n")																																		// 329
#define RPL_WHOISACCOUNT(nick, account)(" " + nick + " " + account + " :is logged in as" + "\n")																																// 330
#define RPL_NOTOPIC(channel)(" " + channel + " :No topic is set" + "\n")																																						// 331
#define RPL_TOPIC(channel, topic)(" " + channel + " :" + topic + "\n")																																							// 332
#define RPL_TOPICWHOTIME(channel, nick, setat)(" " + channel + " " + nick + " " + setat + "\n")																																// 333
#define RPL_INVITELIST(channel)(" " + channel + "\n")																																											// 336
#define RPL_ENDOFINVITELIST()(" :End of /INVITE list" + "\n")																																									// 337
#define RPL_INVITING(nick, channel)(" " + nick + " " + channel + "\n")																																							// 341
#define RPL_INVEXLIST(channel, mask)(" " + channel + " " + mask + "\n")																																						// 346
#define RPL_ENDOFINVEXLIST(channel)(" " + channel + " :End of Channel Invite Exception List" + "\n")																															// 347
#define RPL_EXCEPTLIST(channel, mask)(" " + channel + " " + mask + "\n")																																						// 348
#define RPL_ENDOFEXCEPTLIST(channel)(" " + channel + " :End of channel exception list" + "\n")																																	// 349
#define RPL_VERSION(version, server, comments)(" " + version + " " + server + " :" + comments + "\n")																															// 351
#define RPL_NAMREPLY(symbol, channel, nick)(" " + symbol + " " + channel + " :" + nick + "\n")																																	// 353
#define RPL_ENDOFNAMES(channel)(" " + channel + " :End of /NAMES list" + "\n")																																					// 366
#define RPL_LINKS(server, hopcount, server_info)(" * " + server + " :" + hopcount + " " + server_info + "\n")																													// 364
#define RPL_ENDOFLINKS()(" * " + " :End of /LINKS list" + "\n")																																								// 365
#define RPL_BANLIST(channel, mask, who, set_ts)(" " + channel + " " + mask + " " + who +  " " + set_ts + "\n")																													// 367
#define RPL_ENDOFBANLIST(channel)(" " + channel + " :End of channel ban list" + "\n")																																			// 368
#define RPL_ENDOFWHOWAS(nick)(" " + nick + " :End of WHOWAS" + "\n")																																							// 369
#define RPL_INFO(string)(" :" + string + "\n")																																													// 371
#define RPL_ENDOFINFO()(" :End of INFO list" + "\n")																																											// 374
#define RPL_MOTDSTART(server)(" :- " + server + " Message of the day - " + "\n")																																				// 375
#define RPL_MOTD(motd)(" :" + motd + "\n")																																														// 372
#define RPL_ENDOFMOTD()(" :End of /MOTD command." + "\n")																																										// 376
#define RPL_WHOISHOST(nick)(" " + nick + " :is connecting from *@localhost 127.0.0.1" + "\n")																																	// 378
#define RPL_WHOISMODES(nick)(" " + nick + " :is using modes +ailosw" + "\n")																																					// 379
#define RPL_YOUREOPER()(" :You are now an IRC operator" + "\n")																																								// 381
#define RPL_REHASHING(config_file)(" " + config_file + " :Rehashing" + "\n")																																					// 382
#define RPL_TIME(server, time)(" " + server + " :" + time + "\n")																																								// 391
#define RPL_STARTTLS()(" :STARTTLS successful, proceed with TLS handshake" + "\n")																																				// 670									
#define RPL_WHOISSECURE(nick)(" " + nick + " :is using a secure connection" + "\n")																																			// 671						
#define RPL_HELPSTART(subject, str)(" " + subject + " :" + str + "\n")																																							// 704
#define RPL_HELPTXT(subject, str)(" " + subject + " :" + str + "\n")																																							// 705
#define RPL_ENDOFHELP(subject, str)(" " + subject + " :" + str + "\n")																																							// 706
#define RPL_LOGGEDIN(nick, user, host, account, username)(" " + nick + "!" + user + "@" + host + " " + account + " :You are now logged in as " + username + "\n")																// 900																						
#define RPL_LOGGEDOUT(nick, user, host, account)(" " + nick + "!" + user + "@" + host + " " + account + " :You are now logged out" + "\n")																						// 901																	
#define RPL_SASLSUCCESS()(" :SASL authentication successful" + "\n")																																							// 903
#define RPL_SASLMECHS(mechanisms)(" " + mechanisms + " :are available SASL mechanisms" + "\n")																																	// 908					

//												ERROR MESSAGES												//

#define ERR_UNKNOWNERROR (command, info)(" " + command + " :" + info + "\n")																																					// 400					
#define ERR_NOSUCHNICK(nickname) (" " + nickname + " :No such nick/channel" + "\n")																																				// 401					
#define ERR_NOSUCHSERVER(server_name)(" " + server_name + " :No such server" + "\n")																																			// 402							
#define ERR_NOSUCHCHANNEL(channel) (" " + nickname + " :No such channel" + "\n")																																				// 403						
#define ERR_CANNOTSENDTOCHAN(channel)(" " + channel + " :Cannot send to channel" + "\n")																																		// 404								
#define ERR_TOOMANYCHANNELS(channel)(" " + channel + " :You have joined too many channels" + "\n")																																// 405										
#define ERR_WASNOSUCHNICK() (" :There was no such nickname" + "\n")																																								// 406		
#define ERR_NOORIGIN ()(" :No origin specified" + "\n")																																											// 409
#define ERR_INPUTTOOLONG ()(" :Input line was too long" + "\n")																																									// 417	
#define ERR_UNKNOWNCOMMAND (command)(" " + command + " :Unknown command" + "\n")																																				// 421							
#define ERR_NOMOTD ()(" :MOTD File is missing" + "\n")																																											// 422
#define ERR_ERRONEUSNICKNAME (nickname)(" " + nickname + " :Erroneus nickname" + "\n")																																			// 432								
#define ERR_NICKNAMEINUSE (nickname)(" " + nickname + " :Nickname is already in use" + "\n")																																	// 433										
#define ERR_USERNOTINCHANNEL (nickname, channel)(" " + nickname + " " + channel + " :They aren't on that channel" + "\n")																										// 441																	
#define ERR_NOTONCHANNEL (channel)(" " + channel + " :You're not on that channel" + "\n")																																		// 442									
#define ERR_USERONCHANNEL (nickname, channel)(" " + nickname + " " + channel + " :is already on channel" + "\n")																												// 443															
#define ERR_NOTREGISTERED ()(" :You have not registered" + "\n")																																								// 451			
#define ERR_NEEDMOREPARAMS (command)(" " + command + " :Not enough parameters" + "\n")																																			// 461								
#define ERR_ALREADYREGISTERED (nickname)(" :You may not reregister" + "\n")																																						// 462					
#define ERR_PASSWDMISMATCH ()(" :Password incorrect" + "\n")																																									// 464		
#define ERR_YOUREBANNEDCREEP ()(" :You are banned from this server." + "\n")																																					// 465						
#define ERR_CHANNELISFULL (channel)(" " + channel + " :Cannot join channel (+l)" + "\n")																																		// 471									
#define ERR_UNKNOWNMODE (modechar)(" " + modechar + " :is unknown mode char to me" + "\n")																																		// 472									
#define ERR_INVITEONLYCHAN (channel)(" " + channel + " :Cannot join channel (+i)" + "\n")																																		// 473									
#define ERR_BANNEDFROMCHAN (channel)(" " + channel + " :Cannot join channel (+b)" + "\n")																																		// 474									
#define ERR_BADCHANNELKEY (channel)(" " + channel + " :Cannot join channel (+k)" + "\n")																																		// 475									
#define ERR_BADCHANMASK (channel)(" " + channel + " :Bad Channel Mask" + "\n")																																					// 476						
#define ERR_NOPRIVILEGES ()(" :Permission Denied- You're not an IRC operator" + "\n")																																			// 481								
#define ERR_CHANOPRIVSNEEDED (channel)(" " + channel + " :You're not channel operator" + "\n")																																	// 482										
#define ERR_CANTKILLSERVER ()(" :You cant kill a server!" + "\n")																																								// 483			
#define ERR_NOOPERHOST ()(" :No O-lines for your host" + "\n")																																									// 491		
#define ERR_UMODEUNKNOWNFLAG ()(" :Unknown MODE flag" + "\n")																																									// 501		
#define ERR_USERSDONTMATCH ()(" :Cant change mode for other users" + "\n")																																						// 502					
#define ERR_HELPNOTFOUND (subject)(" " + subject + " :No help available on this topic" + "\n")																																	// 524										
#define ERR_INVALIDKEY (target_chan)(" " + target_chan + " :Key is not well-formed" + "\n")																																		// 525									
#define ERR_STARTTLS (cannel)(" :STARTTLS failed (Wrong moon phase)" + "\n")																																					// 691						
#define ERR_INVALIDMODEPARAM (target, mode, parameter, description)(" " + target, " " + mode + " " + parameter + " :" + description + "\n")																						// 696																					
#define ERR_NOPRIVS (priv)(" " + priv + " :Insufficient oper privileges." + "\n")																																				// 723							
#define ERR_NICKLOCKED ()(" :You must use a nick assigned to you" + "\n")																																						// 902					
#define ERR_SASLFAIL ()(" :SASL authentication failed" + "\n")																																									// 904		
#define ERR_SASLTOOLONG ()(" :SASL message too long" + "\n")																																									// 905		
#define ERR_SASLABORTED ()(" :SASL authentication aborted" + "\n")																																								// 906			
#define ERR_SASLALREADY ()(" :You have already authenticated using SASL" + "\n")																																				// 907							

#endif
