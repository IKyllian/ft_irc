#include "../includes/Channel.cpp"

Channel() {}
Channel(std::string &name) : name(name) {}
Channel(const Channel &channel) : name(channel.name) {
	users.clear();
	users.insert(channel.users.begin(), channel.users.end());
}

~Channel() {
	users.clear();
}

std::string get_name() const { return (name); }
std::set<std::string> &get_users() const { return (users); }
std::set<std::string>::iterator get_user(std::string nickname) const { return (users.find(nickname)); }
std::string get_channel_modes() const { return (channel_modes); }

void set_name(std::string &val) {
	name = val;
}

void set_users(std::string &val) {
	users.insert(val);	
}

void set_channel_modes(std::string &val) {
	channel_modes = val;
}