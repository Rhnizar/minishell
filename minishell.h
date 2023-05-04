/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:40:00 by kchaouki          #+#    #+#             */
/*   Updated: 2023/05/03 16:58:39 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>




//////////////// struct ///////////////

typedef struct s_list
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
}				t_list;

///////////////// end struct ///////////


////// linked list /////

typedef struct s_test
{
	t_list			*lst;
	struct s_test	*next;
}			t_test;

//// end linked list //////

void	print_list(t_list *lst);

/////// fill list /////
void	*command(char *line);
void	*option(char *line);
void	*argument(char *line);

# endif