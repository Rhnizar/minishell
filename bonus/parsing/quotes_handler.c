/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:13:06 by kchaouki          #+#    #+#             */
/*   Updated: 2023/05/22 22:26:44 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

static char	*dollar_handler(char *arg, int *i)
{
	char	*output;
	int		two_q;
	int		quote;
	int		j;

	j = ((output = NULL), (two_q = 0), 0);
	quote = is_quote(arg[j]);
	if (is_quote(arg[j + 1]) > 0)
	{
		two_q = ((j++), 1);
		output = join_to_str(output, arg[j++]);
	}
	else
		output = join_to_str(output, arg[j++]);
	while (arg[j] && is_quote(arg[j]) != quote)
		output = join_to_str(output, arg[j++]);
	if (arg[j] == '\0' || quote != is_quote(arg[j]))
		return (free(output), NULL);
	if (two_q == 0)
		output = join_to_str(output, arg[j++]);
	else
		j++;
	return ((*i) += j, output);
}

static char	*check_dollar(char *old_out, char *str, int *i, int *quote)
{
	char	*dollar_output;
	char	*output;
	int		j;

	j = 0;
	output = NULL;
	dollar_output = dollar_handler(&str[j], &j);
	if (!dollar_output)
		return (NULL);
	output = ft_join_strings(old_out, dollar_output);
	free(dollar_output);
	(*quote) = is_quote(str[j]);
	if (*quote > 0)
		j++;
	else
		output = join_to_str(output, str[j]);
	(*i) += j;
	return (output);
}

char	*quotes_handler(char *token)
{
	char	*output;
	int		quote;
	int		i;

	output = ((i = -1), (quote = 0), ft_strdup(""));
	while (token[++i])
	{
		while (token[i] && is_quote(token[i]) == 0)
			output = join_to_str(output, token[i++]);
		quote = is_quote(token[i]);
		if (token[i + 1] == '$' || (is_quote(token[i + 1]) > 0 && \
		is_quote(token[i + 1]) != is_quote(token[i]) && token[i + 2] == '$'))
			output = check_dollar(output, &token[i], &i, &quote);
		else if (token[i + 1] == '\0' && quote > 0)
			return (free(output), NULL);
		else if (token[i + 1] != '\0')
			i++;
		if (!output)
			return (NULL);
		while (token[i] && quote != is_quote(token[i]))
			output = join_to_str(output, token[i++]);
		if (token[i] == '\0' && quote != is_quote(token[i]))
			return (free (output), NULL);
	}
	return (output);
}
