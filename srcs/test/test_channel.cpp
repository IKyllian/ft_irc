#include "../../includes/ft_irc.hpp"
#include "../../includes/Channel.hpp"
#include "../../includes/Client.hpp"
int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	std::vector<std::string> channels_string;
	std::vector<std::string> channels_string2;
	channels_string.push_back("chan,channel2,test_channel_1234,azeazeojazjpopaozjepoajepoajze4");
	channels_string.push_back("1234,azerty1234567890,coucou,helloworld");
	channels_string2.push_back("channel2");
	channels_string2.push_back("azerty1234567890");
	// join_command(channels);
	std::vector<Channel> channels;
	std::string name = "myChannel";
	std::string client_name = "Kyllian";
	std::string client2_name = "Romain";
	std::string user7 = "user7";
    Channel channel(name);
	Client client1(client_name);
	Client client2(client2_name);
	Client client3(user7);

	join_command(channels_string, &channels, &client1);
	join_command(channels_string2, &channels, &client1);

	std::cout << channels[0].get_name() << std::endl;
	std::cout << channels[1].get_name() << std::endl;

	std::map<std::string, std::string> mymap;

	// channel.set_user(&client1);

	channels[0].set_channel_modes("+i");

	// channels[0].add_invite(&client2);
	// std::cout << "Invite list size = " << channels[0].get_invite_list().size() << std::endl;
	// channels[0].set_user(&client2);
	// std::cout << "Invite list size = " << channels[0].get_invite_list().size() << std::endl;

	std::cout << channels[0].get_users().size() << std::endl;
	for (std::map<Client*, std::string>::iterator it = channels[0].get_users().begin(); it != channels[0].get_users().end(); ++it) {
		std::cout << "Users : " << it->first->get_nickname() << std::endl;
	}

	std::cout << channels[1].get_users().size() << std::endl;
	for (std::map<Client*, std::string>::iterator it = channels[1].get_users().begin(); it != channels[1].get_users().end(); ++it) {
		std::cout << "Users : " << it->first->get_nickname() << std::endl;
	}

	channels[0].set_user_mode("-iws", &client3);
	
	channels[0].set_user_mode("+issswkaqsssss", &client1);
	std::cout << "Modes user1 = " << channels[0].get_users().find(&client1)->second << std::endl;

	channels[0].set_user_mode("-is", &client1);
	std::cout << "Modes user1 = " << channels[0].get_users().find(&client1)->second << std::endl;

	client1.set_nickname("kdelport");

	std::cout << "New nickname " << client1.get_nickname() << std::endl;
	std::cout << "Nickname in channel " << channels[0].get_users().find(&client1)->first->get_nickname() << std::endl;

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
