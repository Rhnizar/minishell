/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_with_my_char.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:56:34 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/09 09:41:06 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*fill_arr_char(void)
// {
// 	char *arr;

// 	arr = malloc(sizeof(char) * 7);
// 	if (!arr)
// 		return (NULL);
// 	arr = "|<>()*";
// 	return (arr);
// }

int char_in_string(char *str, char *ref)
{
	int		i;
	int		j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (ref[j])
		{
			if (str[i] == ref[j])
				return (j);
			j++;
		}
		i++;
	}
	return (-1);
}

char	*cheack_str(int token)
{
	if (token == 0)
		return (ft_strdup("|"));
	else if (token == 1)
		return (ft_strdup("<"));
	else if (token == 2)
		return (ft_strdup(">"));
	else if (token == 3)
		return (ft_strdup("("));
	else if (token == 4)
		return (ft_strdup(")"));
	else if (token == 5)
		return (ft_strdup("*"));
	else
		return ("none");
}

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
void	split_with_char(char *str, t_tokens **token)
{
	char	ref[7] = "|<>()*";
	int		re;
	char	**sp;
	int		i;

	re = char_in_string(str, ref);
	i = 0;
	if (re != -1)
	{
		sp = ft_split(str, ref[re]);
		create_list(token, cheack_str(re), re);
		while (sp[i])
		{
			// if (char_in_string(sp[i], ref) == -1 )
				create_list(token, sp[i++], -55);
		}
	}
	else
		create_list(token, str, 0);
}

void	create_list(t_tokens **tokens, char *str, int type)
{
	t_tokens	*new;
	t_tokens	*tmp;

	new = malloc(sizeof(t_tokens));
	if (!new)
		return;
	new->str = str;
	new->type = type;
	new->next = NULL;
	new->prev = NULL;
	if (!*tokens)
	{
		*tokens = new;
		return ;
	}
	tmp = *tokens;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}



{["echo", "hello;"] , ">", "rrr", ">", "r", ">", ">>", "rr", "|", ["ls", "-la"] , "&&", ["cd", "/home"]}

// echo hello > rrr >r>rr|ls -la && cd /home

while (sp1[i])
{
	j = 0;
	sp2 = ft_split(sp1[i]);
	while (sp2[j])
	{
		add_to_list(sp2[j]);
		j++;
	}
	ft_free_split(sp2);
	i++;
}

echo
"test"
>
td;ls