/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 08:26:39 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/12 12:26:31 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	check_syntax(char *str, char *ref)
{
// 	int	i;

// 	i = 0;
// 	int	r;
// 	int	r_tmp;
// 	while (str[i])
// 	{
// 		r = char_in_string(str[i], ref);
// 		if (r != WLDC)
// 		{
// 			r_tmp = r;
// 			r = char_in_string(str[i + 1], ref);
// 			if (r_tmp == r && (r == PIPE || r == OR))
// 			{
// 				if (BONUS == 100)
// 					printf("bash: syntax error near unexpected token `%c'", ref[r]);
// 			}
// 		}
// 		i++;
// 	}
	
	(void)str;
	if (BONUS == 100)
		printf("this is mandatory\n");
	else
		printf("this is bonus\n");
	return (0);
	// (void)str;
	(void)ref;
	// printf("rr\n");
	return (0);
}
