#include "../includes/ft_irc.hpp"
#include "../includes/Channel.hpp"
#include "../includes/Client.hpp"
int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	std::string name = "myChannel";
	std::string client_name = "Kyllian";
    Channel channel(name);
	Client client1(client_name);

	std::cout << channel.get_name() << std::endl;

	std::map<std::string, std::string> mymap;

	std::string user1 = "user1";
	std::string user2 = "user2";

	std::string user7 = "user7";

	channel.set_users(client1);
	// channel.set_users(user2);

	std::cout << channel.get_users().size() << std::endl;
	for (std::map<Client&, std::string>::iterator it = channel.get_users().begin(); it != channel.get_users().end(); ++it) {
		std::cout << "Users :w " << it->first.get_nickname() << std::endl;
	}
	// channel.set_user_mode("+issswkaqsssss", "user7");
	channel.set_user_mode("+issswkaqsssss", client1);
	// std::cout << "Modes user1 = " << channel.get_users().find(client1)->second << std::endl;
	std::cout << "Modes user1 = " << channel.get_users().begin()->second << std::endl;

	channel.set_user_mode("-iws", client1);
	// std::cout << "Modes user1 = " << channel.get_users().find(client1)->second << std::endl;


	channel.set_channel_modes("+isooppkzvccmyy");
	std::cout << "Modes channel = " << channel.get_channel_modes() << std::endl;

	channel.set_channel_modes("-kism");
	std::cout << "Modes channel = " << channel.get_channel_modes() << std::endl;

    return (0);
}
