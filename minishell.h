/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:40:00 by kchaouki          #+#    #+#             */
/*   Updated: 2023/06/09 16:38:53 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "parsing/parsing.h"
# include "execution/execution.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <limits.h>
# include <dirent.h>

# define PATH "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:\
/usr/local/munki"
# define EIAD ": is a directory\n"
# define ENSFD ": No such file or directory\n"
# define ECNF ": command not found\n"
# define EPD ": Permission denied\n"
# define ESYNTX "minishell: syntax error near unexpected token `"
# define EAMBGRD ": ambiguous redirect\n"

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
	pid_t		*pid;
	int			tube[4];
	t_env		*env;
	t_env		*export;
	t_cmdshell	*all_commands;
}			t_global;

typedef	struct s_recipe
{
	char	*command;
	char	**args;
	char	**envp;
}	t_recipe;


t_args		*args_expander(t_global *global, t_args	*args);
t_redis		*redis_expander(t_global *global, t_redis *redis);


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

/*========== exit ==============*/
void	exitt(t_args *args);


/*========== pwd ==============*/
void	pwd(t_global *global);
/*========== cd ==============*/
void	cd(t_global *global, t_args	*args, t_env *export);
/*========== echo ==============*/
void	echo(t_global *global, t_args *args);



// void	handle_one_command(t_global *global, t_cmdshell **all_cmds);
// void	execution(t_global **global);

void	handle_one_command(t_global *global, t_cmdshell *all_cmds);
void	execution(t_global *global);
void	sig_handl(int sig);



#endif
