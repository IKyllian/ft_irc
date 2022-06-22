#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <iostream>
#include <vector>
#include <string>
#include "Client.hpp"

class Client;

class Message {
	public :
		Message();
		Message(const Message &message);
		~Message();

		Message& operator=(const Message& rhs);

		Client 						&get_sender() const;
		Client 						&get_receiver() const;
		std::string 				get_prefix() const;
		std::string 				get_command() const;
		std::string 				get_parameter() const;
		int							get_nb_parameter() const;
		std::vector<std::string>	&get_tab_parameter();


		void set_sender(Client *val);
		void set_receiver(Client *val);
		void set_prefix(std::string &val);
		void set_command(std::string &val);
		void set_parameter(std::string &val);
		void set_nb_parameter(int val);

	private :
		Client 						*_sender;
		Client 						*_receiver;
		std::string 				_payload;
		std::string 				_prefix;
		std::string 				_command;
		std::string					_parameter;
		int							_nb_parameter;
		std::vector<std::string>	_tab_parameter;
};

#endif