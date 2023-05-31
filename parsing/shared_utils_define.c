/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_utils_define.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:58:02 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/31 12:04:10 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fill_list_args(t_args **lst, char *str)
{
	t_args	*new;
	t_args	*tmp;

	new = malloc(sizeof(t_args));
	if (!new)
		return ;
	new->str = str;
	new->next = NULL;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	fill_list_redis(t_redis **lst, char *str, int type)
{
	t_redis	*new;
	t_redis	*tmp;

	new = malloc(sizeof(t_redis));
	if (!new)
		return ;
	new->str = str;
	new->type = type;
	new->next = NULL;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	check_node1(t_cmds **cmd, t_tokens *tmp, t_utils *utils)
{
	if (utils->red_id != -1)
	{
		if (tmp->next)
			fill_list_redis(&(*cmd)->redis, \
				ft_strdup(tmp->next->str), utils->red_id);
		utils->red_id = -1;
	}
	else
		fill_list_args(&(*cmd)->args, ft_strdup(tmp->str));
}

void	free_redis(t_redis *redis)
{
	t_redis	*tmp;
	t_redis	*tmp2;

	tmp = redis;
	while (tmp)
	{
		tmp2 = tmp->next;
		free (tmp->str);
		free (tmp);
		tmp = tmp2;
	}
}

void	free_args(t_args *args)
{
	t_args	*tmp;
	t_args	*tmp2;

	tmp = args;
	while (tmp)
	{
		tmp2 = tmp->next;
		free (tmp->str);
		free (tmp);
		tmp = tmp2;
	}
}
