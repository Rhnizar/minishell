/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:40:00 by kchaouki          #+#    #+#             */
/*   Updated: 2023/05/04 12:58:50 by kchaouki         ###   ########.fr       */
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
# define EARGS "Invalid argumments\n"
# define ENSFD ": No such file or directory\n"
# define ECNF ": command not found\n"
# define EPD ": Permission denied\n"

typedef struct s_cmdshell
{
	char	*cmd;
	char	*opt;
	char	*arg;
	int		pip;
	char	*herdoc;
	char	*append;
	char	*variable;
	char	*red_in;
	char	*red_out;
	int		and;
	int		or;
}				t_cmdshell;

////// linked list /////

typedef struct s_list
{
	t_cmdshell			*cmdshell;
	struct s_list		*next;
}				t_list;

/////// global struct /////

typedef struct s_global
{
	t_list		*lst;
	pid_t		*pids;
	int			num_pips;
}				t_global;

char	*quotes_handler(char *str);
void	print_error(char *msg, char *arg, int status);

# endif