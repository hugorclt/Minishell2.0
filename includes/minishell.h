/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:34:37 by hrecolet          #+#    #+#             */
/*   Updated: 2022/11/22 01:31:34 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* -------------------------------------------------------------------------- */
/*                                  includes                                  */
/* -------------------------------------------------------------------------- */
# include <stdio.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "../Libft/libft.h"

/* -------------------------------------------------------------------------- */
/*                                   define                                   */
/* -------------------------------------------------------------------------- */
# define TRUE					1
# define FALSE					0
# define STDOUT					1
# define STDERR					2
# define SUCCESS				0
# define FAILURE				1
# define NB_TOKEN				10
# define STEP_PRINT_TREE		10

/* ------------------------------- token_type ------------------------------- */
# define OR						1
# define CMD					9
# define AND					0
# define PIPE					6
# define INFILE					5
# define HEREDOC				3
# define OUTFILE				4
# define LPARENTH				7
# define RPARENTH				8
# define OUTFILE_APND			2

/* ------------------------------- error_type ------------------------------- */
# define QUIT					1
# define FREE					2
# define CD_ERROR				1
# define MALLOC_ERROR			1
# define SYNTAX_ERROR			2
# define CMD_NOT_FOUND			127
# define EXIT_TOO_MANY_ARGS		1
# define EXIT_NUM_ARG_REQUIRED	2

/* -------------------------------------------------------------------------- */
/*                                    color                                   */
/* -------------------------------------------------------------------------- */
# define RESET	"\033[0m"
# define WHITE	"\033[97m"
# define RED	"\033[1;31m"
# define BLUE	"\033[1;34m"
# define PINK	"\033[1;95m"
# define GREEN	"\033[1;32m"
# define PURPLE	"\033[1;35m"
# define ORANGE	"\033[38:5:208m"

/* -------------------------------------------------------------------------- */
/*                                  typedef                                   */
/* -------------------------------------------------------------------------- */
typedef unsigned char u_char;

/* -------------------------------------------------------------------------- */
/*                                  structure                                 */
/* -------------------------------------------------------------------------- */

typedef struct s_token
{
	int			id;
	char		**cmd;
}	t_token;

typedef struct s_list
{
	char			*key;
	char			*value;
	struct s_list	*next;
}					t_list;

typedef struct	s_scanner
{
	int		start_pos;
	int		end_pos;
	char	*token_tab[10];
	char	*cmd;
}	t_scanner;


typedef struct s_tree
{
	t_token			*token;
	struct s_tree 	*left;
	struct s_tree 	*right;
}	t_tree;

typedef struct s_data
{
	u_char		last_cmd_status;
	t_list		*env;
	t_scanner	scanner;
	t_tree		*tree;
}	t_data;

/* -------------------------------------------------------------------------- */
/*                                  prototypes                                */
/* -------------------------------------------------------------------------- */
/* ----------------------------------- env ---------------------------------- */
char	*env_get_value(char	*key);
void	env_init_list(char **env);
void	env_change_value(char *key, char *new_value);

/* -------------------------------- execution ------------------------------- */
void	create_tree(void);
t_token	*append_two_token(t_token *tokone, t_token *toketwo);
t_tree 	*create_and_or(void);

/* --------------------------------- parser --------------------------------- */
t_token	*get_token();

/* ---------------------------------- lexer --------------------------------- */
int		is_token(char *str, int i);
int		find_token_id(char *token);
int		is_quoted(int index, char *cmd);
int		find_end(void);
int		peek_token(void);
void	init_scanner(char *cmd);
char	*scan_token(void);
void	skip_whitespaces(char *cmd, int *i);

/* -------------------------------- singleton ------------------------------- */
t_data		*_data(void);
t_scanner	*_scanner(void);
t_list		**_list(void);
t_tree		**_tree(void);

/* ---------------------------------- error --------------------------------- */
void	error_parsing(char *msg);

/* ---------------------------------- free ---------------------------------- */
void	free_all(int flag);
void	free_matrix(char **matrix);

/* ----------------------------------- len ---------------------------------- */
int	tab_len(char **cmd);

/* ------------------------------ list_function ----------------------------- */
int		ft_lstsize(t_list *lst);
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_lstadd_front(t_list **alst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstdelone(t_list *lst, void (*del)(void*));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(char *key, char *value);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/* ---------------------------------- print --------------------------------- */
void	print_tab(char **tab);
void	print_lst(void);
void	print_tree(void);

/* ---------------------------------- utils --------------------------------- */
char	*ft_substring(char const *s, unsigned int start, size_t end);
void	update_last_cmd_status(int status);

/* ---------------------------------- tree ---------------------------------- */
t_tree	*create_node(t_token *token, t_tree *l_child, t_tree *r_child);

/* ----------------------------- transformation ----------------------------- */
char	**split_quoted(char *cmd);
char	*unquote_line(char *cmd);
char	**unquote(char **cmd);

#endif
