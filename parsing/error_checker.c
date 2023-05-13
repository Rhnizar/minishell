/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 09:36:17 by kchaouki          #+#    #+#             */
/*   Updated: 2023/05/13 12:06:56 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// char	*sp_char_handler(char *str)
// {
// 	char	**sp;
// 	if (BONUS == 0)
// 		sp = create_sp();
// }

static int	is_quote(char c)
{
	if (c == '\'')
		return (1);
	else if (c == '\"')
		return (2);
	return (0);
}

char	**create_sp(void)
{
	if (BONUS == 0)
		return (ft_split(">> << > < |", ' '));
	return (ft_split(">> << || && > < | * ( )", ' '));
}

// {">>", "<<", "||", "&&", ">", "<", "|", "*", "(", ")"}

//i need to chang the exit status inside the struct
// so i need to pass the struct
static void	syntx_error(char *arg)
{
	ft_putstr_fd(ESYNTX, 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("\'\n", 2);
}

static char	*recognize_quote(int quote)
{
	if (quote == 1)
		return ("\'");
	return ("\"");
}

int	snytx_error_checker(char *arg)
{
	char	**sep;
	int		quote;
	int		i;

	i = -1;
	sep = create_sp();
	// (void) arg;
	// while (sep[++i])
	// {
	// 	printf("%s\n", sep[i]);
	// }
	while (arg[++i])
	{
		while (arg[i] && is_quote(arg[i]) == 0)
		{
			//check sp char
			i++;
		}
		quote = is_quote(arg[i]);
		if (arg[i + 1] == '\0' && quote > 0)
			return (syntx_error(recognize_quote(quote)), free(arg), 258);
		else if (arg[i + 1] != '\0')
			i++;
		while (arg[i] && quote != is_quote(arg[i]))
			i++;
		if (arg[i] == '\0' && quote != is_quote(arg[i]))
			return (syntx_error(recognize_quote(quote)), free(arg), 258);
	}
	return (0);
}
