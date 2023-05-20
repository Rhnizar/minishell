/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_mandatory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:13:31 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/20 08:59:13 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	define_m(t_tokens token)
{
	t_tokens	tmp;
	
	while (tmp)
	{
		printf("%s\n", tmp->str);
		tmp = tmp->next;
	}
}

int main(void)
{
	printf("just test define mandaory\n");
	return (0);
}