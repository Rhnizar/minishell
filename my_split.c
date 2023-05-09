/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:01:09 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/09 16:36:26 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	check2(char *str, char **split, int *i, int *j)
{
	while (char_in_string(str[*i], "&|<>()*") != -1 && \
		char_in_string(str[*i + 1], "&|<>()*") != -1)
	{
		split[*j] = ft_strdup("\x07");
		(*j)++;
		split[*j] = join_to_str(split[*j], str[*i + 1]);
		(*j)++;
		(*i)++;
	}
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
	printf("%d\n", len_first_split(str));
	while (str[i])
	{
		if (char_in_string(str[i], "&|<>()*") != -1)
		{
			if (i != 0)
				j++;
			split[j] = join_to_str(split[j], str[i]);
			j++;
			check2(str, split, &i, &j);
		}
		else
			split[j] = join_to_str(split[j], str[i]);
		i++;
	}
	return (split);
}

int	main(int ac, char **av)
{
	char	**sp;
	int		i;

	(void) ac;
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
