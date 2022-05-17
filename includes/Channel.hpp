#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <set>

class Channel {
	public :
		Channel()
		Channel(std::string &name)
		Channel(const Channel &channel);
		~Channel() {}

		std::string get_name() const
		std::set<std::string> get_users() const
		std::string get_channel_modes() const
		
		void set_name(std::string &val)
		void set_users(std::string &val)
		void set_channel_modes(std::string &val)

	private :
		std::string name;
		std::set<std::string> users;
		std::string channel_modes;
};

#endif