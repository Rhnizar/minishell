/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_idea.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:37:10 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/09 09:10:26 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int main(void)
{
	char		**split_space;
	t_tokens	*token;

	token = NULL;
	split_space = ft_split("echo hello >hh >h>h>h>kk", ' ');
	int i;
	i = 0;
	while(split_space[i])
		split_with_char(split_space[i++], &token);
	while (token)
	{
		printf("%s\n", token->str);
		token = token->next;
	}
	// printf("---------------\n");
	// while (token)
	// {
	// 	printf("%s\n", token->str);
	// 	token = token->prev;
	// }
	return (0);
}