# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsergien <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/20 11:44:54 by tsergien          #+#    #+#              #
#    Updated: 2018/07/20 11:45:06 by tsergien         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

SRC_FILES = main.c reader.c comments.c rooms.c output.c valid.c \
			algorithm.c visited.c queve.c hashmap.c ants.c list_ways.c\
			ants_distribution.c algorithm2.c additional.c

SRC_DIR = src/

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ_FILES = $(SRC_FILES:.c=.o)

OBJ_DIR = obj/

OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

HEADER = -I includes/

LIB_DIR = libft/

WWW = -Wall -Wextra -Werror

COLOR = \033[0;36m

RESET_COLOR = \033[0m

all: $(NAME)

$(NAME): $(OBJ)
		@make -C $(LIB_DIR)
		@gcc $(OBJ) -o $(NAME) -L $(LIB_DIR) -lft
		@echo "$(COLOR)***	Ant farm is ready	***"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
		@mkdir -p $(OBJ_DIR)
		@gcc $(WWW) -o $@ -c $< $(HEADER)

clean:
		@make clean -C $(LIB_DIR)
		@rm -rf $(OBJ_DIR)
		@echo "$(COLOR)***  all clean, obj removed	***"

fclean: clean
		@make fclean -C $(LIB_DIR)
		@rm -f $(NAME)
		@echo "$(COLOR)***  all transperently clean	***$(RESET_COLOR)"

re: fclean all
