# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/14 14:04:50 by hrecolet          #+#    #+#              #
#    Updated: 2022/11/23 18:59:42 by hrecolet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= 	minishell

FILES 		=	srcs/main.c\
				srcs/parser/lexer/lexer.c\
				srcs/parser/lexer/lexer_utils.c\
				utils/singleton/singleton.c\
				utils/print.c\
				utils/list_functions/ft_lstadd_back.c\
				utils/list_functions/ft_lstadd_front.c\
				utils/list_functions/ft_lstclear.c\
				utils/list_functions/ft_lstdelone.c\
				utils/list_functions/ft_lstiter.c\
				utils/list_functions/ft_lstlast.c\
				utils/list_functions/ft_lstnew.c\
				utils/list_functions/ft_lstsize.c\
				utils/list_functions/ft_lst_remove_if.c\
				utils/free.c\
				tree_functions/create_node.c\
				utils/env_utils.c\
				parser/transformation/expand.c\
				parser/transformation/split_quoted.c\
				parser/transformation/unquoting.c\
				utils/utils/len.c\
				parser/create_tree/init_tree.c\
				parser/create_tree/tree_utils.c\
				srcs/parser/checker/check_cmd.c\
				srcs/utils/update_last_cmd_status.c\

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

$(OBJS_DIR)/%.o	: 	srcs/parser/lexer/%.c 
					@printf "\033[0;33mGenerating minsihell object... %-38.38s \r" $@
					@$(CC) $(CFLAGS) -c $< -o $@ -MMD $(INCL_DIR)

$(OBJS_DIR)/%.o	: 	srcs/utils/singleton/%.c 
					@printf "\033[0;33mGenerating minsihell object... %-38.38s \r" $@
					@$(CC) $(CFLAGS) -c $< -o $@ -MMD $(INCL_DIR)

$(OBJS_DIR)/%.o	: 	srcs/utils/%.c 
					@printf "\033[0;33mGenerating minsihell object... %-38.38s \r" $@
					@$(CC) $(CFLAGS) -c $< -o $@ -MMD $(INCL_DIR)

$(OBJS_DIR)/%.o	: 	srcs/utils/list_functions/%.c 
					@printf "\033[0;33mGenerating minsihell object... %-38.38s \r" $@
					@$(CC) $(CFLAGS) -c $< -o $@ -MMD $(INCL_DIR)
		
$(OBJS_DIR)/%.o	: 	srcs/utils/tree_functions/%.c 
					@printf "\033[0;33mGenerating minsihell object... %-38.38s \r" $@
					@$(CC) $(CFLAGS) -c $< -o $@ -MMD $(INCL_DIR)
				
$(OBJS_DIR)/%.o	: 	srcs/parser/transformation/%.c 
					@printf "\033[0;33mGenerating minsihell object... %-38.38s \r" $@
					@$(CC) $(CFLAGS) -c $< -o $@ -MMD $(INCL_DIR)

$(OBJS_DIR)/%.o	: 	srcs/parser/create_tree/%.c 
					@printf "\033[0;33mGenerating minsihell object... %-38.38s \r" $@
					@$(CC) $(CFLAGS) -c $< -o $@ -MMD $(INCL_DIR)

$(OBJS_DIR)/%.o	: 	srcs/exec/builtins/%.c 
					@printf "\033[0;33mGenerating minsihell object... %-38.38s \r" $@
					@$(CC) $(CFLAGS) -c $< -o $@ -MMD $(INCL_DIR)

$(OBJS_DIR)/%.o	: 	srcs/parser/checker/%.c 
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
