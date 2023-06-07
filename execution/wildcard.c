/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:24:48 by kchaouki          #+#    #+#             */
/*   Updated: 2023/06/07 12:28:05 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static t_tokens	*wildcard_tokenizer(char *token)
// {
// 	t_tokens	*tokens;
// 	char		**output;
// 	char		*to_split;
// 	int			i;

// 	to_split = ((i = 0), NULL);
// 	while (token[i])
// 	{
// 		if (token[i] == '*')
// 		{
// 			to_split = join_to_str(to_split, '\x07');
// 			to_split = join_to_str(to_split, token[i]);
// 			to_split = join_to_str(to_split, '\x07');
// 		}
// 		else
// 			to_split = join_to_str(to_split, token[i]);
// 		i++;
// 	}
// 	i = 0;
// 	tokens = NULL;
// 	output = ft_split(to_split, '\x07');
// 	while (output[i])
// 		create_tokens(&tokens, ft_strdup(output[i++]));
// 	return (free(to_split), free_double_ptr(output), tokens);
// }

// char	*find_match(char *to_handle, char *entity_name)
// {
// 	t_tokens	*tokens;

// 	tokens = wildcard_tokenizer(to_handle);
// }

t_tokens	*wildcard(char *arg)
{
	struct dirent	*entity;
	// t_tokens		*tokens;
	DIR 			*dir;
	// char			*ret;

	(void)	arg;
	dir = opendir(".");
	// tokens = NULL;
	if (dir == NULL)
		return (NULL);
	while (1)
	{
		entity = readdir(dir);
		if (entity == NULL)
			break ;
		// ret = find_match(arg, entity->d_name);
		// if (ret)
		// 	create_tokens(&tokens, ret);
		// printf("%s\n", entity->d_name);
	}
	closedir(dir);
	return (NULL);
	// return (tokens);
}

// int main()
// {
// 	wildcard();
// 	return (0);
// }