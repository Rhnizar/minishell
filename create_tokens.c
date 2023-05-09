/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:47:30 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/09 17:03:44 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_tokens(t_tokens **lst, char *str, int type)
{
	t_tokens	*new;
	t_tokens	*tmp;

	new = malloc(sizeof(t_tokens));
	if (!new)
		return ;
	new->str = str;
	new->type = type;
	new->next = NULL;
	new->prev = NULL;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while(tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}