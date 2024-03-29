# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/14 14:04:50 by hrecolet          #+#    #+#              #
#    Updated: 2022/12/20 18:33:12 by hrecolet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= 	minishell

FILES 		=	srcs/main.c									 \
				srcs/exec/exec_choice.c						 \
				srcs/exec/pipe.c							 \
				srcs/exec/exec_cmd.c 						 \
				srcs/exec/join_cmdpath.c					 \
				srcs/exec/launch_exec.c 					 \
				srcs/exec/builtins/builtin_cd.c				 \
				srcs/exec/builtins/builtin_echo.c			 \
				srcs/exec/builtins/builtin_env.c			 \
				srcs/exec/builtins/builtin_exit.c			 \
				srcs/exec/builtins/builtin_export.c			 \
				srcs/exec/builtins/builtin_pwd.c			 \
				srcs/exec/builtins/builtin_unset.c			 \
				srcs/exec/builtins/builtins_error.c 		 \
				srcs/exec/redirection/parse_redirection.c	 \
				srcs/exec/redirection/open_redirection.c 	 \
				srcs/exec/redirection/redirection_utils.c	 \
				srcs/parser/checker/check_cmd.c				 \
				srcs/parser/lexer/join_redir.c				 \
				srcs/parser/lexer/lexer_utils.c				 \
				srcs/parser/lexer/lexer.c					 \
				srcs/parser/lexer/lexer_init.c				 \
				srcs/parser/parser/parser.c					 \
				srcs/parser/parser/parser_utils.c			 \
				srcs/parser/parser/concat_token.c			 \
				srcs/parser/transformation/expand_utils.c	 \
				srcs/parser/transformation/expand.c			 \
				srcs/parser/transformation/split_quoted.c	 \
				srcs/parser/transformation/unquoting.c		 \
				srcs/parser/transformation/unquoting_utils.c \
				srcs/parser/transformation/clean_redirection.c\
				srcs/parser/heredoc/heredoc.c 				 \
				srcs/parser/heredoc/create_file.c			 \
				srcs/parser/heredoc/heredoc_utils.c			 \
				srcs/parser/transformation/wildcards.c		 \
				srcs/parser/transformation/wildcards_utils.c \
				srcs/utils/list_functions/ft_lst_remove_if.c \
				srcs/utils/list_functions/ft_lstadd_back.c	 \
				srcs/utils/list_functions/ft_lstadd_front.c	 \
				srcs/utils/list_functions/ft_lstclear.c		 \
				srcs/utils/list_functions/ft_lstdelone.c	 \
				srcs/utils/list_functions/ft_lstiter.c		 \
				srcs/utils/list_functions/ft_lstlast.c		 \
				srcs/utils/list_functions/ft_lstnew.c		 \
				srcs/utils/list_functions/ft_lstsize.c		 \
				srcs/utils/singleton/singleton.c			 \
				srcs/utils/tree_functions/create_node.c		 \
				srcs/utils/env_utils.c						 \
				srcs/utils/env_utils2.c						 \
				srcs/utils/error.c							 \
				srcs/utils/free_all.c						 \
				srcs/utils/free_all_utils.c					 \
				srcs/utils/utils_cmd.c						 \
				srcs/utils/last_cmd_status.c				 \
				srcs/utils/utils/len.c						 \
				srcs/utils/print.c							 \
				srcs/utils/signal.c							 \

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

$(OBJS_DIR)/%.o	: 	srcs/parser/parser/%.c 
					@printf "\033[0;33mGenerating minsihell object... %-38.38s \r" $@
					@$(CC) $(CFLAGS) -c $< -o $@ -MMD $(INCL_DIR)

$(OBJS_DIR)/%.o	: 	srcs/exec/builtins/%.c 
					@printf "\033[0;33mGenerating minsihell object... %-38.38s \r" $@
					@$(CC) $(CFLAGS) -c $< -o $@ -MMD $(INCL_DIR)

$(OBJS_DIR)/%.o	: 	srcs/parser/checker/%.c 
					@printf "\033[0;33mGenerating minsihell object... %-38.38s \r" $@
					@$(CC) $(CFLAGS) -c $< -o $@ -MMD $(INCL_DIR)

$(OBJS_DIR)/%.o	: 	srcs/exec/redirection/%.c 
					@printf "\033[0;33mGenerating minsihell object... %-38.38s \r" $@
					@$(CC) $(CFLAGS) -c $< -o $@ -MMD $(INCL_DIR)

$(OBJS_DIR)/%.o	: 	srcs/exec/%.c 
					@printf "\033[0;33mGenerating minsihell object... %-38.38s \r" $@
					@$(CC) $(CFLAGS) -c $< -o $@ -MMD $(INCL_DIR)

$(OBJS_DIR)/%.o	: 	srcs/parser/heredoc/%.c 
					@printf "\033[0;33mGenerating minsihell object... %-38.38s \r" $@
					@$(CC) $(CFLAGS) -c $< -o $@ -MMD $(INCL_DIR)


# End Multiple Directory

all 			: 	$(NAME)

leaks			:	all
					valgrind --suppressions=ignore_readline	\
					--leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes	\
					./minishell

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
