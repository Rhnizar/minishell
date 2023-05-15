/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:39:59 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/13 19:28:27 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**fill_with_null(int len)
{
	char	**split;
	int		i;

	split = malloc(sizeof(char *) * (len + 1));
	if (!split)
		return (NULL);
	i = 0;
	while (i < len + 1)
	{
		split[i] = NULL;
		i++;
	}
	return (split);
}

char	*join_to_str(char *str, char c)
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

void	free_double_ptr(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free (str[i++]);
	free(str);
}