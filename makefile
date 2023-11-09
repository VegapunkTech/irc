NAME = ircserv

.PHONY: all, fclean, re

SRCS = src/server.cpp src/main.cpp src/client.cpp utils/get_client_infos.cpp \
		src/channel.cpp

OBJS = $(SRCS:.c=.o)

CC = g++

CFLAGS = -Wall -Wextra -Werror -std=c++98

all: $(NAME) $(NAME1)

$(NAME):$(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)


fclean:
	rm -f $(NAME)

re: fclean all