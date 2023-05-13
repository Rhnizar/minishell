/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   what_do_you_represent_string.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 07:58:07 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/11 11:53:07 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_str(char *str, char *ref)
{
	int	i;
	int	r;

	i = 0;
	while (str[i])
	{
		r = char_in_string(str[i], ref);
		if (r != -1)
			return (r);
		i++;
	}
	return (-1);
}

int		check_cmd3(char *str1, char *str2, char *str3, char *ref)
{
	int	r1;
	int	r2;

	r1 = check_str(str1, ref);
	if (r1 != -1)
	{
		if (ft_strncmp(str2, "\x07", 4) == 0)
		{
			r2 = check_str(str3, ref);
			if (r2 != -1 && r1 == r2)
				printf("khasna nsaybo node\n");
		}
	}
	return (0);
}

// int		check_cmd(t_tokens *token, char *ref)
// {
// 	// if (token && token->next && token->next->next)
// 	if (token->prev && token->next)
// 	{
// 		if (check_str(token->str, ref) != -1)
// 		{
// 			// if (ft_strncmp(token->next->str, "\x07", 4) == 0)
// 			// {
// 			// 	check_str(token->next->next->str, ref) != -1 &&)
// 			// }
// 		}
// 	}
// 	else if (token->next)
// 	{
		
// 	}
// 	else
		
// }

void	what_is_the_str(t_tokens *token)
{
	t_tokens	*tmp;
	// char		format[] = "|<>()*&";

	tmp = token;
	while (tmp)
	{
		// check_cmd(tmp, format);
		// if (tmp && tmp->next && tmp->next->next)
		// 	check_cmd3(tmp->str, tmp->next->str, tmp->next->next->str, format);
		// else if (tmp && tmp->next)
		// 	check_cmd2(tmp->str, tmp->next->str, format);
		// else
		// 	check_cmd1(tmp->str, format);
		tmp = tmp->next;
	}
	
}
int main(int argc, char **argv)
{
	// char		**sp;
	// t_tokens	*token;
	// // t_tokens	*tmp;

	// if (argc == 2)
	// {
	// 	sp = my_split(argv[1]);
	// 	token = split_and_fill_list(sp);
	// 	free_double_ptr(sp);
	// 	// tmp = token;
	// 	// while (tmp)
	// 	// {
	// 	// 	printf("%s\n", tmp->str);
	// 	// 	tmp = tmp->next;
	// 	// }
	// 	what_is_the_str(token);
	// 	// free_tokens(token);
	// }

	(void)argv;
	(void)argc;
	check_syntax("hello", "hjfhgh");
	return (0);
}
