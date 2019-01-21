# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: prastoin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/07 11:13:09 by prastoin          #+#    #+#              #
#    Updated: 2019/01/14 16:50:04 by fbecerri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = frac

SRC = main.c getinfo.c fractol.c intial.c

OBJ = $(SRC:.c=.o)

FLAG = -Wall -Wextra -Werror -Ofast

LIB = libft/libft.a

LIB2 = -L/usr/local/lib

LIBX = -framework OpenGL -framework AppKit

INC = -I./libft/ -I/usr/local/include

all: $(NAME)

$(NAME): $(OBJ) $(LIB)
		gcc $(FLAG) $(LIB) -L ./lib -lmlx  $(LIB2) $(INC) $(OBJ) $(LIBX) -o $(NAME)

$(LIB):
		make -C libft/ fclean
			make -C ./libft/

%.o: %.c frac.h
		gcc $(FLAG) $(INC) -o $@ -c $<

clean:
		make -C libft/ clean
			rm -rf $(OBJ)

fclean: clean
		make -C libft/ fclean
			rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re all
