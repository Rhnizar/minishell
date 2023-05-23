/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   khdma_n9iya.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:14:44 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/09 13:17:37 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int char_in_string(char c, char *ref)
{
	int		j;

	j = 0;
	while (ref[j])
	{
		if (c == ref[j])
			return (j);
		j++;
	}
	return (-1);
}

int		count_split(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (char_in_string(str[i], "&|<>()*") != -1)
			count++;
		i++;
	}
	return (count);
}

int	cheack_sp_char(char *str)
{
	int	i;
	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (char_in_string(str[i], "&|<>()*") == -1)
		return (1);
	else
		return (0);
}

int	len_first_split(char *str)
{
	int	len;

	len = count_split(str);
	if (cheack_sp_char(str) == 0)
	{
		if (char_in_string(str[0], "&|<>()*") != -1)
			return (len * 2);
		else
			return (len * 2 + 1);
	}
	else
		return (len * 2 + 1);
}

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

char	**my_split(char *str)
{
	char	**split;
	int		i;
	int		j;

	split = fill_with_null(len_first_split(str));
	if (!split)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (char_in_string(str[i], "&|<>()*") != -1)
		{
			if (i != 0)
				j++;
			split[j] = join_to_str(split[j], str[i]);
			j++;
			if (char_in_string(str[i], "&|<>()*") != -1 && char_in_string(str[i + 1], "&|<>()*") != -1)
			{
				split[j++] = ft_strdup("\x07");
				split[j] = join_to_str(split[j], str[i + 1]);
				j++;
				i++;
			}
		}
		else
			split[j] = join_to_str(split[j], str[i]);
		i++;
	}
	return (split);
}

int main(int ac, char **av)
{
	(void) ac;
	char	**sp;
	int		i;

	if (ac == 2)
	{
		i = 0;
		sp = my_split(av[1]);
		while (sp[i])
		{
			printf("%s\n", sp[i]);
			i++;
		}
	}
	return (0);
}