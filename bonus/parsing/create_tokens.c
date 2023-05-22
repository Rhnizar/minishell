/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:47:30 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/22 22:26:11 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

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

void	free_tokens(t_tokens *tokens)
{
	t_tokens	*tmp;
	t_tokens	*tmp2;

	tmp = tokens;
	while (tmp)
	{
		tmp2 = tmp->next;
		free (tmp->str);
		free (tmp);
		tmp = tmp2;
	}
}

int	count_tokens(t_tokens *tokens)
{
	t_tokens	*tmp;
	int			count;

	tmp = tokens;
	count = 0;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}
