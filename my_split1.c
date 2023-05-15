/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_split1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:01:09 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/11 08:28:48 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check2(char *str, char **split, int *i, int *j)
{
	while (char_in_string(str[*i], "|<>()*&") != -1 && \
		char_in_string(str[*i + 1], "|<>()*&") != -1)
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
	while (str[i])
	{
		if (char_in_string(str[i], "|<>()*&") != -1)
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

// int	main(int ac, char **av)
// {
// 	char	**sp;
// 	t_tokens *lst;
// 	t_tokens *tmp;

// 	(void) ac;
// 	if (ac == 2)
// 	{
// 		sp = my_split(av[1]);
// 		lst = split_and_fill_list(sp);
// 		// free_double_ptr(sp);
// 		tmp = lst;
// 		while (tmp)
// 		{
// 			printf("%s\n", tmp->str);
// 			// if (ft_strncmp(tmp->str, "\x07", 4) == 0)
// 			// {
// 			// 	printf("me\n");
// 			// 	exit(1);
// 			// }
			
// 			tmp = tmp->next;
// 		}
// 		// free_tokens(lst);
// 	}
// 	return (0);
// }
