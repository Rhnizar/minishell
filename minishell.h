/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:40:00 by kchaouki          #+#    #+#             */
/*   Updated: 2023/06/04 18:50:03 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "parsing/parsing.h"
# include "execution/execution.h"
# include <readline/readline.h>
# include <readline/history.h>


# define PATH "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:\
/usr/local/munki"
# define ENSFD ": No such file or directory\n"
# define ECNF ": command not found\n"
# define EPD ": Permission denied\n"
# define ESYNTX "minishell: syntax error near unexpected token `"
# define EAMBGRD ": ambiguous redirect"

# include <termios.h>

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
	t_env		*export;
	t_cmdshell	*all_commands;
}			t_global;

t_args		*args_expander(t_global *global);
int			count_split(char **split);


int			fill_global_struct(t_global **global, char *line);
int			init_global(t_global **global, char **env);
/*------- all free --------*/
void		free_double_ptr(char **str);
void		free_commands(t_cmdshell *comands);
void		global_free(t_global *global);
void		free_redis(t_redis *redis);
void		free_args(t_args *args);
void		free_env(t_env *env);
void		free_tokens(t_tokens *tokens);
void		free_token_utils(t_utils *utils, t_tokens *tokens);



#endif
