/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utilis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:58:33 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/08 11:40:09 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// void	print_list(t_cmdshell *lst)
// {
// 	printf("\n--------------------------------------------\n");
// 	printf("\n CMD ==> %s\n", lst->cmd);
// 	printf("\n OPT ==> %s\n", lst->opt);
// 	printf("\n ARG ==> %s\n", lst->arg);
// 	printf("\n--------------------------------------------\n");
// }


static char	*join_to_str(char *str, char c)
{
	char	*output;
	int		i;

	if (!str)
		output = malloc(2);
	else
		output = malloc(ft_strlen(str) + 2);
	if (!output)
		return (NULL);
	i = 0;
	while (str && str[i])
	{
		output[i] = str[i];
		i++;
	}
	output[i++] = c;
	output[i] = '\0';
	free (str);
	return (output);
}