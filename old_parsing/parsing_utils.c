/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:07:41 by kchaouki          #+#    #+#             */
/*   Updated: 2023/05/17 13:26:02 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	arg_len(char *s)
{
	int	count;

	count = 0;
	while (s && s[count])
		count++;
	return (count);
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

int	skip_spaces(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	return (i);
}
