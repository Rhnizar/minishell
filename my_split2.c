/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 12:30:39 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/13 18:01:18 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_quote(char *str)
{
	int		i;
	int		r;

	i = 0;
	while (str[i])
	{
		r = char_in_string(str[i], "\"'");
		if (r != -1)
			return (r);
		i++;
	}
	return (-1);
}

int count_quote(char *str, int r)
{
	char	ref[] = "\"'";
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ref[r])
			count++;
		i++;
	}
	return (count);
}

char	**fill_with_null2(int len)
{
	char	**split;
	int		i;

	len = 5;
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

char **split_quote(char *str, int r)
{
	int		i;
	int		j;
	int		cq;
	char	**split;
	char	ref[2] = "\"'";

	i = 0;
	j = 0;
	cq = count_quote(str, r);

	split = fill_with_null2(5);
	while (str[i])
	{
		if (str[i] == ref[r])
		{
			if (i != 0)
				j++;
			while(str[i] && cq != 0)
			{
				split[j] = join_to_str(split[j], str[i]);
				if (str[i] == ref[r])
					cq--;
				i++;
			}
			j++;
			if (str[i])
			{
				while (str[i])
				{
					printf("here\n");
					split[j] = join_to_str(split[j], str[i++]);
				}
			}		
		}
		else
		{
			printf("===>%c\n", str[i]);
			// while (str[i])
				split[j] = join_to_str(split[j], str[i]);
		}
		if (str[i])
			i++;
	}
	split[j] = NULL;
	return (split);
}

// t_tokens	*split_and_fill_list(char **split)
// {
// 	t_tokens	*list;
// 	char		**sp2;
// 	int			i;
// 	int			r;
// 	int			j;

// 	i = 0;
// 	list = NULL;
// 	while (split[i])
// 	{
// 		r = check_quote(split[i]);
// 		// printf("%d\n", check_quote(argv[1], r));
// 		if (r != -1)
// 		{
// 			split_quote(split[i], r);
// 		}
// 			// create_tokens(&list, ft_strdup(split[i]), 0);
// 		else
// 		{
// 			sp2 = ft_split(split[i], ' ');
// 			j = 0;
// 			while (sp2[j])
// 			{
// 				create_tokens(&list, ft_strdup(sp2[j]), 0);
// 				j++;
// 			}
// 			free_double_ptr(sp2);
// 		}
// 		i++;
// 	}
// 	return(list);
// }

int main(int argc, char **argv)
{
	char **split;
	// t_tokens *token;
	int	i;
	int	r;

	i = 0;
	// token = NULL;
	split = NULL;
	if (argc == 2)
	{
		r = check_quote(argv[1]);
		if (r != -1)
			split = split_quote(argv[1], r);
		while(split[i])
		{
			printf("%s\n", split[i]);
			i++;
		}
			// printf("%d\n", count_quote(argv[1], r));
		// split = my_split(argv[1]);
		// token = split_and_fill_list(split);
		// while(token)
		// {
		// 	printf("%s\n", token->str);
		// 	token = token->next;
		// }
	}
	return (0);
}

// void	free_tokens(t_tokens *tokens)
// {
// 	t_tokens	*tmp;
// 	t_tokens	*tmp2;

// 	tmp = tokens;
// 	while (tmp)
// 	{
// 		tmp2 = tmp->next;
// 		free (tmp->str);
// 		free (tmp);
// 		tmp = tmp2;
// 	}
// }