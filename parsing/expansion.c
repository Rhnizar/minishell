/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:13:06 by kchaouki          #+#    #+#             */
/*   Updated: 2023/05/08 11:07:07 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_quote(char c)
{
	if (c == '\'')
		return (1);
	else if (c == '\"')
		return (2);
	return (0);
}

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

// char	*dollar_handler(char *token)
// {
	
// }

char	*quotes_handler(char *token)
{
	char	*output;
	int		quote;
	int		is_dolar;
	int		i;

	i = -1;
	quote = 0;
	output = NULL;
	is_dolar = 0;
	while (token[++i])
	{
		// printf("####%s\n", &str[i]);
		while (token[i] && is_quote(token[i]) == 0)
			output = join_to_str(output, token[i++]);
		quote = is_quote(token[i]);
		// output = ft_strjoin(output, handle_dollar(&token[i]));
		i++;
		// if (str[i])
		// {
		// 	if (quote == 2 && str[i + 1] == '$')
		// 	{
		// 		is_dolar = 1;
		// 		output = join_to_str(output, '\"');
		// 	}
		// 	i++;
		// }
		while (token[i] && quote != is_quote(token[i]))
			output = join_to_str(output, token[i++]);
		// if (quote == 2 && str[i + 1] == '$')
		// {
		// 	is_dolar = 1;
		// 	output = join_to_str(output, '\"');
		// 	i++;
		// 	while (str[i] && quote != is_quote(str[i]))
		// 		output = join_to_str(output, str[i++]);
		// }
		// if (is_dolar == 1) 
		// {
		// 	output = join_to_str(output, '\"');
		// 	is_dolar = 0;
		// 	quote = 0;
		// }
		if (token[i] == '\0' && quote != is_quote(token[i]))
			return (free (output), NULL);
	}
	return (output);
}

