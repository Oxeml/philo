# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oemelyan <oemelyan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/19 13:26:25 by oemelyan          #+#    #+#              #
#    Updated: 2024/05/10 15:49:31 by oemelyan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= cc #-fsanitize=thread
CFLAGS	= -g -Wall -Werror -Wextra
NAME	= philo
OBJDIR	= obj
SRCS	= actions.c freedom.c init.c main.c monitor.c my_lib.c parsing.c threads.c utils.c
OBJS	= $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))
HEADERS	= philo.h

all: $(NAME)

$(OBJDIR)/%.o: %.c $(HEADERS) Makefile
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(PRINTF)
	$(CC) $(CFLAGS) -pthread $^ -o $(NAME)

clean:
	rm -rf $(OBJDIR)
#make -C

fclean: clean
	rm -f $(NAME)
#make -C

re: fclean $(NAME)

.PHONY: all clean fclean re