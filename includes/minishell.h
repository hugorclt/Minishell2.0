/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:34:37 by hrecolet          #+#    #+#             */
/*   Updated: 2022/12/08 14:40:13 by lbisson          ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>

# include "../Libft/libft.h"

/* -------------------------------------------------------------------------- */
/*                                   define                                   */
/* -------------------------------------------------------------------------- */
# define TRUE					1
# define FALSE					0
# define OPEN 					1 
# define CLOSE 					0
# define STDOUT					1
# define STDIN					0
# define STDERR					2
# define SUCCESS				0
# define FAILURE				1
# define NB_TOKEN				10
# define STEP_PRINT_TREE		10

/* ------------------------------- token_type ------------------------------- */
# define AND					0
# define OR						1
# define OUTFILE_APND			2
# define HEREDOC				3
# define OUTFILE				4
# define INFILE					5
# define PIPE					6
# define LPARENTH				7
# define RPARENTH				8
# define CMD					9
# define EOL					10

/* ------------------------------- error_type ------------------------------- */
# define QUIT					1
# define FREE					2
# define CD_ERROR				1
# define MALLOC_ERROR			1
# define SYNTAX_ERROR			2
# define NOT_FOUND				127
# define EXIT_TOO_MANY_ARGS		1
# define EXIT_NUM_ARG_REQUIRED	2

/* -------------------------------- sig_type -------------------------------- */
# define SIG_PARSE				0
# define SIG_EXEC				1
# define SIG_HEREDOC			2

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
typedef void (*t_fptr)(char **);

/* -------------------------------------------------------------------------- */
/*                                  structure                                 */
/* -------------------------------------------------------------------------- */
typedef struct s_file
{
	char	*file;
	int		type;
}	t_file;

typedef	struct s_choice
{
	t_fptr	callback;
	char	*fun_name;
}	t_choice;

typedef struct s_token
{
	t_file	*infile;
	t_file	*outfile;
	char	**cmd;
	int		id;
	int		pipe[2];
	int		fd_in;
	int		fd_out;
	int		nb_file_in;
	int		nb_file_out;
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

typedef struct s_info_cmd
{
	u_char		last_cmd_status;
	int			index_cmd;
	int			index_cmd_start;
	int			nb_cmd;
	int			*pid;
}	t_info_cmd;

typedef struct s_data
{
	int			singleq;
	int			doubleq;
	int			nb_heredoc;
	t_info_cmd	info_cmd;
	t_list		*env;
	t_scanner	scanner;
	t_tree		*tree;
}	t_data;

/* -------------------------------------------------------------------------- */
/*                                  prototypes                                */
/* -------------------------------------------------------------------------- */
/* ----------------------------------- env ---------------------------------- */
char	*env_get_value(char	*key);
char	*env_get_key(char *key);
char	**env_to_matrix(void);
void	env_unset_key(char *key);
void	env_init_list(char **env);
void	env_add_node(char *key, char *value);
void	env_change_value(char *key, char *new_value);

/* -------------------------------- execution ------------------------------- */
char	*join_cmdpath(char *cmd);
void	exec_choice(t_tree *node);
void	exec_cmd(t_tree *node);
void	launch_exec(t_tree *node);
void	wait_cmd(void);
void	link_fd(t_tree *node);

/* --------------------------------- parser --------------------------------- */
int		create_tree(void);
t_token	*append_two_token(t_token *tokone, t_token *toketwo);
t_tree 	*create_and_or(void);

/* ---------------------------- parse_redirection --------------------------- */
void	create_temp_file(t_token **token, char *delimiter, int index);
void	parse_redirection(t_token **token, char **cmd);
void	open_file(t_tree *node);

/* ---------------------------------- lexer --------------------------------- */
int		is_token(char *str, int i);
int		find_token_id(char *token);
int		is_quoted(int index, char *cmd);
int		find_end(void);
int		peek_token(void);
char	*scan_token(void);
void	init_scanner(char *cmd);
void	skip_whitespaces(char *cmd, int *i);
t_token	*get_token(void);
int		check_cmd(char *cmd);
int		is_redir(int id);
int		strjoin_redir(t_token **token, char **cmd);
int 	peek_token_tree(void);

/* -------------------------------- builtins -------------------------------- */
void	builtin_cd(char **arg);
void	builtin_echo(char **arg);
void	builtin_env(char **arg);
void	builtin_exit(char **arg);
void	builtin_export(char **arg);
void	builtin_pwd(char **arg);
void	builtin_unset(char **arg);

/* -------------------------------- singleton ------------------------------- */
t_data		*_data(void);
t_scanner	*_scanner(void);
t_info_cmd	*_info_cmd(void);
t_list		**_list(void);
t_tree		**_tree(void);

/* ---------------------------------- error --------------------------------- */
void	error_parsing(char *msg);
void	print_error_unexpected(char *cmd);
void	error_opening(char *str);

/* ---------------------------------- free ---------------------------------- */
void	free_all(int flag);
void	free_matrix(char **matrix);
void	free_token(t_token *token);

/* ----------------------------------- len ---------------------------------- */
int	tab_len(char **cmd);

/* ------------------------------ list_function ----------------------------- */
int		ft_lstsize(t_list *lst);
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_lstadd_front(t_list **alst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void 	ft_lst_remove_if(t_list **begin_list, char *key_ref);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(char *key, char *value);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/* ---------------------------------- print --------------------------------- */
void	print_tab(char **tab);
void	print_lst(void);
void	print_tree(void);

/* ---------------------------------- utils --------------------------------- */
int		get_last_cmd_status(void);
void	update_last_cmd_status(int status);
void	sig_choice(int choice);
void	init_nb_cmd(t_tree *tree);

/* ---------------------------------- tree ---------------------------------- */
t_tree	*create_node(t_token *token, t_tree *l_child, t_tree *r_child);

/* ----------------------------- transformation ----------------------------- */
int		get_valid_dollar_index(char *cmd);
char	*get_key(char *cmd);
char	*get_before_dollar(char *cmd);
char	*get_dollar_value(char *cmd, char *key, char *before_dollar);
char	*unquote_line(char *cmd);
char	**split_quoted(char *cmd);
char	**unquote(char **cmd);
char	**expand(char **args);

#endif
