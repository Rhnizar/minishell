/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 18:34:13 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/06/04 13:54:12 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	add_env_exp2(t_env **export, t_env **env, char *str, size_t equal)
{
	char	*value;

	if (str[equal + 1] == '\0')
		value = ft_strdup("");
	else
		value = ft_strdup((ft_strchr(str, '=') + 1));
	add_to_env(export, ft_substr(str, 0, equal), ft_strdup(value));
	add_to_env(env, ft_substr(str, 0, equal), value);
}

int	identifier(char *str)
{
	int	i;

	i = 0;
	if ((str[i] == '_' && (str[i + 1] && str[i + 1] == '=')) || str[i] == '#')
		return (1);
	if (str[i] == '=' || ft_isdigit(str[i]))
	{
		printf("bash: export: `%s': not a valid identifier\n", str);
		return (1);
	}
	while (str[i] && str[i] != '=')
	{
		if (ft_isalnum(str[i]) == 0)
		{
			if (str[i] != '_')
			{
				printf("bash: export: `%s': not a valid identifier\n", str);
				return (1);
			}
			return (9);
		}
		i++;
	}
	return (0);
}

void	add_env_exp3(t_env **env, t_env **export, t_args *arg)
{
	size_t		equal;
	char		*var;

	while (arg && arg->str)
	{
		if (identifier(arg->str) == 1)
		{
			if (arg->str[0] == '#')
				break ;
			arg = arg->next;
			continue ;
		}
		equal = find_equale(arg->str);
		var = ft_substr(arg->str, 0, equal);
		if (search_var(*export, var) == 1)
		{
			if (ft_strchr(arg->str, '=') != NULL)
				edit_value(*env, *export, arg->str);
		}
		else if (equal == ft_strlen(arg->str))
			add_to_env(export, ft_strdup(arg->str), NULL);
		else
			add_env_exp2(export, env, arg->str, equal);
		free(var);
		arg = arg->next;
	}
}

void	add_to_export_or_print(t_env **env, t_env **export, t_args *args)
{
	t_args		*arg;

	if (!args->next || (args->next && args->next->str[0] == '#'))
		print_export(*export);
	else
	{
		arg = args->next;
		add_env_exp3(env, export, arg);
	}
}
