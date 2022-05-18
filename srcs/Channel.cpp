#include "../includes/Channel.hpp"

Channel::Channel() {}
Channel::Channel(std::string &name) : name(name) {}
Channel::Channel(const Channel &channel) : name(channel.name) {
	users.clear();
	users.insert(channel.users.begin(), channel.users.end());
	channel_modes = channel.channel_modes;
}

Channel::~Channel() {
	users.clear();
}

std::string Channel::get_name() const { return (name); }
std::set<std::string>::iterator Channel::get_user(std::string nickname) const { return (users.find(nickname)); }
std::string Channel::get_channel_modes() const { return (channel_modes); }

void Channel::set_name(std::string &val) {
	name = val;
}

void Channel::set_users(std::string &val) {
	users.insert(val);	
}

void Channel::set_channel_modes(std::string &val) {
	channel_modes = val;
}