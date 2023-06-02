/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 18:34:13 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/06/02 19:00:13 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*_export(t_env *env)
{
	t_env	*export;
	t_env	*tmp_env;

	tmp_env = env;
	export = NULL;
	while (tmp_env)
	{
		add_to_env(&export, ft_strdup(tmp_env->var), ft_strdup(tmp_env->value));
		tmp_env = tmp_env->next;
	}
	return (export);
}

static void	print_export(t_env *export)
{
	t_env	*tmp_export;

	tmp_export = export;
	while (tmp_export)
	{
		if (tmp_export->value != NULL)
			printf("declare -x %s=\"%s\"\n", tmp_export->var, tmp_export->value);
		else
			printf("declare -x %s\n", tmp_export->var);
		tmp_export = tmp_export->next;
	}
}

int	search_var(t_env *export, char *var)
{
	t_env	*tmp_export;

	tmp_export = export;
	while (tmp_export)
	{
		if (ft_strcmp(tmp_export->var, var) == 0)
			return (1);
		tmp_export = tmp_export->next;
	}
	return (0);
}

void	edit_value2(t_env *exp_or_env, char *var, size_t equal, char *str)
{
	t_env	*tmp_exp_env;

	tmp_exp_env = exp_or_env;
	while (tmp_exp_env)
	{
		if (ft_strcmp(tmp_exp_env->var, var) == 0)
		{
			free(tmp_exp_env->value);
			if (equal == ft_strlen(str))
				tmp_exp_env->value = ft_strdup("");
			else
			{
				if (str[equal + 1] == '\0')
					tmp_exp_env->value = ft_strdup("");
				else
					tmp_exp_env->value = ft_strdup((ft_strchr(str, '=') + 1));
			}
			break ;
		}
		tmp_exp_env = tmp_exp_env->next;
	}
	if (!tmp_exp_env)
		add_to_env(&exp_or_env, var, ft_strdup((ft_strchr(str, '=') + 1)));
}

void	edit_value(t_env *env, t_env *export, char *str)
{
	char		*var;
	size_t		equal;

	equal = find_equale(str);
	var = ft_substr(str, 0, equal);
	edit_value2(export, var, equal, str);
	edit_value2(env, var, equal, str);
}

void	add_env_exp2(t_env *export, t_env *env, char *str, size_t equal)
{
	char	*value;

	if (str[equal + 1] == '\0')
		value = ft_strdup("");
	else
		value = ft_strdup((ft_strchr(str, '=') + 1));
	add_to_env(&export, ft_substr(str, 0, equal), ft_strdup(value));
	add_to_env(&env, ft_substr(str, 0, equal), value);
}

// int	identifier(char *str)
// {
// 	return(0);
// }
void	add_to_export_or_print(t_env *env, t_env *export, t_args *args)
{
	size_t		equal;
	char		*var;

	equal = 0;
	if (!args->next)
		print_export(export);
	else
	{
		// valid identifier ==> if kayn return ;
		equal = find_equale(args->next->str);
		var = ft_substr(args->next->str, 0, equal);
		if (search_var(export, var) == 1)
		{
			if (ft_strchr(args->next->str, '=') != NULL)
				edit_value(env, export, args->next->str);
			else
				return ;
		}
		else if (equal == ft_strlen(args->next->str))
			add_to_env(&export, ft_strdup(args->next->str), NULL);
		else
			add_env_exp2(export, env, args->next->str, equal);
	}
}
