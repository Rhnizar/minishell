/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:01:09 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/10 16:56:55 by rrhnizar         ###   ########.fr       */
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

int	check_syntax(char *str)
{
	int	i;

	i = 0;
	int	r;
	int	r_tmp;
	while (str[i])
	{
		r = char_in_string(str[i], "|<>()*&");
		r_tmp = r;
		while (r != -1)
		{
			i++;
			r = char_in_string(str[i], "|<>()*&");
		}
		i++;
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

t_tokens	*split_and_fill_list(char **split)
{
	t_tokens	*list;
	char		**sp2;
	int			i;
	int			j;

	i = 0;
	list = NULL;
	while (split[i])
	{
		sp2 = ft_split(split[i], ' ');
		j = 0;
		while (sp2[j])
		{
			create_tokens(&list, ft_strdup(sp2[j]), 0);
			j++;
		}
		free_double_ptr(sp2);
		i++;
	}
	return(list);
}

void	free_tokens(t_tokens *tokens)
{
	t_tokens	*tmp;
	t_tokens	*tmp2;

	tmp = tokens;
	while (tmp)
	{
		tmp2 = tmp->next;
		free (tmp->str);
		free (tmp);
		tmp = tmp2;
	}
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
