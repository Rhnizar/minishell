/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:40:00 by kchaouki          #+#    #+#             */
/*   Updated: 2023/05/19 20:03:19 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h" 
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/errno.h>
# include <signal.h>

# define PATH "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:\
/usr/local/munki"
# define ENSFD ": No such file or directory\n"
# define ECNF ": command not found\n"
# define EPD ": Permission denied\n"
# define ESYNTX "minishell: syntax error near unexpected token `"
# define EAMBGRD ": ambiguous redirect"

# ifndef BONUS
#  define BONUS 0
# endif

# define PIPE 0
# define RED_IN 1
# define RED_OUT 2
# define PAR_OPEN 3
# define PAR_CLOSE 4
# define WLDC 5

# define APP 6
# define CMD 7
# define AND 8
# define OR  9
# define HERE_DOC 10
# define ARG 11

typedef struct s_tokens
{
	char			*str;
	int				type;
	struct s_tokens	*prev;
	struct s_tokens	*next;
}	t_tokens;

//////// struct for environment variables //////////
typedef struct s_env
{
	char	*content;
	struct s_env	*next;
}	t_env;

//////// struct t9sam token ///////
typedef struct s_check
{
	char *str;
	char *ot;
	char **split;
	int	dq;
	int sq;
	int sid;
}			t_check;

// typedef struct s_cmdshell
// {
// 	char	*cmd; /bin/cat
// 	char	**args; ["cat", "-e", "filename"]
// 	t_env	*env;
// 	// int		pip;
// 	// char	**reds; // ==> append red_in red_out herdoc
// 	t_cmdshell	*next;
// }	t_cmdshell;

char	**env_to_double_ptr(t_env *env);
t_env	*create_env(char **envp);
void	free_env(t_env *env);

// //utiles 1
// int		skip_spaces(char *str);
// int		arg_len(char *s);
// char	*ft_join_strings(char *s1, char *s2);
// char	*join_with_space(char *old, char *arg);

// //utiles 2
// char	*find_separator(char **sep, char *str, int *sp);
// char	*recognize_quote(int quote);
// void	syntx_error(char *arg);
// char	**create_separator(void);
// int		is_quote(char c);

// //-----------------
// void	run_here_docs(char *str);
// void	check_parentheses(char *str);
// char	*quotes_handler(char *arg);
// int		syntax_error_handler(char *arg);

////// minishell utils
char	*join_to_str(char *str, char c);
void	free_double_ptr(char **str);

//create tokens
void	create_tokens(t_tokens **lst, char *str, int type);


////// utils global split ///////
int			find_separator(char **sep, char *str);
int			str_in_string(char *str);
void		init_check(t_check	*check, char *read_line);
t_tokens	*split_and_fill_list(char *output);
void		dq_sq(t_check *check, int *i, int *dq_or_sq);
void		check_quote(t_check *check, int *i);
void		check_space_tab(t_check *check, int *i);



void	print_error(char *msg, char *arg, int status);

# endif