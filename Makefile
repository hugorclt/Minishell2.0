# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/14 14:04:50 by hrecolet          #+#    #+#              #
#    Updated: 2022/11/14 21:44:41 by hrecolet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= 	minishell

FILES 		=	srcs/main.c\

INCL_DIR	=	includes

CC 			= 	cc
CFLAGS 		= 	-Wall -Wextra -Werror

OBJS_DIR	=	.objs
OBJS 		= 	$(addprefix $(OBJS_DIR)/, $(notdir $(FILES:%.c=%.o)))

DEP			=	$(addprefix $(OBJS_DIR)/, $(notdir $(FILES:%.c=%.d)))

$(OBJS_DIR)		:
					@mkdir -p $(OBJS_DIR)


$(OBJS_DIR)/%.o	: 	srcs/%.c 
					@printf "\033[0;33mGenerating minsihell object... %-38.38s \r" $@
					@$(CC) $(CFLAGS) -c $< -o $@ -MMD -I./$(INCL_DIR)

all 			: 	$(NAME)

$(NAME)			: 	$(OBJS_DIR) $(OBJS)
					@$(MAKE) --no-print-directory -C Libft
		      		@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline Libft/libft.a
					@echo "\033[1;32mMinishell: Done!\033[0m"

clean			:
					@$(MAKE) --no-print-directory -C Libft fclean
		      		@rm -f $(OBJS)
					@rm -rf $(OBJS_DIR)
					@echo "\033[1;31mObject cleaned!\033[0m"

fclean			:	
					@$(MAKE) --no-print-directory -C Libft fclean
					@rm -f $(OBJS)
					@rm -rf $(OBJS_DIR)
					@rm -f $(NAME)
					@echo "\033[1;31mProgram and object cleaned!\033[0m"

re				:	fclean all

.PHONY			:
					all test clean fclean re

-include $(DEP)
