/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 08:22:53 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/06/07 14:43:18 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	cd(t_global *global, t_args	*args)
{
	char	cu_wo_di[PATH_MAX];
	char	*dir;

	if (args && args->next)
	{
		if (getcwd(cu_wo_di, sizeof(cu_wo_di)) != NULL)
		{
			if (chdir(args->next->str) == -1)
			{
				dir = ft_strjoin(ft_strdup(cu_wo_di), "/");
				dir = ft_strjoin(dir, args->next->str);
				if (chdir(dir) == -1)
				{
					printf("bash: %s: %s\n", args->next->str, strerror(errno));
					global->exit_status = 1;
				}
			}
		}
		else
		{
			perror("bash");
			global->exit_status = 1;
		}
	}
}
