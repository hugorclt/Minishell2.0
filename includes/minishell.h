/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:34:37 by hrecolet          #+#    #+#             */
/*   Updated: 2022/11/18 19:09:44 by lbisson          ###   ########.fr       */
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

typedef struct s_data
{
	char	*token_list[8]; //pas a free
	t_list	*grammar_lst;
}	t_data;


typedef struct s_tree
{
	int				id;
	struct s_tree 	*left;
	struct s_tree 	*right;
}	t_tree;

/* -------------------------------------------------------------------------- */
/*                                   define                                   */
/* -------------------------------------------------------------------------- */
# define TRUE 1
# define FALSE 0
# define NB_TOKEN 7

/* ------------------------------- token_type ------------------------------- */
# define CMD 7
# define PIPE 6
# define INFILE 5
# define HEREDOC 3
# define OUTFILE 4
# define OUTFILE_APND 2
# define AND 0
# define OR 1

/* ------------------------------- error_type ------------------------------- */
# define CD_ERROR				1
# define CWD_ERROR				1
# define MALLOC_ERROR			1
# define SYNTAX_ERROR			2
# define CMD_NOT_FOUND			127
# define EXIT_TOO_MANY_ARGS		1
# define EXIT_NUM_ARG_REQUIRED	2
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

/* -------------------------------------------------------------------------- */
/*                                  prototypes                                */
/* -------------------------------------------------------------------------- */
/* -------------------------------- execution ------------------------------- */


/* --------------------------------- parser --------------------------------- */


/* ---------------------------------- lexer --------------------------------- */
void	lexer(char *cmd);

/* -------------------------------- singleton ------------------------------- */
t_data	*_data(void);
t_list	**_list(void);

/* ---------------------------------- error --------------------------------- */
void	error_parsing(char *msg);

/* ---------------------------------- free ---------------------------------- */
void	free_all(void);

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

/* ---------------------------------- utils --------------------------------- */
char	*ft_substring(char const *s, unsigned int start, size_t end);

#endif
