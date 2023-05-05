/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:40:00 by kchaouki          #+#    #+#             */
/*   Updated: 2023/05/05 12:27:28 by rrhnizar         ###   ########.fr       */
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
#define SEMC 6

#define APP 8
#define CMD 9
#define AND 10
#define OR  11
#define HER 12
#define	ARG 13
#define OPT	14


// typedef struct s_tokens
// {
// 	char	*str = "|"
// 	int		type = PIPE;
	
// }	t_tokens;

//////////////// struct ///////////////

typedef struct s_cmdshell
{
	char	*cmd;
	char	*opt;
	char	*arg;
	int		pip;
	char	**reds; // ==> append red_in red_out herdoc
	int		and;
	int		or;
}				t_cmdshell;

///////////////// end struct ///////////


////// linked list /////

typedef struct s_listt
{
	t_cmdshell			*cmdshell;
	struct s_listt		*next;
}				t_listt;

//// end linked list //////


/////// global struct /////

typedef struct s_global
{
	t_listt		*lst;
	pid_t		*pids;
	int			num_pips;	
}				t_global;

void	print_list(t_cmdshell *lst);

/////// fill list /////
void	*command(char *line);
void	*option(char *line);
void	*argument(char *line);

# endif