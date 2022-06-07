SRCS		= 	srcs/main.cpp \
				srcs/Channel.cpp \
				srcs/Server.cpp \
				srcs/Client.cpp \
				srcs/Message.cpp \
				srcs/create_Message.cpp \
				srcs/print_numerics.cpp \
				srcs/do_parsing.cpp	\
				#srcs/send.cpp \

COMMAND		=	srcs/command/away.cpp \
				srcs/command/privmsg.cpp \
				srcs/command/who.cpp \
				srcs/command/nick.cpp

OBJS			= $(SRCS:.cpp=.o) $(COMMAND:.cpp=.o)

DEPS			= $(SRCS:.cpp=.d) $(COMMAND:.cpp=.d)

NAME			= ircserv
CC				= clang++
CFLAGS			= --std=c++98 -Wall -Wextra -Werror

all:			$(NAME)

%.o: 			%.cpp
				$(CC) $(CFLAGS) -MM -MG -MT $@ $< -o $(@:%.o=%.d)
				$(CC) $(CFLAGS) -c $< -o $@

$(NAME):		$(OBJS)
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:			
				$(RM) $(OBJS)
				$(RM) $(DEPS)

fclean:			clean
				$(RM) $(NAME)

re:			fclean all

.PHONY:		re fclean clean all

-include $(DEPS)
