/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 12:32:56 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/06/06 12:14:26 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*delete_node(t_env **env_exp, char *var)
{
	t_env	*tmp_env_exp;

	tmp_env_exp = *env_exp;
	while (tmp_env_exp)
	{
		if (ft_strcmp(var, tmp_env_exp->var) == 0)
			return (tmp_env_exp);
		tmp_env_exp = tmp_env_exp->next;
	}
	return (NULL);
}

void	unset_var(t_env **env_exp, char *var)
{
	t_env	*del_node;

	del_node = delete_node(env_exp, var);
	if (!del_node)
		return ;
	if (del_node == *env_exp)
		*env_exp = del_node->next;
	if (del_node->next)
		del_node->next->prev = del_node->prev;
	if (del_node->prev)
		del_node->prev->next = del_node->next;
	free(del_node->value);
	free(del_node->var);
	free(del_node);
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
				unset_var(export, tmp_args->str);
				unset_var(env, tmp_args->str);
				tmp_args = tmp_args->next;
			}
		}
	}
}
