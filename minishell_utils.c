/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:39:59 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/06/01 14:57:08 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_global(t_global **global, char **env)
{
	*global = malloc(sizeof(t_global));
	if (!*global)
		exit (-1);
	(*global)->exit_status = 0;
	(*global)->env = create_env(env);
	(*global)->export = _export((*global)->env);
	return (0);
}