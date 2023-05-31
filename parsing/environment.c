/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 19:30:32 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/31 19:44:00 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_env(t_env *env)
{
	t_env	*tmp;
	t_env	*tmp2;

	tmp = env;
	while (tmp)
	{
		tmp2 = tmp->next;
		free (tmp->var);
		free (tmp->value);
		free (tmp);
		tmp = tmp2;
	}
}

static void	add_to_env(t_env **env, char *var, char *value)
{
	t_env	*new;
	t_env	*tmp;

	new = malloc(sizeof(t_env));
	if (!new)
	{
		free_env(*env);
		return ;
	}
	new->var = var;
	new->value = value;
	new->next = NULL;
	new->prev = NULL;
	if (!*env)
	{
		*env = new;
		return ;
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

static int	find_equale(char *str)
{
	int	count;

	count = 0;
	while (str[count] && str[count] != '=')
		count++;
	return (count);
}

t_env	*create_env(char **envp)
{
	t_env	*env;

	env = NULL;
	while (*envp)
	{
		add_to_env(&env, ft_substr(*envp, 0, find_equale(*envp)), \
		ft_strdup(ft_strchr(*envp, '=') + 1));
		envp++;
	}
	return (env);
}
