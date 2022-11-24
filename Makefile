# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/14 14:04:50 by hrecolet          #+#    #+#              #
#    Updated: 2022/11/23 19:28:21 by lbisson          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= 	minishell

FILES 		=	builtins/builtin_cd.c				\
				builtins/builtin_echo.c				\
				builtins/builtin_env.c				\
				builtins/builtin_exit.c				\
				builtins/builtin_export.c			\
				builtins/builtin_pwd.c				\
				builtins/builtin_unset.c			\
				create_tree/init_tree.c				\
				create_tree/tree_utils.c			\
				lexer/lexer_utils.c					\
				lexer/lexer.c						\
				list_functions/ft_lst_remove_if.c	\
				list_functions/ft_lstadd_back.c		\
				list_functions/ft_lstadd_front.c	\
				list_functions/ft_lstclear.c		\
				list_functions/ft_lstdelone.c		\
				list_functions/ft_lstiter.c			\
				list_functions/ft_lstlast.c			\
				list_functions/ft_lstnew.c			\
				list_functions/ft_lstsize.c			\
				singleton/singleton.c				\
				srcs/main.c							\
				transformation/expand.c				\
				transformation/split_quoted.c		\
				transformation/unquoting.c			\
				tree_functions/create_node.c		\
				utils/env_utils.c					\
				utils/free.c						\
				utils/len.c							\
				utils/print.c						\
				utils/update_last_cmd_status.c		\

INCL_DIR	=	-I./includes -I./Libft

CC 			= 	cc
CFLAGS 		= 	-Wall -Wextra -Werror -g3

OBJS_DIR	=	.objs
OBJS 		= 	$(addprefix $(OBJS_DIR)/, $(notdir $(FILES:%.c=%.o)))

DEP			=	$(addprefix $(OBJS_DIR)/, $(notdir $(FILES:%.c=%.d)))

$(OBJS_DIR)		:
					@mkdir -p $(OBJS_DIR)


# For Multiple Directory
$(OBJS_DIR)/%.o	: 	srcs/%.c
					@printf "\033[0;33mGenerating minsihell object... %-38.38s \r" $@
					@$(CC) $(CFLAGS) -c $< -o $@ -MMD $(INCL_DIR)

$(OBJS_DIR)/%.o	: 	srcs/builtins/%.c 
					@printf "\033[0;33mGenerating minsihell object... %-38.38s \r" $@
					@$(CC) $(CFLAGS) -c $< -o $@ -MMD $(INCL_DIR)

$(OBJS_DIR)/%.o	: 	srcs/lexer/%.c 
					@printf "\033[0;33mGenerating minsihell object... %-38.38s \r" $@
					@$(CC) $(CFLAGS) -c $< -o $@ -MMD $(INCL_DIR)

$(OBJS_DIR)/%.o	: 	srcs/singleton/%.c 
					@printf "\033[0;33mGenerating minsihell object... %-38.38s \r" $@
					@$(CC) $(CFLAGS) -c $< -o $@ -MMD $(INCL_DIR)

$(OBJS_DIR)/%.o	: 	srcs/utils/%.c 
					@printf "\033[0;33mGenerating minsihell object... %-38.38s \r" $@
					@$(CC) $(CFLAGS) -c $< -o $@ -MMD $(INCL_DIR)

$(OBJS_DIR)/%.o	: 	srcs/list_functions/%.c 
					@printf "\033[0;33mGenerating minsihell object... %-38.38s \r" $@
					@$(CC) $(CFLAGS) -c $< -o $@ -MMD $(INCL_DIR)
		
$(OBJS_DIR)/%.o	: 	srcs/tree_functions/%.c 
					@printf "\033[0;33mGenerating minsihell object... %-38.38s \r" $@
					@$(CC) $(CFLAGS) -c $< -o $@ -MMD $(INCL_DIR)
				
$(OBJS_DIR)/%.o	: 	srcs/transformation/%.c 
					@printf "\033[0;33mGenerating minsihell object... %-38.38s \r" $@
					@$(CC) $(CFLAGS) -c $< -o $@ -MMD $(INCL_DIR)

$(OBJS_DIR)/%.o	: 	srcs/create_tree/%.c 
					@printf "\033[0;33mGenerating minsihell object... %-38.38s \r" $@
					@$(CC) $(CFLAGS) -c $< -o $@ -MMD $(INCL_DIR)

# End Multiple Directory

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

.SECONDEXPANSION:


-include $(DEP)
