/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 18:34:13 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/06/01 15:57:57 by kchaouki         ###   ########.fr       */
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
		printf("declare -x %s=\"%s\"\n", tmp_export->var, tmp_export->value);
		tmp_export = tmp_export->next;
	}
}

void	add_to_export_or_print(t_env *env, t_env *export, t_args *args)
{
	char		*value;
	size_t		equal;

	equal = 0;
	if (!args->next)
		print_export(export);
	else
	{
		equal = find_equale(args->next->str);
		if (equal == ft_strlen(args->next->str))
			add_to_env(&export, ft_strdup(args->next->str), ft_strdup(""));
		else
		{
			if (args->next->str[equal + 1] == '\0')
				value = ft_strdup("");
			else
				value = ft_strdup((ft_strchr(args->next->str, '=') + 1));
			add_to_env(&export, ft_substr(args->next->str, 0, equal), ft_strdup(value));
			add_to_env(&env, ft_substr(args->next->str, 0, equal), value);
		}
	}
}