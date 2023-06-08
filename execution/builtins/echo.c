/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 09:07:25 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/06/08 21:45:41 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_opt(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	echo2(t_args *tmp_args)
{
	int	r;

	r = 0;
	while (tmp_args)
	{
		if (check_opt(tmp_args->str) == 1)
		{
			r = 1;
			tmp_args = tmp_args->next;
			continue ;
		}
		if (tmp_args->next)
			printf("%s ", tmp_args->str);
		else
			printf("%s", tmp_args->str);
		tmp_args = tmp_args->next;
	}
	if (r == 0)
		printf("\n");
}

void	echo(t_global *global, t_args *args)
{
	t_args	*tmp_args;

	if (args)
	{
		if (args->next)
		{
			tmp_args = args->next;
			echo2(tmp_args);
		}
		else
			printf("\n");
		global->exit_status = 0;
	}
}
