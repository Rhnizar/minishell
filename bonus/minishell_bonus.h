/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:40:00 by kchaouki          #+#    #+#             */
/*   Updated: 2023/05/22 22:32:47 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h" 
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

//syntax_check
typedef struct s_syntax_check
{
	t_tokens	*all_tokens;
	t_tokens	*token;
	char		**sep;
	int			index_par;
	int			par;
	int			index;
	int			sp_id;
}	t_syntax_check;

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
int		count_tokens(t_tokens *tokens);
void	free_tokens(t_tokens *tokens);


////// utils global split ///////
int			find_separator(char **sep, char *str);
int			str_in_string(char *str);
void		init_check(t_check	*check, char *read_line);
t_tokens	*split_and_fill_list(char *output);
void		dq_sq(t_check *check, int *i, int *dq_or_sq);
void		check_quote(t_check *check, int *i);
void		check_space_tab(t_check *check, int *i);


// analyser
int		syntax_error_handler(t_tokens *tokens);
int		check_separators(t_syntax_check	check, int *par, int *i_par);
void	here_doc_befor_error(t_tokens *tokens, int index);
int		is_separator(char *token, char **sep);
void	syntx_error(char *arg);


void	print_error(char *msg, char *arg, int status);

# endif