/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 12:25:35 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/06/07 12:56:52 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	pwd(t_global *global)
{
	char	cu_wo_di[PATH_MAX];

	if (getcwd(cu_wo_di, sizeof(cu_wo_di)) != NULL)
		printf("%s\n", cu_wo_di);
	else
	{
		perror("bash");
		global->exit_status = 1;
	}
}
