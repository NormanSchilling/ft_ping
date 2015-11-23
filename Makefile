# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nschilli <nschilli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/10/22 15:18:20 by nschilli          #+#    #+#              #
#    Updated: 2015/10/22 17:14:15 by nschilli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GCC = gcc

CFLAGS	= -Wall -Wextra -Werror -O3 -g

APP = ft_ping

SRC_DIR = srcs/
INC_DIR = includes/

FILE = main.c

SRC = $(addprefix $(SRC_DIR), $(FILE))

OBJ = $(SRC:.c=.o)

all: $(APP)

$(APP): $(OBJ)
	@make -C libft/
	@$(GCC) $(CFLAGS) -o $(APP) $(OBJ) libft/libft.a
	@echo "\033[33m"compilation of $(APP) : "\033[32m"Success"\033[0m"

%.o: %.c
	@echo -n .
	@$(GCC) $(CFLAGS) -c -o $@ $^ -I $(INC_DIR)

clean:
	@make -C libft/ clean
	@rm -f $(OBJ)

fclean: clean
	@make -C libft/ fclean
	@rm -rf $(APP)
	@echo "\033[31m"$(APP) : deleted"\033[0m"

re: fclean all

.PHONY: clean fclean re
