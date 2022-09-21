# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbraets <mbraets@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/18 12:15:17 by cdefonte          #+#    #+#              #
#    Updated: 2022/09/15 17:46:07 by mbraets          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3d

SRC_DIR		=	src/
OBJ_DIR		=	obj/
INC_DIR		=	inc/
LIBFT_DIR	=	libft/

LIBX_DIR	=	minilibx_mac/
MLXFLAGS	=	-L$(LIBX_DIR) -lmlx -framework OpenGL -framework AppKit -lz

LIBFT		=	$(LIBFT_DIR)libft.a

CC			=	cc
# CFLAGS		=	-Werror -Wall -Wextra -g3 -MMD -MP -fsanitize=address
CFLAGS		=	-Werror -Wall -Wextra -g3 -MMD -MP

ifeq ($(shell uname), Linux)
	CFLAGS		+=	-DLINUX
	LIBX_DIR	=	mlx_linux/
	MLXFLAGS	=	-L$(LIBX_DIR) -lmlx -lXext -lX11
endif
ifeq ($(BONUS),true)
	CFLAGS		+=	-DBONUS
endif

LIB_FLAGS	=	-L$(LIBFT_DIR) -lft $(MLXFLAGS) -lm
INCLUDES	=	-I$(LIBFT_DIR) -I$(INC_DIR) -I$(LIBX_DIR)

SRCS		=	$(addprefix $(SRC_DIR),\
					main.c utils.c texture.c hit_points.c\
					mlx_management.c raycasting.c map_draw.c vectors_utils.c\
					img_utils.c colision.c raytracing.c init.c game_display.c\
					parsing.c parsing_map.c parsing_map_check.c parsing_flags.c\
					parsing_utils.c)
OBJS		=	$(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))
DEPS		=	$(OBJS:.o=.d)

all			:	$(NAME)


$(NAME)		:	$(OBJS) $(LIBFT)
				$(shell $(SDK))
				$(MAKE) -C $(LIBX_DIR)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIB_FLAGS)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)


$(LIBFT)	:
				make -C $(LIBFT_DIR)

clean		:
				rm -rf $(OBJS) $(DEPS)
				make clean -C $(LIBFT_DIR)


fclean		:	clean
				rm -f $(NAME)
				make fclean -C $(LIBFT_DIR)

re			:	fclean
				$(MAKE)

bonus		: fclean
				$(MAKE) BONUS=true

-include $(DEPS)


.PHONY: all clean run fclean
