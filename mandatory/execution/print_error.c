/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:19:54 by kchaouki          #+#    #+#             */
/*   Updated: 2023/05/04 12:12:12 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_error(char *msg, char *arg, int status)
{
	char	*error_msg;

	if (msg && !arg)
		ft_putstr_fd(msg, 2);
	else if (!msg && !arg)
	{
		error_msg = ft_strjoin("minishell: ", strerror(errno));
		ft_putstr_fd(error_msg, 2);
		ft_putchar_fd('\n', 2);
		free (error_msg);
	}
	else
	{
		arg = ft_strjoin("minishell: ", arg);
		error_msg = ft_strjoin(arg, msg);
		ft_putstr_fd(error_msg, 2);
		free (arg);
		free (error_msg);
	}
	if (status != -1)
		exit(status);
}
