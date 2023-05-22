/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:10:32 by kchaouki          #+#    #+#             */
/*   Updated: 2023/05/22 22:26:34 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

//   echo with option -n
// ◦ cd with only a relative or absolute path
// ◦ pwd with no options
// ◦ export with no options
// ◦ unset with no options
// ◦ env with no options or arguments
// ◦ exit with no options

static int	double_check(char *token, char *builtin)
{
	char	*exact_token;

	exact_token = ft_strnstr(token, builtin, ft_strlen(token));
	if (!exact_token || ft_strncmp(exact_token, \
	builtin, ft_strlen(exact_token)) != 0)
		return (0);
	return (1);
}

int	is_builtin(char *token)
{
	if (double_check(token, "echo"))
		return (1);
	else if (double_check(token, "cd"))
		return (1);
	else if (double_check(token, "pwd"))
		return (1);
	else if (double_check(token, "env"))
		return (1);
	else if (double_check(token, "export"))
		return (1);
	else if (double_check(token, "unset"))
		return (1);
	else if (double_check(token, "exit"))
		return (1);
	return (0);
}

// int main (int ac, char **av)
// {
// 	// ft_strdup("echoo")
// 	// printf("%s\n", ft_strnstr(ft_strdup("echd"), ft_strdup("echoo"), ft_strlen("echo")));
// 	printf("%d\n", is_builtin(av[1]));
// 	// printf("%s\n", token_tolower(ft_strdup("TeSt")));
// 	return (0);
// }
