/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:13:06 by kchaouki          #+#    #+#             */
/*   Updated: 2023/05/13 07:57:01 by kchaouki         ###   ########.fr       */
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

// char	*sp_char_handler(char *str)
// {
// 	char	**sp;
// 	if (BONUS == 0)
// 		sp = create_sp();
// }

char	*dollar_handler(char *arg, int *i)
{
	char	*output;
	int		quote;
	char	quote_char;
	int		j;
	int		two_q;

	j = 0;
	output = NULL;
	quote_char = arg[j];
	quote = is_quote(arg[j]);
	two_q = 0;
	if (is_quote(arg[j + 1]) > 0)
	{
		j++;
		two_q = 1;
		output = join_to_str(output, arg[j++]);
	}
	else
		output = join_to_str(output, arg[j++]);
	while (arg[j] && is_quote(arg[j]) != quote)
		output = join_to_str(output, arg[j++]);
	if (arg[j] == '\0' || quote != is_quote(arg[j]))
		return (print_syntx_error(&quote_char, 2), free(output), NULL);
	if (two_q == 0)
		output = join_to_str(output, arg[j++]);
	else
		j++;
	(*i) += j;
	return (output);
}

char	*quotes_handler(char *arg)
{
	char	*output;
	char	*dollar_output;
	int		quote;
	char	quote_char;
	int		i;

	i = -1;
	quote = 0;
	output = NULL;
	while (arg[++i])
	{
		while (arg[i] && is_quote(arg[i]) == 0)
			output = join_to_str(output, arg[i++]);
		quote = is_quote(arg[i]);
		quote_char = arg[i];
		if ((arg[i + 1] && arg[i + 1] == '$') || \
		(arg[i + 1] && is_quote(arg[i + 1]) > 0 && is_quote(arg[i + 1]) != is_quote(arg[i]) && arg[i + 2] == '$'))
		{
			dollar_output = dollar_handler(&arg[i], &i);
			if (!dollar_output)
				return (free(output), NULL);
			output = ft_join_strings(output, dollar_output);
			free(dollar_output);
			quote = is_quote(arg[i]);
			quote_char = arg[i];
			if (quote > 0)
				i++;
		}
		else if (arg[i + 1])
			i++;
		if (arg[i] == '\0' && quote != is_quote(arg[i]))
		{
			print_syntx_error(&quote_char, 2);
			return (free (output), NULL);
		}
		while (arg[i] && quote != is_quote(arg[i]))
			output = join_to_str(output, arg[i++]);
		if (arg[i] == '\0' && quote != is_quote(arg[i]))
		{
			print_syntx_error(&quote_char, 2);
			return (free (output), NULL);
		}
	}
	return (output);
}

// char	*lexer(char *arg)
// {
// 	char	*outfile;
// 	int		i;

// 	i = -1;
// 	while (arg[++i])
// 	{	
// 	}	
// 	return (outfile);	
// }

