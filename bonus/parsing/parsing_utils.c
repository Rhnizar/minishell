/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 23:52:06 by kchaouki          #+#    #+#             */
/*   Updated: 2023/05/22 23:56:14 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

static int	arg_len(char *s)
{
	int	count;

	count = 0;
	while (s && s[count])
		count++;
	return (count);
}

char	*join_with_space(char *old, char *arg)
{
	char	*output;
	int		i;
	int		j;

	output = malloc(arg_len(old) + arg_len(arg) + 2);
	if (!output)
		return (NULL);
	i = 0;
	j = 0;
	while (old && old[j])
		output[i++] = old[j++];
	if (old)
		output[i++] = ' ';
	j = 0;
	while (arg && arg[j])
		output[i++] = arg[j++];
	output[i] = '\0';
	if (old)
		free(old);
	return (output);
}

int	is_quote(char c)
{
	if (c == '\'')
		return (1);
	else if (c == '\"')
		return (2);
	return (0);
}

char	*ft_join_strings(char *s1, char *s2)
{
	char	*output;
	char	*p_s1;
	int		i;

	p_s1 = s1;
	output = malloc(arg_len(s1) + arg_len(s2) + 1);
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
