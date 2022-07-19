# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbraets <mbraets@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/18 12:15:17 by cdefonte          #+#    #+#              #
#    Updated: 2022/07/19 15:36:52 by Cyrielle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cubed

SRC_DIR		=	src/
OBJ_DIR		=	obj/
INC_DIR		=	inc/
LIBFT_DIR	=	libft/
LIBX_DIR	=	minilibx_mac/
MLXFLAGS	=	-L$(LIBX_DIR) -lmlx -framework OpenGL -framework AppKit -lz
ifeq ($(shell uname), Linux)
LIBX_DIR	=	mlx_linux/
MLXFLAGS	=	-L$(LIBX_DIR) -lmlx -lXext -lX11
endif

LIBFT		=	$(LIBFT_DIR)libft.a

CC			=	cc
#CFLAGS		=	-Werror -Wall -Wextra -g3 -fsanitize=address
CFLAGS		=	-Werror -Wall -Wextra
LIB_FLAGS	=	-L$(LIBFT_DIR) -lft $(MLXFLAGS)
INCLUDES	=	-I$(LIBFT_DIR) -I$(INC_DIR) -I$(LIBX_DIR)

SRCS		=	$(addprefix $(SRC_DIR),\
					main.c parsing.c parsing2.c utils.c texture.c\
					mlx_management.c)
OBJS		=	$(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))
HDRS		=	$(addprefix $(INC_DIR), cubed.h)

all			:	$(NAME)


$(NAME)		:	$(OBJS) $(LIBFT) $(HDRS)
				$(shell $(SDK))
				$(MAKE) -C $(LIBX_DIR)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIB_FLAGS)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(HDRS)
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)


$(LIBFT)	:
				make -C $(LIBFT_DIR)

clean		:
				rm -rf $(OBJS)
				make clean -C $(LIBFT_DIR)


fclean		:	clean
				rm -f $(NAME)
				make fclean -C $(LIBFT_DIR)

re			:	fclean all

.PHONY: all clean run fclean
