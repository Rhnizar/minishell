/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 09:09:38 by kchaouki          #+#    #+#             */
/*   Updated: 2023/05/23 20:53:04 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PARSING_H
# define PARSING_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <fcntl.h>
# include <sys/errno.h>
# include <signal.h>

/*--------------tokens's linked list-------------*/
typedef struct s_tokens
{
	char			*str;
	struct s_tokens	*prev;
	struct s_tokens	*next;
}	t_tokens;

/*----------------check syntax error-------------*/
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

/*-------------check for global split------------*/
typedef struct s_check
{
	char 	*str;
	char	*ot;
	char	**split;
	int		dq;
	int		sq;
	int		sid;
}			t_check;

/*------linked list of environment variables------*/
typedef struct s_env
{
	char			*content;
	struct s_env	*next;
}	t_env;

/*---------linked list for redirections--------*/
typedef struct s_redis
{
	char			*str;
	int				type;
	struct s_redis	*next;
}		t_redis;

/*----------linked list for arguments----------*/
typedef struct s_args
{
	char			*str;
	struct s_args	*next;
}		t_args;

/*-------utils to fill commands's struct------*/
typedef	struct s_utils
{
	char	**spl_sp_char;
	char	**spl_redi;
	int		red_id;
	int		sp_id;
	int		red_id_prev;
	int		sp_id_prev;
	int		red_id_prev_prev;
}			t_utils;

/*-------------command's struct---------------*/
typedef struct s_cmds
{
	char	*cmd;
	t_redis	*redis;
	int		is_builtin;
	t_args	*args;
	int		operator;
	char	*subshell;
}				t_cmds;

/*----------linked list of commands--------*/
typedef struct s_cmdshell
{
	t_cmds	*cmds;
	struct s_cmdshell	*next;                               
}	t_cmdshell;







# endif