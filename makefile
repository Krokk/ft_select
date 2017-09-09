# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/05 17:20:16 by rfabre            #+#    #+#              #
#    Updated: 2017/09/05 17:20:57 by rfabre           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY : all clean fclean re
NAME = ft_select
CFLAGS += -Wall -Wextra -g
SRC = main.c\

LIB = ./libft/libft.a
CC = gcc
OBJ = $(SRC:.c=.o)

# COLOR
C_GOOD = "\033[32m"
C_DURING = "\033[36m"
C_FINI = "\033[0m"

# MESSAGE
SUCCESS = $(C_GOOD)"\t'MAKE' ->\t\033[1;34m$(NAME): \033[0m  \tLibrary compilation completed successfully"$(C_FINI)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft/
	@echo $(C_GOOD)"\t'MAKE' ->\t\033[1;34m$(NAME): \033[0m  \tLibrary compilation in progress..."$(C_FINI)
	$(CC) $(OBJ) $(LIB) -o $(NAME) -ltermcap
	@echo $(SUCCESS)

clean:
	@make clean -C libft/
	@/bin/rm -f $(OBJ)
	@echo $(C_GOOD)".o files DELETED" $(C_FINI)

fclean: clean
	@make fclean -C libft/
	@/bin/rm -f $(NAME)
	@echo $(C_GOOD)"executable DELETED" $(C_FINI)

re: fclean all