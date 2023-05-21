/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:40:00 by kchaouki          #+#    #+#             */
/*   Updated: 2023/05/21 14:45:03 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <string.h>
# include <fcntl.h>
# include <sys/errno.h>
# include <signal.h>

/////// redirection ///////
// >> << < >
#define APP 0
#define HERE_DOC 1
#define RED_IN 2
#define RED_OUT 3

////// end /////////
// || && |
#define OR  0
#define AND 1
#define PIPE 2

// #define PAR_OPEN 3
// #define PAR_CLOSE 4
// #define WLDC 5
// #define CMD 8
// #define	ARG 11

typedef struct s_tokens
{
	char			*str;
	struct s_tokens	*prev;
	struct s_tokens	*next;
}	t_tokens;

//////// struct t9sam token ///////

typedef struct s_check
{
	char 	*str;
	char	*ot;
	char	**split;
	int		dq;
	int		sq;
	int		sid;
}			t_check;

//////// struct for environment variables //////////

typedef struct s_env
{
	char			*str;
	struct s_env	*next;
}	t_env;

typedef struct s_redis
{
	char			*str;
	int				type;
	struct s_redis	*next;
}		t_redis;

typedef struct s_args
{
	char			*str;
	struct s_args	*next;
}		t_args;

//// utils the fill struct commands ///////////

typedef	struct s_utils
{
	char	**spl_sp_char;
	char	**spl_redi;
	// int		red_id;
	// int		sp_id;
}			t_utils;

////////////////// struct the comands shell ///////////

typedef struct s_cmds
{
	char	*cmd;        //   /bin/cat
	t_redis	*redis;
	int		is_builtin;
	t_args	*args;
	int		red_id;
	int		sp_id;
	char	*subshell;
	t_utils *utils;
}				t_cmds;

//////////////// struct ///////////////

typedef struct s_cmdshell
{
	t_cmds	*cmds;
	struct s_cmdshell	*next;                               
}	t_cmdshell;

typedef struct s_global
{
	int			exit_status;
	t_env		*env;
	t_cmdshell	*all_commands;
}			t_global;

///////////////// end struct ///////////


int		len_first_split(char *str);
int		char_in_string(char c, char *ref);
char	*join_to_str(char *str, char c);
char	**my_split(char *str);
void	free_double_ptr(char **str);
void	create_tokens(t_tokens **lst, char *str);
void		free_tokens(t_tokens *tokens);
int	check_syntax(char *str, char *ref);
char	**fill_with_null(int len);
int count_quote(char *str, int r);
char **split_quote(char *str, int r);

////// utils global split ///////
int			find_separator(char **sep, char *str);
int			str_in_string(char *str);
void		init_check(t_check	*check, char *read_line);
t_tokens	*split_and_fill_list(char *output);
void		dq_sq(t_check *check, int *i, int *dq_or_sq);
void		check_quote(t_check *check, int *i);
void		check_space_tab(t_check *check, int *i);

///////// utils fill struct commands /////
// int			check_quote_cmd(char *str);
// int			check_sep_or_red(char *str, char **str_to_check);
// void		init_cmd(t_cmds **cmds, t_tokens *tokens);
// t_cmdshell	*fill_list_cmds(t_cmdshell *lst, t_tokens *token);
// int			check_subshell(char *str);

////////////////////  next  idea the define ////////
int	init_global(t_global *glob);
int	init_struct_cmds(t_cmds **cmds);

# endif