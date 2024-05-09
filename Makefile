# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oemelyan <oemelyan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/19 13:26:25 by oemelyan          #+#    #+#              #
#    Updated: 2024/05/07 17:15:21 by oemelyan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= cc
CFLAGS	= -Wall -Werror -Wextra -g -fsanitize=address
NAME	= philo
OBJDIR	= obj
SRCS	= 	$(wildcard *.c)
OBJS	= $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))
HEADERS	= philo.h

SAN_LDFLAG = -L /Users/oemelyan/Documents/projects/LeakSanitizer -llsan -lc++ -Wno-gnu-include-next -I /Users/oemelyan/Documents/projects/LeakSanitizer

all: $(NAME)

$(OBJDIR)/%.o: %.c $(HEADERS) Makefile
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(PRINTF)
	$(CC) $(CFLAGS) $^ -o $(NAME) $(SAN_LDFLAG)

clean:
	rm -rf $(OBJDIR)
#make -C

fclean: clean
	rm -f $(NAME)
#make -C

re: fclean $(NAME)

.PHONY: all clean fclean re