# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbraets <mbraets@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/18 12:15:17 by cdefonte          #+#    #+#              #
#    Updated: 2022/10/13 14:26:33 by mbraets          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D

SRC_DIR		=	src/
OBJ_DIR		=	obj/
INC_DIR		=	inc/
LIBFT_DIR	=	libft/

LIBX_DIR	=	minilibx_mac/
MLXFLAGS	=	-L$(LIBX_DIR) -lmlx -framework OpenGL -framework AppKit -lz

LIBFT		=	$(LIBFT_DIR)libft.a

CC			=	cc
# CFLAGS		=	-Werror -Wall -Wextra -g3 -MMD -MP -fsanitize=address
#CFLAGS		=	-Werror -Wall -Wextra -g3 -MMD -MP
CFLAGS		=	-Werror -Wall -Wextra -g3 -MMD -MP

ifeq ($(shell uname), Linux)
	CFLAGS		+=	-DLINUX
	LIBX_DIR	=	mlx_linux/
	MLXFLAGS	=	-L$(LIBX_DIR) -lmlx -lXext -lX11
endif

LIB_FLAGS	=	-L$(LIBFT_DIR) -lft $(MLXFLAGS) -lm
INCLUDES	=	-I$(LIBFT_DIR) -I$(INC_DIR) -I$(LIBX_DIR)

SRCS		=	$(addprefix $(SRC_DIR),\
					main.c utils.c texture.c hit_points.c\
					mlx_management.c raycasting.c vectors_utils.c\
					colision.c init.c game_display.c\
					parsing.c parsing_map.c parsing_map_check.c parsing_flags.c\
					parsing_utils.c fog.c texture_utils.c hit_points_check.c\
					\
					draw_sprites_bonus.c parsing_bonus.c textures_bonus.c \
					init_map_bonus.c\
					map_draw_bonus.c raytracing_bonus.c img_utils_bonus.c)

ifeq ($(BONUS),true)
	CFLAGS		+=	-DBONUS
	SRCS		+=  $(addprefix $(SRC_DIR),\
					hook_bonus.c socket_bonus.c socket_init_bonus.c \
					init_bonus.c loop_bonus.c \
					door_bonus.c socket_door_bonus.c)
endif
ifeq ($(LEAK),true)
	CFLAGS		+=	-DLEAK
endif

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
				rm -rf $(OBJ_DIR)
				make clean -C $(LIBFT_DIR)


fclean		:	clean
				rm -f $(NAME)
				make fclean -C $(LIBFT_DIR)

re			:	fclean
				$(MAKE)

bonus		:
				$(MAKE) BONUS=true
leak		:
				$(MAKE) BONUS=true LEAK=true

-include $(DEPS)

.PHONY: all clean run fclean bonus leak
