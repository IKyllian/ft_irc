#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <vector>
#include <string>

class Message {
	
	public:

		Message();
		Message(const Message &message);
		~Message();

		std::string 				get_prefix() const;
		std::string 				get_command() const;
		std::string 				get_parameter() const;
		std::vector<std::string>	&get_tab_parameter();

		void set_prefix(std::string &val);
		void set_command(std::string &val);
		void set_parameter(std::string &val);

		Message& operator=(const Message& rhs);

		std::string get_target_nickname() const;

	protected:

	private:

		std::string 				_prefix;
		std::string 				_command;
		std::string					_parameter;
		std::vector<std::string>	_tab_parameter;
};

#endif