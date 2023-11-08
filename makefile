NAME = ircclient
NAME1 = ircserv

.PHONY: all, fclean, re

SRCS = client/client.cpp
SRCS1 = server/server.cpp server/main.cpp

OBJS = $(SRCS:.c=.o)

CC = g++

CFLAGS = -Wall -Wextra -Werror -std=c++98

all: $(NAME) $(NAME1)

$(NAME):$(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

$(NAME1):$(SRCS1)
	$(CC) $(CFLAGS) $(SRCS1) -o $(NAME1)

fclean:
	rm -f $(NAME)

re: fclean all