# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdefonte <cdefonte@student42.fr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/28 17:24:15 by cdefonte          #+#    #+#              #
#    Updated: 2022/09/27 23:34:39 by mbraets          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRC = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
      ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
      ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
      ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
      ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c \
	  ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
	  ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c	\
	  get_next_line.c ft_tabtablen.c ft_lstmap.c ft_lstiter.c ft_lstclear.c \
	  ft_lstsize.c ft_lstadd_back.c ft_lstdelone.c ft_lstadd_front.c ft_lstnew.c \
	  ft_lstlast.c ft_stris.c ft_isspace.c ft_atof.c
OBJ = $(SRC:.c=.o)

INC = libft.h

CFLAGS = -Wall -Wextra -Werror
RM = rm -f
CC = cc

all: $(NAME)

$(NAME): $(OBJ) $(INC)
	ar rc $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	$(RM) $(OBJ)

fclean:
	$(RM) $(OBJ) $(NAME)

re: fclean all

.PHONY: all fclean clean re
