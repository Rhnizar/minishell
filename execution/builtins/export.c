/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 18:34:13 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/06/02 21:32:50 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

int check_ident(char c)
{
	char ref[] = "=$+*[]/&?~,";
	int	i;

	i = 0;
	while (ref[i])
	{
		if (ref[i] == c)
			return(1);
		i++;
	}
	return (0);
}

void	identifier(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (check_ident(str[i]) == 1)
		printf("bash: export: `%s': not a valid identifier\n", str);
}

void	add_env_exp3(t_env *env, t_env *export, t_args *arg)
{
	size_t		equal;
	char		*var;

	equal = 0;
	while (arg)
	{
		identifier(arg->str);
		equal = find_equale(arg->str);
		var = ft_substr(arg->str, 0, equal);
		if (search_var(export, var) == 1)
		{
			if (ft_strchr(arg->str, '=') != NULL)
				edit_value(env, export, arg->str);
			else
				return ;
		}
		else if (equal == ft_strlen(arg->str))
			add_to_env(&export, ft_strdup(arg->str), NULL);
		else
			add_env_exp2(export, env, arg->str, equal);
		arg = arg->next;
	}
}

void	add_to_export_or_print(t_env *env, t_env *export, t_args *args)
{
	t_args		*arg;

	if (!args->next)
		print_export(export);
	else
	{
		arg = args->next;
		add_env_exp3(env, export, arg);
	}
}
