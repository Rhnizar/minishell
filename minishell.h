/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:40:00 by kchaouki          #+#    #+#             */
/*   Updated: 2023/05/31 20:26:13 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "parsing/parsing.h"

# define PATH "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:\
/usr/local/munki"
# define ENSFD ": No such file or directory\n"
# define ECNF ": command not found\n"
# define EPD ": Permission denied\n"
# define ESYNTX "minishell: syntax error near unexpected token `"
# define EAMBGRD ": ambiguous redirect"

typedef enum e_redirtypes
{
	FILE_APPEND,
	HEREDOC,
	FILE_IN,
	FILE_OUT,
	OR,
	AND,
	PIPE
}	t_rtype;

typedef struct s_global
{
	int			exit_status;
	int			pipe[2];
	t_env		*env;
	t_cmdshell	*all_commands;
}			t_global;

int	fill_global_struct(t_global **global, char *line, char **environment);
void		free_args(t_args *args);
void		free_redis(t_redis *redis);


/*========= start expender =============*/
t_args		*args_expander(t_args *args, t_env *env);
char		*remove_quotes(char *str);
t_tokens	*expantion_tokenizer(char *token);
char		*get_value(char *to_expand, t_env *env);
char		*expantion_quote_case(t_tokens **tmp, t_env *env, char *old);
/*========= end expender =============*/


# endif