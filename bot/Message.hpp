#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <iostream>
#include <vector>
#include <string>

class Message {
	public :
		Message();
		Message(const Message &message);
		~Message();

		std::string 				get_prefix() const;
		std::string 				get_command() const;
		std::string 				get_parameter() const;
		int							get_nb_parameter() const;
		std::vector<std::string>	&get_tab_parameter();
		std::string 				get_target_nickname() const;
		//std::string 				get_payload() const;
		//std::string 				get_command_info() const;
		//std::string 				get_mask() const;
		//std::string 				get_subject() const;


		void set_prefix(std::string &val);
		void set_command(std::string &val);
		void set_parameter(std::string &val);
		void set_nb_parameter(int val);
		//void set_payload(std::string &val);
		//void set_command_info(std::string &val);
		//void set_mask(std::string &val);
		//void set_subject(std::string &val);

	private :
	std::string 				_payload;
	std::string 				_prefix;
    std::string 				_command;
	//std::string 				_command_info;
    //std::string 				_mask;
	//std::string 				_subject;
	std::string					_parameter;
	int							_nb_parameter;
	std::vector<std::string>	_tab_parameter;
};

#endif