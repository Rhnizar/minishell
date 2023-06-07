/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 08:22:53 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/06/07 19:16:36 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	cd_no_arg(t_global *global, t_args *args, t_env *export)
{
	t_env	*tmp_exp;

	if (!args)
		return ;
	else
	{
		tmp_exp = export;
		while (tmp_exp)
		{
			if (ft_strcmp(tmp_exp->var, "HOME") == 0)
			{
				chdir(tmp_exp->value);
				return ;
			}
			tmp_exp = tmp_exp->next;
		}
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		global->exit_status = 1;
	}
}

static void	error_message(char *arg, char *message)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
}

void	check_dir(t_global *global, char *dir, char *cu_wo_di, char *str)
{
	if (chdir(str) == -1)
	{
		dir = ft_strjoin(ft_strdup(cu_wo_di), "/");
		dir = ft_strjoin(dir, str);
		if (chdir(dir) == -1)
		{
			error_message(str, strerror(errno));
			global->exit_status = 1;
		}
		free(dir);
	}
}

void	cd(t_global *global, t_args	*args, t_env *export)
{
	char	cu_wo_di[PATH_MAX];
	char	*dir;

	dir = NULL;
	if (args && args->next)
	{
		if (getcwd(cu_wo_di, sizeof(cu_wo_di)) != NULL)
			check_dir(global, dir, cu_wo_di, args->next->str);
		else
		{
			perror("minishell");
			global->exit_status = 1;
		}
	}
	else
		cd_no_arg(global, args, export);
}
