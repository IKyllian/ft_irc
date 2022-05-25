#include "../../includes/ft_irc.hpp"
#include "../../includes/Channel.hpp"
#include "../../includes/Client.hpp"

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	std::string name = "myChannel";
	std::string client_name = "Kyllian";
	std::string client2_name = "Romain";
	std::string user7 = "user7";
    Channel channel(name);
	Client client1(client_name);
	Client client2(client2_name);
	Client client3(user7);

	std::cout << channel.get_name() << std::endl;

	std::map<std::string, std::string> mymap;

	channel.set_user(&client1);

	channel.set_channel_modes("+i");

	channel.add_invite(&client2);
	std::cout << "Invite list size = " << channel.get_invite_list().size() << std::endl;
	channel.set_user(&client2);
	std::cout << "Invite list size = " << channel.get_invite_list().size() << std::endl;

	std::cout << channel.get_users().size() << std::endl;
	for (std::map<Client*, std::string>::iterator it = channel.get_users().begin(); it != channel.get_users().end(); ++it) {
		std::cout << "Users : " << it->first->get_nickname() << std::endl;
	}

	channel.set_user_mode("-iws", &client3);
	
	channel.set_user_mode("+issswkaqsssss", &client1);
	std::cout << "Modes user1 = " << channel.get_users().find(&client1)->second << std::endl;


	channel.set_user_mode("-is", &client1);
	std::cout << "Modes user1 = " << channel.get_users().find(&client1)->second << std::endl;

	client1.set_nickname("kdelport");

	std::cout << "New nickname " << client1.get_nickname() << std::endl;
	std::cout << "Nickname in channel " << channel.get_users().find(&client1)->first->get_nickname() << std::endl;

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
