/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:01:09 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/08 18:01:53 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int char_in_string(char *str, char *ref)
// {
// 	int		i;
// 	int		j;

// 	i = 0;
// 	while (str[i])
// 	{
// 		j = 0;
// 		while (ref[j])
// 		{
// 			if (str[i] == ref[j])
// 				return (j);
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (-1);
// }

int char_in_string(char c, char *ref)
{
	int		i;
	int		j;

	i = 0;
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
		if (char_in_string(str[i], "|<>()*") != -1)
			count++;
		i++;
	}
	return (count);
}

char	*word(char *str, char c)
{
	int		i;
	int		count;
	int		j;
	char	*wostr;

	i = 0;
	count = 0;
	j = 0;
	while (str[i] && str[i] != c)
	{
		count++;
		i++;
	}
	i = 0;
	wostr = malloc (sizeof(char ) * count + 1);
	if (!wostr)
		return (NULL);
	while (str[i] && str[i] != c)
		wostr[j++] = str[i++];
	wostr[j] = '\0';
	return (wostr);
}

int	cheack_sp_char(char *str)
{
	int	i;
	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (char_in_string(str[i], "|<>()*") == -1)
		return (1);
	else
		return (0);
}

int	len_first_split(char *str)
{
	int	len;
	len = count_split(str);
	if (cheack_sp_char(str) == 1)
		return (len * 2 + 1);
	else
		return (len * 2);
}

char	**my_split(char *str)
{
	char	**split;
	int		i;
	int		count;
	int		j;
	int		len;
	int		r;
	int		iw;

	i = 0;
	j = 0;
	r = 0;
	iw = 0;
	count	= 0;
	len = len_first_split(str);
	split = malloc(sizeof(char *) * len + 1);
	if (!split)
		return (NULL);
	while (str[i])
	{
		// if (char_in_string(str[i], "|<>()*") != -1)
		// {
		// 	// split[j++] = word(str, str[i]);
		// 	// split[j++] = word(&str[i], str[i]);
		// 	// printf("%s\n", split[j]);
		// }
		if (char_in_string(str[i], "|<>()*") != -1)
		{
			split[j] = malloc(sizeof(char) * count + 1);
			while (str[r] && str[r] != ' ' && char_in_string(str[r], "|<>()*") == -1)
				split[j][iw++] = str[r++];
			split[j][iw] = '\0';
			printf("%s\n", split[j]);
			j++;
			// r++;
			count = 0;
		}
		count++;
		i++;
	}
	return (split);
}



int main(int argc, char **argv)
{
	(void)argc;
	printf("%d\n", len_first_split(argv[1]));
	// printf("%d\n", count_split("echo l > m > n | t"));  //==> len + 1 + len = exact ===> add +1 if the special char not in the beginning the command
	// printf("%s\n", word("echo l > m > n | t", '>'));
	char **split;
	split = my_split(argv[1]);
	// int i = 0;
	// while (split[i])
	// {
	// 	printf("%s\n", split[i]);
	// 	i++;
	// }
	return (0);
}

// "\22"
// echo "hello"
// >
// r
// >
// rr
// >
// rr