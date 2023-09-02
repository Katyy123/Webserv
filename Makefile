# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: catia <catia@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/09 12:43:46 by tdi-leo           #+#    #+#              #
#    Updated: 2023/09/01 16:47:40 by catia            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = webserv

C_NAME = client

SERVER = srcs/WebServer.cpp server.cpp srcs/config_parsing/Config.cpp \
		srcs/config_parsing/Config_directives.cpp srcs/config_parsing/Config_exceptions.cpp \
		srcs/config_parsing/Config_tools.cpp \
		srcs/config_parsing/utils/utils.cpp libraries/sServ.cpp \
		libraries/sLocation.cpp libraries/sHttpMethods.cpp

CLIENT = client.cpp

S_OBJS=${SERVER:.cpp=.o}

C_OBJS=${CLIENT:.cpp=.o}

$(NAME): $(S_OBJS) $()
	@echo "building server"
	@c++ -g -Wall -Wextra -Werror -std=c++98 $(S_OBJS) -o $(NAME)

$(C_NAME): $(C_OBJS) $()
	@echo "building client"
	@c++ -g -Wall -Wextra -Werror -std=c++98 $(C_OBJS) -o $(C_NAME)

all: $(NAME) $(C_NAME)

re: fclean $(NAME)

clean:
	@echo "removing all"
	@rm -f ${NAME} $(C_NAME) *.o
	@rm srcs/config_parsing/Config.o libraries/sServ.o libraries/sLocation.o libraries/sHttpMethods.o \
		srcs/config_parsing/Config_directives.o srcs/config_parsing/Config_exceptions.o \
		srcs/config_parsing/Config_tools.o \
		srcs/config_parsing/utils/utils.o srcs/WebServer.o #just temporarly

fclean: clean

sanitize: $(S_OBJS) $()
	c++ -fsanitize=address -Wall -Wextra -Werror -std=c++98 ${OBJS} -o $(NAME)

%.o: %.cpp
	@c++ -Wall -Wextra -Werror -std=c++98 -c $< -o $@

.PHONY: all re clean fclean