/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 12:30:39 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/15 12:52:07 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_split_quote(char *str, int r)
{
	int i;
	int	count;
	int	cq;
	char	ref[] = "\"'";

	i = 0;
	count = 0;
	cq = count_quote(str, r);
	while (str[i])
	{
		if (char_in_string(str[i], ref) != -1)
		{
			count++;
			while (cq != 0)
			{
				if (str[i] == ref[r])
					cq--;
				i++;
			}
		}
		else
		{
			while(str[i] && str[i] != ref[r])
				i++;
			count++;
		}
	}
	return (count);
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
	split = fill_with_null(len_split_quote(str, r));
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
			while (str[i])
				split[j] = join_to_str(split[j], str[i++]);
		}
		else
			split[j] = join_to_str(split[j], str[i]);
		if (str[i])
			i++;
	}
	return (split);
}

t_tokens	*split_and_fill_list(char **split)
{
	t_tokens	*list;
	char		**sp2;
	char		**sp_quote;
	int			i;
	int			r;
	int			j;
	int			s;

	i = 0;
	list = NULL;
	while (split[i])
	{
		r = check_quote(split[i]);
		if (r != -1)
		{
			sp_quote = split_quote(split[i], r);
			s = 0;
			while (sp_quote[s])
				create_tokens(&list, sp_quote[s++], 0);
		}
		else
		{
			sp2 = ft_split(split[i], ' ');
			j = 0;
			while (sp2[j])
			{
				create_tokens(&list, ft_strdup(sp2[j]), 0);
				j++;
			}
			free_double_ptr(sp2);
		}
		i++;
	}
	return(list);
}

// int main(int argc, char **argv)
// {
// 	char **split;
// 	t_tokens *token;
// 	int	i;

// 	i = 0;
// 	token = NULL;
// 	if (argc == 2)
// 	{
// 		split = my_split(argv[1]);
// 		token = split_and_fill_list(split);
// 		while(token)
// 		{
// 			printf("%s\n", token->str);
// 			token = token->next;
// 		}
// 	}
// 	return (0);
// }

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


// ./minishell "'test'\"test\""


// check the quote   howa lowl 
