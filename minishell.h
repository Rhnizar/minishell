/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:40:00 by kchaouki          #+#    #+#             */
/*   Updated: 2023/05/10 14:50:08 by rrhnizar         ###   ########.fr       */
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



// #define BONUS 0

#define PIPE 0
#define RED_IN 1
#define RED_OUT 2
#define PAR_OPEN 3
#define PAR_CLOSE 4
#define WLDC 5

#define AND 6
#define APP 7
#define CMD 8
#define OR  9
#define HERE_DOC 10
#define	ARG 11

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
	char			*str;
	struct s_env	*next;
}	t_env;

//////////////// struct ///////////////

typedef struct s_cmdshell
{
	char	*cmd;        //   /bin/cat
	int		is_builtin;
	char	**args;     //["cat", "-e", "filename"]
	t_env	*env;
	// int		exit_status;
	// int		pip;
	// char	**reds; // ==> append red_in red_out herdoc
	struct s_cmdshell	*next;
}	t_cmdshell;

///////////////// end struct ///////////


////// linked list /////

// typedef struct s_listt
// {
// 	t_cmdshell			*cmdshell;
// 	struct s_listt		*next;
// }				t_listt;

//// end linked list //////


/////// global struct /////

// typedef struct s_global
// {
// 	t_listt		*lst;
// 	pid_t		*pids;
// 	int			num_pips;	
// }				t_global;

int		len_first_split(char *str);
int		char_in_string(char c, char *ref);
char	*join_to_str(char *str, char c);
char	**my_split(char *str);
void	free_double_ptr(char **str);
void	create_tokens(t_tokens **lst, char *str, int type);
t_tokens	*split_and_fill_list(char **split);
void		free_tokens(t_tokens *tokens);

# endif