# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mben-zeh <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/06 22:00:40 by mben-zeh          #+#    #+#              #
#    Updated: 2023/01/06 22:00:43 by mben-zeh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME=so_long

CC=gcc

CFLAGS= -Wall -Werror -Wextra

SRC =  	ft_split.c check.c error.c get_next_line_utils.c get_next_line.c libft_utils.c so_long.c utils.c

SRC_bonus = ./bonus/ft_split_bonus.c  ./bonus/error_bonus.c ./bonus/check_bonus.c ./bonus/get_next_line_utils_bonus.c ./bonus/get_next_line_bonus.c ./bonus/libft_utils_bonus.c ./bonus/so_long_bonus.c ./bonus/utils_bonus.c ./bonus/move_bonus.c

OBJ=${SRC:.c=.o}

OBJ_bonus=${SRC_bonus:.c=.o}

MAPS = maps/map.ber


all:${NAME}
	
${NAME}:${OBJ}
	@$(CC) $(OBJ) -lmlx -framework OpenGL -framework AppKit -o ${NAME} 

bonus : $(OBJ_bonus)
	@$(CC) $(SRC_bonus) -lmlx -framework OpenGL -framework AppKit -o ${NAME} 

clean :
	rm -f ${OBJ} ${OBJ_bonus}
fclean : clean
	rm -f ${NAME}
re : fclean all

.PHONY: all clean fclean re