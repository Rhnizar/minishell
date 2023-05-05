/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_idea.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:37:10 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/05 15:51:05 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	char	**split_space;
	split_space = ft_split("echo hello", ' ');
	int i;
	i = 0;
	while(split_space[i])
		printf("%s\n", split_space[i++]);
	return (0);
}