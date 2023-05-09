/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_my_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:52:41 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/09 14:55:45 by rrhnizar         ###   ########.fr       */
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

// char	**my_split(char *str)
// {
// 	char	**split;
// 	int		i;
// 	int		count;
// 	int		j;
// 	int		len;
// 	int		r;
// 	int		iw;

// 	i = 0;
// 	j = 0;
// 	r = 0;
// 	iw = 0;
// 	count	= 0;
// 	len = len_first_split(str);
// 	split = malloc(sizeof(char *) * len + 1);
// 	if (!split)
// 		return (NULL);
// 	int len2 = ft_strlen(str) + 1;
// 	while (len2 != 0)
// 	{
// 		// if (char_in_string(str[i], "|<>()*") != -1)
// 		// {
// 		// 	// split[j++] = word(str, str[i]);
// 		// 	// split[j++] = word(&str[i], str[i]);
// 		// 	// printf("%s\n", split[j]);
// 		// }
// 		while (str[i] == ' ')
// 			i++;
// 		// printf("pp %c\n", str[i]);
// 		if (char_in_string(str[i], "|<>()*") != -1 || str[i] == ' ' || str[i] == '\0')
// 		{
// 			split[j] = malloc(sizeof(char) * count + 1);
// 			while (str[r] && str[r] != ' ' && char_in_string(str[r], "|<>()*") == -1)
// 				split[j][iw++] = str[r++];
// 			split[j][iw] = '\0';
// 			printf("%s\n", split[j]);
// 			j++;
// 			// r++;
// 			count = 0;
// 		}
// 		count++;
// 		len2--;
// 		i++;
// 	}
// 	return (split);
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

char	*diri_khdmtk(char *str, int *i)
{
	// (void)str;
	// printf("1 ==> %d\n", *i);
	// *i += 5;
	int		count;
	int		i_tmp;
	int		j;
	char	*word;
	
	count = 1;
	i_tmp = *i;
	j = 0;
	// *i++;
	while (str[*i] && char_in_string(str[*i], "|<>()*") == -1)
		count++;
	if (count == 0)
		return (ft_strdup("\x07"));
	word = malloc(sizeof(char) * count + 1);
	while(i_tmp != *i)
		word[j++] = str[i_tmp++];
	word[j] = '\0';
	return (word);
		
}
char	**my_split(char *str)
{
	char	**split;
	int		i;
	int		len;
	int		j;

	i = 0;
	j = 0;
	len = len_first_split(str);
	split = malloc(sizeof(char *) * len + 1);
	if (!split)
		return (NULL);
	while (str[i])
	{
		if (char_in_string(str[i], "|<>()*") != -1)
		{
			if (i != 0)
				j++;
			split[j] = join_to_str(split[j], str[i]);
			j++;
			if (char_in_string(str[i], "|<>()*") != -1 && char_in_string(str[i + 1], "|<>()*") != -1)
			{
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

int main(void)
{
	char **sp = my_split("<echo|>Hello");
	int	i = 0;
	while (sp[i])
	{
		printf("%s\n", sp[i]);
		i++;
	}

	// printf("hey \x07");
	
	return (0);
}

// int main(int argc, char **argv)
// {
// 	(void)argc;
// 	printf("%d\n", len_first_split(argv[1]));
// 	// printf("%d\n", count_split("echo l > m > n | t"));  //==> len + 1 + len = exact ===> add +1 if the special char not in the beginning the command
// 	// printf("%s\n", word("echo l > m > n | t", '>'));
// 	char **split;
// 	split = my_split(argv[1]);
// 	// int i = 0;
// 	// while (split[i])
// 	// {
// 	// 	printf("%s\n", split[i]);
// 	// 	i++;
// 	// }
// 	return (0);
// }

// "\22"
// echo "hello"
// >
// r
// >
// rr
// >
// rr