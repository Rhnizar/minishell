/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 12:32:56 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/06/05 15:39:25 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	unset_var(t_env **env_exp, char *var)
{
	t_env	*tmp_env_exp;

	tmp_env_exp = *env_exp;
	while (tmp_env_exp)
	{
		if (ft_strcmp(var, tmp_env_exp->var) == 0)
		{
			tmp_env_exp->prev->next = tmp_env_exp->next;
			// tmp_env_exp->next->prev = tmp_env_exp->prev;
			tmp_env_exp = tmp_env_exp->next;
			continue ;
		}
		tmp_env_exp = tmp_env_exp->next;
	}
	
}

void	unset(t_env **env, t_env **export, t_args *args)
{
	t_args	*tmp_args;

	tmp_args = args;
	if (ft_strcmp("unset", tmp_args->str) == 0)
	{
		if (tmp_args->next)
		{
			while (tmp_args)
			{
				if (search_var(*export, tmp_args->str))
				{
					unset_var(export, tmp_args->str);
					if (search_var(*env, tmp_args->str))
						unset_var(env, tmp_args->str);
				}
				tmp_args = tmp_args->next;
			}
		}
	}
}
