/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:07:41 by kchaouki          #+#    #+#             */
/*   Updated: 2023/05/15 10:19:45 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_arg_len(char *s)
{
	size_t	count;

	if (!s)
		return (0);
	count = 0;
	while (s[count])
		count++;
	return (count);
}

char	*ft_join_strings(char *s1, char *s2)
{
	char	*output;
	char	*p_s1;
	char	*p_s2;
	int		i;

	p_s2 = s2;
	while (*p_s2 == ' ')
		p_s2++;
	if (*p_s2 == '\0')
		return (NULL);
	p_s1 = s1;
	output = malloc(ft_arg_len(s1) + ft_arg_len(s2) + 1);
	if (!output)
		return (NULL);
	i = 0;
	while (s1 && *s1)
		output[i++] = *s1++;
	while (s2 && *s2)
		output[i++] = *s2++;
	output[i] = '\0';
	if (p_s1)
		free(p_s1);
	return (output);
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
