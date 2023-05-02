/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:41:35 by kchaouki          #+#    #+#             */
/*   Updated: 2022/10/11 07:38:28 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*new;

	if (!lst)
		return ;
	while (*lst)
	{
		new = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = new;
	}
}
