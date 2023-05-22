/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 08:56:35 by kchaouki          #+#    #+#             */
/*   Updated: 2023/05/22 22:25:43 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_bonus.h"

int	is_separator(char *token, char **sep)
{
	int	i;

	i = -1;
	while (sep[++i])
	{
		if (ft_strnstr(token, sep[i], ft_strlen(sep[i])))
			return (i);
	}
	return (-1);
}

void	syntx_error(char *arg)
{
	ft_putstr_fd(ESYNTX, 2);
	if (arg[0] == '\"' || arg[0] == '\"')
		ft_putchar_fd(*arg, 2);
	else
		ft_putstr_fd(arg, 2);
	ft_putstr_fd("\'\n", 2);
}

static int	check_quotes(char *token)
{
	char	*quote;
	int		i;

	i = -1;
	quote = NULL;
	while (token[++i])
	{
		while (token[i] && !ft_strchr("\"'", token[i]))
			i++;
		quote = ft_strchr("\"'", token[i]);
		if (!token[i + 1] && quote[0])
			return (syntx_error(&quote[0]), 1);
		else if (token[i + 1])
			i++;
		while (token[i] && quote[0] != token[i])
			i++;
		if (!token[i] && quote[0] != token[i])
			return (syntx_error(&quote[0]), 1);
	}
	return (0);
}

static t_syntax_check	fill_syntax_check(t_tokens *all_tokens, t_tokens *token)
{
	t_syntax_check	sntx_check;

	sntx_check.all_tokens = all_tokens;
	sntx_check.token = token;
	sntx_check.sep = ft_split(">> << > < || && | ( )", ' ');
	sntx_check.sp_id = 0;
	sntx_check.index = 0;
	sntx_check.index_par = 0;
	sntx_check.par = 0;
	return (sntx_check);
}

int	syntax_error_handler(t_tokens *tokens)
{
	t_syntax_check	check;
	t_tokens		*tmp;

	tmp = tokens;
	check = fill_syntax_check(tokens, tmp);
	if (!check.sep)
		print_error(NULL, NULL, 1);
	while (tmp)
	{
		if (check_quotes(tmp->str))
			return (here_doc_befor_error(tokens, check.index), \
			free_double_ptr(check.sep), 258);
		check.sp_id = is_separator(tmp->str, check.sep);
		check.token = tmp;
		if (check_separators(check, &check.par, &check.index_par))
			return (free_double_ptr(check.sep), 258);
		check.index++;
		tmp = tmp->next;
	}
	if (check.par > 0)
		return (here_doc_befor_error(check.all_tokens, check.index_par), \
		syntx_error("("), 258);
	return (free_double_ptr(check.sep), 0);
}

// |:
//     first token: syntax error near unexpected token `|'
//     after '|'  : syntax error near unexpected token `|'
//     after '('  : syntax error near unexpected token `|'
//     after '&&' : syntax error near unexpected token `|'
//     after '||' : syntax error near unexpected token `|'
//     after >/<  : syntax error near unexpected token `|'
//     last token : syntax error: unexpected end of file
// (:
//     after ')'  : syntax error near unexpected token `('
//     after word : syntax error near unexpected token `(' # bash would expect a fucntion
//     after >/<  : syntax error near unexpected token `|'
//     last token : syntax error: unexpected end of file
// ):
//     first token: syntax error near unexpected token `)'
//     after '|'  : syntax error near unexpected token `)'
//     after '('  : syntax error near unexpected token `)'
//     after '&&' : syntax error near unexpected token `)'
//     after '||' : syntax error near unexpected token `)'
//     after >/<  : syntax error near unexpected token `|'
// &&/||:
//     first token: syntax error near unexpected token `|'
//     after '|'  : syntax error near unexpected token `|'
//     after '('  : syntax error near unexpected token `|'
//     after '&&' : syntax error near unexpected token `|'
//     after '||' : syntax error near unexpected token `|'
//     after >/<  : syntax error near unexpected token `|'
//     last token : syntax error: unexpected end of file
// word:
//     after ')'  : syntax error near unexpected token `word'
// >/<:    
//     after >/<  : syntax error near unexpected token `|'
//     last token : syntax error: unexpected end of file