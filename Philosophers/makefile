# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/07 15:35:56 by akaabi            #+#    #+#              #
#    Updated: 2023/07/19 04:01:43 by akaabi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = CC
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread
RM = rm -f

SRC = philosophers.c philo.c some_utils.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	
%.o : %.c philosophers.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean : 
	@$(RM) $(OBJ)

fclean : clean
	@$(RM) $(NAME)

re : fclean all