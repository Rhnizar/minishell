/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:40:00 by kchaouki          #+#    #+#             */
/*   Updated: 2023/05/16 20:19:09 by kchaouki         ###   ########.fr       */
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
// # define EARGS "Invalid argumments\n"
# define ENSFD ": No such file or directory\n"
# define ECNF ": command not found\n"
# define EPD ": Permission denied\n"
# define ESYNTX "minishell: syntax error near unexpected token `"
# define EAMBGRD ": ambiguous redirect"
#define BONUS 1

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

int		arg_len(char *s);
char	*join_to_str(char *str, char c);
char	*ft_join_strings(char *s1, char *s2);
char	*quotes_handler(char *arg);
void	free_double_ptr(char **str);
int		syntax_error_handler(char *arg);
void	here_doc(char *delimiter);


void	print_error(char *msg, char *arg, int status);

# endif