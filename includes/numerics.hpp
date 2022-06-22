#ifndef     NUMERICS_HPP
# define    NUMERICS_HPP

//												RPL MESSAGES												//

#define RPL_WELCOME(networkname, nick)(" :Welcome to the " + networkname + " Network, " + nick)																															// 001
#define RPL_YOURHOST(servername, version)(" :Your host is " + servername + ", running version " + version)																												// 002
#define RPL_CREATED(datetime)(" :This server was created " + datetime)																																					// 003
#define RPL_MYINFO(servername, version, user_modes, channel_modes)(" " + servername + " " + version + " " + user_modes + " " + channel_modes)																			// 004
#define RPL_ISUPPORT(tokens)(" " + tokens + " :are supported by this server")																																			// 005

#define RPL_BOUNCE(hostname, port, info)(" " + hostname + " " + port + " :" + info)																																		// 010
#define RPL_UMODEIS(user_modes)(" " + user_modes)																																										// 221
#define RPL_LUSERCLIENT(u, i, s)(" :There are " + u + " users and , " + i + " invisible on " + s + " servers")																											// 251
#define RPL_LUSEROP(ops)(" " + ops + " :operator(s) online")																																							// 252
#define RPL_LUSERUNKNOWN(connections)(" " + connections + " :unknown connection(s)")																																	// 253
#define RPL_LUSERCHANNELS(channels)(" " + channels + " :channels formed")																																				// 254
#define RPL_LUSERME(c, s)(" :I have " + c + " clients and " + s + "servers")																																			// 255
#define RPL_ADMINME(server)(" " + server + " :Administrative info")																																						// 256
#define RPL_ADMINLOC1(info)(" :" + info)																																												// 257
#define RPL_ADMINLOC2(info)(" :" + info)																																												// 258
#define RPL_ADMINEMAIL(info)(" :" + info)																																												// 259
#define RPL_TRYAGAIN(command)(" " + command + " :Please wait a while and try again.")													////////																		// 263
#define RPL_LOCALUSERS(u, m)(" " + u + " " + m + " :Current local users " + u + ", max " + m)																															// 265
#define RPL_GLOBALUSERS(u, m)(" " + u + " " + m + " :Current global users " + u + ", max " + m)																															// 266
#define RPL_WHOISCERTFP(nick, fingerprint)(" " + nick + " :has client certificate fingerprint " + fingerprint)																											// 276
#define RPL_NONE(NULL)(NULL + "Undefined format")																																													// 300
#define RPL_AWAY(nick, message)(" " + nick + " :" + message)																																							// 301
#define RPL_USERHOST(reply)(" :" + reply)																																												// 302
#define RPL_UNAWAY(NULL)(NULL + " :You are no longer marked as being away")																																						// 305
#define RPL_NOWAWAY(NULL)(NULL + " :You have been marked as being away")																																							// 306
#define RPL_WHOREPLY(channel, username, host, server, nick, flags, hopcount, realname)(" " + channel + " " + username + " " + host + " " + server + " " + nick + " " + flags + " :" + hopcount + " " + realname)		// 352
#define RPL_ENDOFWHO(mask)(" " + mask + " :End of /WHO list")																																							// 315
#define RPL_WHOISREGNICK(nick)(" " + nick + " :has identified for this nick")																																			// 307
#define RPL_WHOISUSER(nick, username, host, realname)(" " + nick + " " + username + " " + host + " * " + realname)																										// 311
#define RPL_WHOISSERVER(nick, server, server_info)(" " + nick + " " + server + " :" + server_info)																														// 312
#define RPL_WHOISOPERATOR(nick)(" " + nick + " :is an IRC operator")																																					// 313
#define RPL_WHOWASUSER(nick, username, host, realname)(" " + nick + " " + username + " " + host + " * :" + realname)																									// 314
#define RPL_WHOISIDLE(nick, secs, signon)(" " + nick + " " + secs + " " + signon + " :seconds idle, signon time")																										// 317
#define RPL_ENDOFWHOIS(nick)(" " + nick + " :End of /WHOIS list")																																						// 318
#define RPL_WHOISCHANNELS(nick, channel)(" " + nick + " :" + channel)																																					// 319
#define RPL_WHOISSPECIAL(nick)(" " + nick + " :blah blah blah")																																							// 320
#define RPL_LISTSTART(NULL)(NULL + " " + "Channel" + " :Users  Name")					// SKIPPED BY THE SERVER !																													// 321
#define RPL_LIST(channel, client_count, topic)(" " + channel + " " + client_count + " :" + topic)																														// 322
#define RPL_LISTEND(NULL)(NULL + " :End of /LIST")																																													// 323
#define RPL_CHANNELMODEIS(channel, modestring, mode_arguments)(" " + channel + " " + modestring + " " + mode_arguments)																									// 324
#define RPL_CREATIONTIME(channel, creationtime)(" " + channel + " " + creationtime)																																		// 329
#define RPL_WHOISACCOUNT(nick, account)(" " + nick + " " + account + " :is logged in as")																																// 330
#define RPL_NOTOPIC(channel)(" " + channel + " :No topic is set")																																						// 331
#define RPL_TOPIC(channel, topic)(" " + channel + " " + topic)																																							// 332
#define RPL_TOPICWHOTIME(channel, nick, setat)(" " + channel + " " + nick + " " + setat)																																// 333
#define RPL_INVITELIST(channel)(" " + channel)																																											// 336
#define RPL_ENDOFINVITELIST(NULL)(NULL + " :End of /INVITE list")																																									// 337
//338 ???
#define RPL_INVITING(nick, channel)(" " + nick + " " + channel)																																							// 341
#define RPL_INVEXLIST(channel, mask)(" " + channel + " " + mask)																																						// 346
#define RPL_ENDOFINVEXLIST(channel)(" " + channel + " :End of Channel Invite Exception List")																															// 347
#define RPL_EXCEPTLIST(channel, mask)(" " + channel + " " + mask)																																						// 348
#define RPL_ENDOFEXCEPTLIST(channel)(" " + channel + " :End of channel exception list")																																	// 349
#define RPL_VERSION(version, server, comments)(" " + version + " " + server + " :" + comments)																															// 351
#define RPL_NAMREPLY(symbol, channel, nick)(" " + symbol + " " + channel + " :" + nick)																																	// 353
#define RPL_ENDOFNAMES(channel)(" " + channel + " :End of /NAMES list")																																					// 366
#define RPL_LINKS(server, hopcount, server_info)(" * " + server + " :" + hopcount + " " + server_info)																													// 364
#define RPL_ENDOFLINKS(NULL)(NULL + " * " + " :End of /LINKS list")																																								// 365
#define RPL_BANLIST(channel, mask, who, set_ts)(" " + channel + " " + mask + " " + who +  " " + set_ts)																													// 367
#define RPL_ENDOFBANLIST(channel)(" " + channel + " :End of channel ban list")																																			// 368
#define RPL_ENDOFWHOWAS(nick)(" " + nick + " :End of WHOWAS")																																							// 369
#define RPL_INFO(string)(" :" + string)																																													// 371
#define RPL_ENDOFINFO(NULL)(NULL + " :End of INFO list")																																											// 374
#define RPL_MOTDSTART(server)(" :- " + server + " Message of the day - ")																																				// 375
#define RPL_MOTD(motd)(" :" + motd)																																														// 372
#define RPL_ENDOFMOTD(NULL)(NULL + " :End of /MOTD command.")																																										// 376
#define RPL_WHOISHOST(nick)(" " + nick + " :is connecting from *@localhost 127.0.0.1")																																	// 378
#define RPL_WHOISMODES(nick)(" " + nick + " :is using modes +ailosw")																																					// 379
#define RPL_YOUREOPER(NULL)(NULL + " :You are now an IRC operator")																																								// 381
#define RPL_REHASHING(config_file)(" " + config_file + " :Rehashing")																																					// 382
#define RPL_TIME(server, time)(" " + server + " :" + time)																																								// 391
#define RPL_STARTTLS(NULL)(NULL + " :STARTTLS successful, proceed with TLS handshake")			//Ici																																	// 670									
#define RPL_WHOISSECURE(nick)(" " + nick + " :is using a secure connection")																																			// 671						
#define RPL_HELPSTART(subject, str)(" " + subject + " :" + str)																																							// 704
#define RPL_HELPTXT(subject, str)(" " + subject + " :" + str)																																							// 705
#define RPL_ENDOFHELP(subject, str)(" " + subject + " :" + str)																																							// 706
#define RPL_LOGGEDIN(nick, user, host, account, username)(" " + nick + "!" + user + "@" + host + " " + account + " :You are now logged in as " + username)																// 900																						
#define RPL_LOGGEDOUT(nick, user, host, account)(" " + nick + "!" + user + "@" + host + " " + account + " :You are now logged out")																						// 901																	
#define RPL_SASLSUCCESS(NULL)(NULL + " :SASL authentication successful")																																							// 903
#define RPL_SASLMECHS(mechanisms)(" " + mechanisms + " :are available SASL mechanisms")																																	// 908					

