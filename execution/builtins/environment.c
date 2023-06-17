/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 19:30:32 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/06/16 15:26:35 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	add_to_env(t_env **env, char *var, char *value)
{
	t_env	*new;
	t_env	*tmp;

	new = malloc(sizeof(t_env));
	if (!new)
	{
		free_env(*env);
		print_error(NULL, NULL, 1);
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

size_t	find_equale(char *str)
{
	size_t	count;

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

void	print_env(t_env *env)
{
	t_env	*tmp_env;

	tmp_env = env;
	while (tmp_env)
	{
		ft_putstr_fd(tmp_env->var, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(tmp_env->value, 1);
		ft_putstr_fd("\n", 1);
		tmp_env = tmp_env->next;
	}
}
