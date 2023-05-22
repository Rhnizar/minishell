/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:05:08 by kchaouki          #+#    #+#             */
/*   Updated: 2023/05/22 22:26:15 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

void	free_env(t_env *env)
{
	t_env	*tmp;
	t_env	*tmp2;

	tmp = env;
	while (tmp)
	{
		tmp2 = tmp->next;
		free (tmp->content);
		free (tmp);
		tmp = tmp2;
	}
}

static void	add_to_env(t_env **env, char *content)
{
	t_env	*new;
	t_env	*tmp;

	new = malloc(sizeof(t_env));
	if (!new)
	{
		free_env(*env);
		return ;
	}
	new->content = content;
	new->next = NULL;
	if (!*env)
	{
		*env = new;
		return ;
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_env	*create_env(char **envp)
{
	t_env	*env;

	env = NULL;
	while (*envp)
	{
		add_to_env(&env, strdup(*envp));
		envp++;
	}
	return (env);
}

static int	count_env_variables(t_env *env)
{
	t_env	*tmp;
	int		count;

	count = 0;
	tmp = env;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

char	**env_to_double_ptr(t_env *env)
{
	char	**output;
	int		i;

	output = malloc(sizeof(char *) * (count_env_variables(env) + 1));
	if (!output)
		return (NULL);
	i = 0;
	while (env)
	{
		output[i++] = ft_strdup(env->content);
		env = env->next;
	}
	output[i] = NULL;
	return (output);
}

// search for a variable if alredy exist on the env variables then update it ?(I THINK I WILL NEED IT IN EXPORT BUILTIN FUNCTION)


// void	print_env(t_env *env)
// {
// 	t_env	*tmp;

// 	tmp = env;
// 	while (tmp)
// 	{
// 		printf("%s\n", tmp->content);
// 		tmp = tmp->next;
// 	}
// }

// int main(int ac, char **av, char **envp)
// {
// 	t_env	*env;
// 	(void)	ac;
// 	(void)	av;
// 	print_env(env);
// 	printf("--------------------\n");
// 	int i = -1;
// 	char	**envdptr = env_to_double_ptr(env); 
// 	while (envdptr && envdptr[++i])
// 		printf("%s\n", envdptr[i]);
// 	free_env(env);
// 	free_double_ptr(envdptr);
// 	return 0;
// }
