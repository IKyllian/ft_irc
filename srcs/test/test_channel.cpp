#include "../../includes/ft_irc.hpp"
#include "../../includes/Channel.hpp"
#include "../../includes/Client.hpp"
#include "../../includes/Server.hpp"
int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	Server server;
	std::vector<std::string> channels_string;
	std::vector<std::string> channels_string2;
	std::vector<std::string> channels_string3;
	std::vector<std::string> channels_string4;
	std::vector<std::string> channels_string5;
	std::vector<std::string> chans;
	std::vector<std::string> mode_parameters;
	std::vector<std::string> topic;
	std::vector<std::string> topic2;
	std::vector<std::string> topic3;
	// Mode Message
	mode_parameters.push_back("chan");
	mode_parameters.push_back("+kit");
	mode_parameters.push_back("1234");
	// mode_parameters.push_back("Kyllian");
	//List of channels
	channels_string.push_back("chan,channel2,test_channel_1234,azeazeojazjpopaozjepoajepoajze4");
	// channels_string.push_back("1234,azerty1234567890,coucou,helloworld");

	//Channel2
	channels_string2.push_back("channel2");
	channels_string2.push_back("azerty1234567890");

	//Channel1
	channels_string3.push_back("chan");
	channels_string3.push_back("1234");


	channels_string4.push_back("Romain");
	channels_string4.push_back("chan");

	channels_string5.push_back("chan");
	channels_string5.push_back("Romain");

	chans.push_back("chan");
	chans.push_back("channel2");

	topic.push_back("chan");
	topic.push_back("Ceci est un topic");

	topic2.push_back("chan");
	topic2.push_back("Ceci est un deuxieme topic");

	topic3.push_back("chan");

	// std::vector<Channel> channels;
	std::string name = "myChannel";
	std::string client_name = "Kyllian";
	std::string client2_name = "Romain";
	std::string user7 = "user7";
    Channel channel(name);
	Client client1(client_name);
	Client client2(client2_name);
	Client client3(user7);

	server.set_user(Client(client_name));
	server.set_user(Client(client2_name));
	server.set_user(Client(user7));

	std::cout << "User size = " << server.get_clients().size() << std::endl;

	// client1.set_user_modes("+ospwioo");

	// std::cout << "Client modes = " << client1.get_user_modes() << std::endl;

	server.command_JOIN(channels_string, &client1);
	server.command_JOIN(channels_string2, &client1);

	std::cout << "Channels size = " << server.get_channels().size() << std::endl;


	// join_command(channels_string, &channels, &client1);
	// join_command(channels_string2, &channels, &client1);

	std::cout << server.get_channels()[0].get_name() << std::endl;
	std::cout << server.get_channels()[1].get_name() << std::endl;

	server.command_MODE_CHAN(&client1, mode_parameters);

	server.command_TOPIC(topic, &client1);
	std::cout << "Topic  = " << server.get_channels()[0].get_topic() << std::endl;


	std::cout << "Password = " << server.get_channels()[0].get_password() << " - Mode = " << server.get_channels()[0].get_channel_modes() << std::endl;

	std::cout << "Password = " << server.get_channels()[0].get_password() << " - Mode = " << server.get_channels()[0].get_channel_modes() << std::endl;

	server.command_INVITE(&client1, channels_string4);
	std::cout << "Invite list size = " << server.get_channels()[0].get_invite_list().size() << std::endl;


	server.command_JOIN(channels_string3, &client1);
	server.command_JOIN(channels_string3, &client2);

	std::cout << "Invite list size = " << server.get_channels()[0].get_invite_list().size() << std::endl;


	server.command_TOPIC(topic2, &client2);
	std::cout << "Topic  = " << server.get_channels()[0].get_topic() << std::endl;
	// server.command_PART(channels_string, &client1);

	// server.command_NAMES(channels_string);
	// server.command_KICK(&client3, channels_string5);
	
	server.command_TOPIC(topic3, &client1);

	server.command_PART(chans, &client2);


	std::cout << "Users size = " << server.get_channels()[0].get_users().size() << std::endl;

	// std::cout << "Channels size = " << server.get_channels().size() << std::endl;


	// channels[0].set_user(&client2);
	// std::cout << "Invite list size = " << channels[0].get_invite_list().size() << std::endl;

	// server.command_PART(channels_string, &client1);

	// std::cout << "Channels size = " << server.get_channels().size() << std::endl;

	// std::cout << server.get_channels()[0].get_users().size() << std::endl;
	// for (std::map<Client*, std::string>::iterator it = server.get_channels()[0].get_users().begin(); it != server.get_channels()[0].get_users().end(); ++it) {
	// 	std::cout << "Users : " << it->first->get_nickname() << std::endl;
	// }

	// std::cout << server.get_channels()[1].get_users().size() << std::endl;
	// for (std::map<Client*, std::string>::iterator it = server.get_channels()[1].get_users().begin(); it != server.get_channels()[1].get_users().end(); ++it) {
	// 	std::cout << "Users : " << it->first->get_nickname() << std::endl;
	// }

	// channels[0].set_user_mode("-iws", &client3);
	
	// channels[0].set_user_mode("+issswkaqsssss", &client1);
	// std::cout << "Modes user1 = " << channels[0].get_users().find(&client1)->second << std::endl;

	// channels[0].set_user_mode("-is", &client1);
	// std::cout << "Modes user1 = " << channels[0].get_users().find(&client1)->second << std::endl;

	// client1.set_nickname("kdelport");

	// std::cout << "New nickname " << client1.get_nickname() << std::endl;
	// std::cout << "Nickname in channel " << channels[0].get_users().find(&client1)->first->get_nickname() << std::endl;

	// channel.ban_user(&client2);
	// for (std::map<Client*, std::string>::iterator it = channel.get_users().begin(); it != channel.get_users().end(); ++it) {
	// 	std::cout << "Users : " << it->first->get_nickname() << std::endl;
	// }
	// for (std::vector<Client*>::iterator it = channel.get_users_ban().begin(); it != channel.get_users_ban().end(); it++) {
	// 	std::cout << "Users Ban : " << (*it)->get_nickname() << std::endl;
	// }

	// channel.ban_user(&client2);
	// for (std::vector<Client*>::iterator it = channel.get_users_ban().begin(); it != channel.get_users_ban().end(); it++) {
	// 	std::cout << "Users Ban : " << (*it)->get_nickname() << std::endl;
	// }
	
	// channel.set_user(&client2);
	// for (std::map<Client*, std::string>::iterator it = channel.get_users().begin(); it != channel.get_users().end(); ++it) {
	// 	std::cout << "Users : " << it->first->get_nickname() << std::endl;
	// }

	// channel.set_user_mode("+issswkaqsssss", user7);

	// channel.set_channel_modes("+isooppkzvccmyy");
	// std::cout << "Modes channel = " << channel.get_channel_modes() << std::endl;

	// channel.set_channel_modes("-kism");
	// std::cout << "Modes channel = " << channel.get_channel_modes() << std::endl;

    return (0);
}
