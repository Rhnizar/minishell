/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:40:00 by kchaouki          #+#    #+#             */
/*   Updated: 2023/05/04 11:58:02 by rrhnizar         ###   ########.fr       */
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




//////////////// struct ///////////////

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