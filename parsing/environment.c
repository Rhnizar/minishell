/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 19:30:32 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/31 18:45:39 by kchaouki         ###   ########.fr       */
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
	int count;

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
		add_to_env(&env, ft_strdup(ft_substr(*envp, 0, find_equale(*envp))), \
		ft_strdup(ft_strchr(*envp, '=') + 1));
		envp++;
	}
	return (env);
}


// static int	count_env_variables(t_env *env)
// {
// 	t_env	*tmp;
// 	int		count;

// 	count = 0;
// 	tmp = env;
// 	while (tmp)
// 	{
// 		count++;
// 		tmp = tmp->next;
// 	}
// 	return (count);
// }

// char	**env_to_double_ptr(t_env *env)
// {
// 	char	**output;
// 	int		i;

// 	output = malloc(sizeof(char *) * (count_env_variables(env) + 1));
// 	if (!output)
// 		return (NULL);
// 	i = 0;
// 	while (env)
// 	{
// 		output[i++] = ft_strdup(env->content);
// 		env = env->next;
// 	}
// 	output[i] = NULL;
// 	return (output);
// }
