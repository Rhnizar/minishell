/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:40:05 by kchaouki          #+#    #+#             */
/*   Updated: 2023/05/07 20:18:49 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	free_env(t_env *env)
// {
	
// }

static void	add_to_env(t_env **env, char *content)
{
	t_env	*new;
	t_env	*tmp;

	new = malloc(sizeof(t_env));
	if (!new)
	{
		// free_env(env);
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
		add_to_env(&env, *envp);
		envp++;
	}
	return (env);
}

int	count_env_variables(t_env *env)
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

// char	**env_to_double_ptr(t_env *env)
// {
// 	char	**output;

// 	return (output);
// }

// search for a variable if alredy exist on the env variables then update it ?(I THINK I WILL NEED IT IN EXPORT BUILTIN FUNCTION)

void	print_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
}

int main(int ac, char **av, char **envp)
{
	t_env	*env;

	(void) ac;
	(void) av;

	env = create_env(envp);

	char *read_line;
	// char *ret_quote;
	while (1)
	{
		env = create_env(envp);
    	read_line = readline("minishell> ");
		print_env(env);
		printf("%d\n", count_env_variables(env));
		// print_error(ECNF, "test", 0);
		// ret_quote = quotes_handler(read_line);
		// printf("%s\n", ret_quote);
		// free (ret_quote);
		
		add_history(read_line);
	}
	// add_to_env(&env, "test1");
	// add_to_env(&env, "test2");
	// add_to_env(&env, "test3");
	// add_to_env(&env, "test4");
	// printf("%s\n", env->next->content);
	// printf("%s\n", env->next->next->content);
	// printf("%s\n", env->next->next->next->content);
	// printf("%s\n", env->content);
	return 0;
}