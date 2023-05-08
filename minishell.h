/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:40:00 by kchaouki          #+#    #+#             */
/*   Updated: 2023/05/08 09:29:31 by rrhnizar         ###   ########.fr       */
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

#define APP 6
#define CMD 7
#define AND 8
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


// void	print_list(t_cmdshell *lst);
// char	*fill_arr_char(void);
/////// fill list /////
void	*command(char *line);
void	*option(char *line);
void	*argument(char *line);
void	create_list(t_tokens **tokens, char *str, int type);
void	split_with_char(char *str, t_tokens **token);

# endif