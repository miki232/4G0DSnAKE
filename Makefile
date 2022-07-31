# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtoia <mtoia@student.42roma.it>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/10 13:32:42 by gifulvi           #+#    #+#              #
#    Updated: 2022/06/27 12:02:05 by mtoia            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Ray

GREENGREEN = \033[38;5;46m
RESET = \033[0m
C_LMGN = \033[95m
T_BLK = \033[5m
T_NRM = \033[25m
T_CLR = \033[K
C_YLW = \033[33m
C_GRN = \033[32m
C_LYLW = \033[93m
C_LGRN = \033[92m
C_LMGN = \033[95m
C_END = \033[0m

SRC=  main.c

PRINTF = ft_printf

LIBFT = libft

HDRS = mlx/

MLX = ./libmlx.dylib

OBJ = $(SRC:.c=.o)

RM = rm -f

CC		=	clang 
CFLAGS	= 

LIBS = -framework OpenGL -lm -framework AppKit

NB = $(words $(FILES))

%.o: %.c
	@$(CC) -I ${HDRS} -c $< -o $@

$(NAME): $(OBJ)
		@make -C ./mlx
		@mv mlx/libmlx.dylib .
		@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(MLX) $(LIBS)
		@echo "$(C_LGRN)➜ [$(NAME)] Program has been Compiled Successfully !$(C_END)"
		

all: $(NAME)
	make clean

clean:
	@${RM} $(OBJ)
	@echo "$(C_LMGN)➜ [$(NAME)] Objects have been cleaned Successfully !$(C_END)"

fclean:
	${RM} $(NAME) ${OBJ}
	@rm libmlx.dylib
	@make -C ./mlx clean
	@make -C ./ft_printf fclean
	@make -C ./libft fclean
	@echo "$(C_LMGN)➜ [$(NAME)] Library has been deleted Successfully !$(C_END)"


re: fclean $(NAME)

run: all


.PHONY: all clean fclean re reb
