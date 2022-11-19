/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:34:37 by hrecolet          #+#    #+#             */
/*   Updated: 2022/11/19 10:44:58 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

/* -------------------------------------------------------------------------- */
/*                                  includes                                  */
/* -------------------------------------------------------------------------- */
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "../Libft/libft.h"

/* -------------------------------------------------------------------------- */
/*                                  structure                                 */
/* -------------------------------------------------------------------------- */
typedef struct s_token
{
	int		id;
	char	*cmd;
}	t_token;

typedef struct s_list
{
	t_token			*token;
	struct s_list	*next;
}					t_list;

typedef struct	s_scanner
{
	char	*token_tab[10];
	char	*cmd;
	int		start_pos;
	int		end_pos;
}	t_scanner;


typedef struct s_tree
{
	t_token			*token;
	struct s_tree 	*left;
	struct s_tree 	*right;
}	t_tree;

typedef struct s_data
{
	t_list		*grammar_lst;
	t_scanner	scanner;
	t_tree		*tree;
}	t_data;
/* -------------------------------------------------------------------------- */
/*                                   define                                   */
/* -------------------------------------------------------------------------- */
# define TRUE 1
# define FALSE 0
# define NB_TOKEN 10

/* ------------------------------- token_type ------------------------------- */
# define AND 0
# define OR 1
# define OUTFILE_APND 2
# define HEREDOC 3
# define OUTFILE 4
# define INFILE 5
# define PIPE 6
# define CMD 7
# define LPARENTH 8
# define RPARENTH 9

/* ------------------------------- error_type ------------------------------- */
# define CD_ERROR				1
# define CWD_ERROR				1
# define MALLOC_ERROR			1
# define SYNTAX_ERROR			2
# define CMD_NOT_FOUND			127
# define EXIT_TOO_MANY_ARGS		1
# define EXIT_NUM_ARG_REQUIRED	2
# define QUIT					1
# define FREE					2
/* exit with numeric value -> 
return the numeric value 
OU si >= à 256 et < 0 return value %2 */

/* -------------------------------------------------------------------------- */
/*                                    color                                   */
/* -------------------------------------------------------------------------- */
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define BLUE "\033[1;34m"
# define PINK "\033[1;95m"
# define WHITE "\033[97m"
# define PURPLE "\033[1;35m"
# define ORANGE "\033[38:5:208m"
# define RESET "\033[0m"

# define STEP_PRINT_TREE 10

/* -------------------------------------------------------------------------- */
/*                                  prototypes                                */
/* -------------------------------------------------------------------------- */
/* -------------------------------- execution ------------------------------- */


/* --------------------------------- parser --------------------------------- */


/* ---------------------------------- lexer --------------------------------- */
t_token	*scan_token(void);
char	*peek_token(void);
void	init_scanner(char *cmd);
int		is_token(char *str, int i);
int		find_token_id(char *token);
int		is_quoted(int index, char *cmd);
int		find_end(void);

/* -------------------------------- singleton ------------------------------- */
t_data		*_data(void);
t_list		**_list(void);
t_scanner	*_scanner(void);
t_tree		**_tree(void);

/* ---------------------------------- error --------------------------------- */
void	error_parsing(char *msg);

/* ---------------------------------- free ---------------------------------- */
void	free_all(int flag);

/* ------------------------------ list_function ----------------------------- */
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_lstadd_front(t_list **alst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstnew(int id, char *cmd);
int		ft_lstsize(t_list *lst);

/* ---------------------------------- print --------------------------------- */
void	print_tab(char **tab);
void	print_lst(void);
void	print_tree(void);
void	print_all_token(void);

/* ---------------------------------- utils --------------------------------- */
char	*ft_substring(char const *s, unsigned int start, size_t end);

/* ---------------------------------- tree ---------------------------------- */
t_tree	*create_node(t_token *token, t_tree *l_child, t_tree *r_child);

#endif