//												ERROR MESSAGES												//

#define ERR_UNKNOWNERROR(command, info)(" " + command + " :" + info)																																					// 400					
#define ERR_NOSUCHNICK(nickname) (" " + nickname + " :No such nick/channel")																																				// 401					
#define ERR_NOSUCHSERVER(server_name)(" " + server_name + " :No such server")																																			// 402							
#define ERR_NOSUCHCHANNEL(channel) (" " + channel + " :No such channel")																																				// 403						
#define ERR_CANNOTSENDTOCHAN(channel)(" " + channel + " :Cannot send to channel")																																		// 404								
#define ERR_TOOMANYCHANNELS(channel)(" " + channel + " :You have joined too many channels")																																// 405										
#define ERR_WASNOSUCHNICK(NULL)(NULL + " :There was no such nickname")																																								// 406		
#define ERR_NOORIGIN(NULL)(NULL + " :No origin specified")																																											// 409
#define ERR_INPUTTOOLONG(NULL)(NULL + " :Input line was too long")																																									// 417	
#define ERR_UNKNOWNCOMMAND(command)(" " + command + " :Unknown command")																																				// 421							
#define ERR_NOMOTD(NULL)(NULL + " :MOTD File is missing")																																											// 422
#define ERR_ERRONEUSNICKNAME(nickname)(" " + nickname + " :Erroneus nickname")																																			// 432								
#define ERR_NICKNAMEINUSE(nickname)(" " + nickname + " :Nickname is already in use")																																	// 433										
#define ERR_USERNOTINCHANNEL(nickname, channel)(" " + nickname + " " + channel + " :They aren't on that channel")																										// 441																	
#define ERR_NOTONCHANNEL(channel)(" " + channel + " :You're not on that channel")																																		// 442									
#define ERR_USERONCHANNEL(nickname, channel)(" " + nickname + " " + channel + " :is already on channel")																												// 443															
#define ERR_NOTREGISTERED(NULL)(NULL + " :You have not registered")																																								// 451			
#define ERR_NEEDMOREPARAMS(command)(" " + command + " :Not enough parameters")																																			// 461								
#define ERR_ALREADYREGISTERED(NULL)(NULL + " :You may not reregister")																																						// 462					
#define ERR_PASSWDMISMATCH(NULL)(NULL + " :Password incorrect")																																									// 464		
#define ERR_YOUREBANNEDCREEP(NULL)(NULL + " :You are banned from this server.")																																					// 465						
#define ERR_CHANNELISFULL(channel)(" " + channel + " :Cannot join channel (+l)")																																		// 471									
#define ERR_UNKNOWNMODE(modechar)(" " + modechar + " :is unknown mode char to me")																																		// 472									
#define ERR_INVITEONLYCHAN(channel)(" " + channel + " :Cannot join channel (+i)")																																		// 473									
#define ERR_BANNEDFROMCHAN(channel)(" " + channel + " :Cannot join channel (+b)")																																		// 474									
#define ERR_BADCHANNELKEY(channel)(" " + channel + " :Cannot join channel (+k)")																																		// 475									
#define ERR_BADCHANMASK(channel)(" " + channel + " :Bad Channel Mask")																																					// 476						
#define ERR_NOPRIVILEGES(NULL)(NULL + " :Permission Denied- You're not an IRC operator")																																			// 481								
#define ERR_CHANOPRIVSNEEDED(channel)(" " + channel + " :You're not channel operator")																																	// 482										
#define ERR_CANTKILLSERVER(NULL)(NULL + " :You can't kill a server!")																																								// 483			
#define ERR_NOOPERHOST(NULL)(NULL + " :No O-lines for your host")																																									// 491		
#define ERR_UMODEUNKNOWNFLAG(NULL)(NULL + " :Unknown MODE flag")																																									// 501		
#define ERR_USERSDONTMATCH(NULL)(NULL + " :Can't change mode for other users")																																						// 502					
#define ERR_HELPNOTFOUND(subject)(" " + subject + " :No help available on this topic")																																	// 524										
#define ERR_INVALIDKEY(target_chan)(" " + target_chan + " :Key is not well-formed")																																		// 525									
#define ERR_STARTTLS(NULL)(NULL + " :STARTTLS failed (Wrong moon phase)")																																					// 691						
#define ERR_INVALIDMODEPARAM(target, mode, parameter, description)(" " + target, " " + mode + " " + parameter + " :" + description)																						// 696																					
#define ERR_NOPRIVS(priv)(" " + priv + " :Insufficient oper privileges.")																																				// 723							
#define ERR_NICKLOCKED(NULL)(NULL + " :You must use a nick assigned to you")																																						// 902					
#define ERR_SASLFAIL(NULL)(NULL + " :SASL authentication failed")																																									// 904		
#define ERR_SASLTOOLONG(NULL)(NULL + " :SASL message too long")																																									// 905		
#define ERR_SASLABORTED(NULL)(NULL + " :SASL authentication aborted")																																								// 906			
#define ERR_SASLALREADY(NULL)(NULL + " :You have already authenticated using SASL")																																				// 907							
#define ERR_NONICKNAMEGIVEN(NULL)(NULL + " :No nickname given")	                      
#define ERR_NORECIPIENT(command)(": No recipient given " + command)	                     
#define ERR_NOTEXTTOSEND(NULL)(NULL + ": No recipient given ")	                      

#endif
