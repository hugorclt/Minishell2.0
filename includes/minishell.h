/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:34:37 by hrecolet          #+#    #+#             */
/*   Updated: 2022/11/15 17:46:46 by hrecolet         ###   ########.fr       */
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
	t_list	*grammar_list;
	char	*token_list[8]; //pas a free
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


/* -------------------------------------------------------------------------- */
/*                                    color                                   */
/* -------------------------------------------------------------------------- */
# define C_RED "\033[1;31m"
# define C_GREEN "\033[1;32m"
# define C_BLUE "\033[1;33m"
# define C_WHITE "\033[97m"
# define C_PURPLE "\033[1;35m"
# define C_ORANGE "\033[38:5:208m"
# define C_RESET "\033[0m"

/* -------------------------------------------------------------------------- */
/*                                  prototype                                 */
/* -------------------------------------------------------------------------- */
/* -------------------------------- execution ------------------------------- */


/* --------------------------------- parser --------------------------------- */


/* ---------------------------------- lexer --------------------------------- */
void	lexer(char *cmd);

/* -------------------------------- singleton ------------------------------- */
t_data	*_data(void);
t_list	**_list(void);

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
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);

/* ---------------------------------- print --------------------------------- */
void	print_tab(char **tab);
void	print_lst(void);

/* ---------------------------------- utils --------------------------------- */
char	*ft_substring(char const *s, unsigned int start, size_t end);

#endif
