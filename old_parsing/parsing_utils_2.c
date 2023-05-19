/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:24:40 by kchaouki          #+#    #+#             */
/*   Updated: 2023/05/17 14:21:03 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_quote(char c)
{
	if (c == '\'')
		return (1);
	else if (c == '\"')
		return (2);
	return (0);
}

char	**create_separator(void)
{
	if (BONUS == 0)
		return (ft_split(">> << > < |", ' '));
	return (ft_split(">> << > < || && | ( )", ' '));
}

void	syntx_error(char *arg)
{
	ft_putstr_fd(ESYNTX, 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("\'\n", 2);
}

char	*recognize_quote(int quote)
{
	if (quote == 1)
		return ("\'");
	return ("\"");
}

char	*find_separator(char **sep, char *str, int *sp)
{
	char	*output;
	int		j;

	j = 0;
	output = NULL;
	while (sep[j])
	{
		output = ft_strnstr(str, sep[j], ft_strlen(sep[j]));
		if (output != NULL)
			break ;
		j++;
	}
	if (*sp != -1)
		(*sp) = j;
	return (output);
}
