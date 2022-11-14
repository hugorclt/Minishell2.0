# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/23 13:39:38 by hrecolet          #+#    #+#              #
#    Updated: 2022/11/15 00:32:56 by hrecolet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	ft_atoi.c ft_isascii.c ft_memset.c ft_split.c ft_strlcpy.c ft_strrchr.c \
				ft_bzero.c ft_isdigit.c ft_memchr.c ft_putchar_fd.c ft_strchr.c ft_strlen.c ft_strtrim.c \
				ft_calloc.c ft_isprint.c ft_memcmp.c  ft_putendl_fd.c ft_strdup.c  ft_strmapi.c ft_substr.c \
				ft_isalnum.c ft_itoa.c ft_memcpy.c ft_putnbr_fd.c ft_strjoin.c ft_strncmp.c ft_tolower.c \
				ft_isalpha.c ft_memmove.c ft_putstr_fd.c ft_strlcat.c ft_strnstr.c ft_toupper.c ft_striteri.c \
				ft_strcmp.c\

OBJ			=	$(SRCS:.c=.o)

NAME		=	libft.a

all			:	$(NAME)

$(NAME)		:	$(OBJ)
				@ar rc $(NAME) $(OBJ) 
				@ranlib $(NAME)
				@echo "\033[1;32m\nLibft: done!\033[0m"
				
%.o			:	%.c
				@printf "\033[0;33mGenerating libft object... %-38.38s \r" $@
				@gcc -Wall -Wextra -Werror -c $< -o $@

clean		:
				@/bin/rm -f $(OBJ)

fclean		:	clean
				@/bin/rm -f $(NAME)

re			:	fclean all

.PHONY		:	all clean fclean re
