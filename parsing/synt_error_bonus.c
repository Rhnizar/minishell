/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synt_error_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 12:24:33 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/23 20:41:02 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init_check(t_check	*check, char *read_line)
{
	check->split = ft_split(">> << || && > < | ( )", ' ');
	if (!check->split)
		return (-1);
	check->str = read_line;
	check->ot = NULL;
	check->dq = 0;
	check->sq = 0;
	check->sid = 0;
	return (0);
}

t_syntax_check	fill_syntax_check(t_tokens *all_tokens, t_tokens *token)
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


static int	check_open_par(t_syntax_check check, int *par, int *i_par)
{
	if (check.sp_id == 7)
	{
		if (*par == 0)
			(*i_par) = check.index;
		(*par)++;
		if (!check.token->next)
		{
			here_doc_befor_error(check.all_tokens, check.index);
			syntx_error("newline");
			return (1);
		}
		check.sp_id = is_separator(check.token->next->str, check.sep);
		if (check.sp_id > 3)
		{
			syntx_error(check.sep[check.sp_id]);
			here_doc_befor_error(check.all_tokens, check.index);
			return (1);
		}
	}
	return (0);
}

static int	check_parentheses(t_syntax_check check, int *par, int *i_par)
{
	if (check_open_par(check, par, i_par))
		return (1);
	if (check.sp_id == 8)
	{
		(*par)--;
		if (!check.token->prev)
			return (syntx_error(check.sep[check.sp_id]), 1);
		if (*par < 0)
		{
			here_doc_befor_error(check.all_tokens, check.index);
			syntx_error(")");
			return (1);
		}
		if (check.token->next)
			check.sp_id = is_separator(check.token->next->str, check.sep);
		if (check.sp_id == -1 || check.sp_id == 7)
		{
			here_doc_befor_error(check.all_tokens, check.index);
			syntx_error(check.token->next->str);
			return (1);
		}
	}
	return (0);
}

int	check_separators(t_syntax_check	check, int *par, int *i_par)
{
	if (check.sp_id != -1)
	{
		if (check_redirections(check))
			return (1);
		if (check_operators(check))
			return (1);
		if (check_parentheses(check, par, i_par))
			return (1);
	}
	else if (check.sp_id == -1 && check.token->next && \
	is_separator(check.token->next->str, check.sep) == 7)
	{
		here_doc_befor_error(check.all_tokens, check.index);
		syntx_error(check.token->next->str);
		return (1);
	}
	return (0);
}