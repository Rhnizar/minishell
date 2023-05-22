/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_separators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 19:29:32 by kchaouki          #+#    #+#             */
/*   Updated: 2023/05/22 19:51:54 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	check_redirections(t_syntax_check check)
{
	if (check.sp_id < 4)
	{
		if (!check.token->next)
		{
			here_doc_befor_error(check.all_tokens, check.index);
			return (syntx_error("newline"), 1);
		}
		check.sp_id = is_separator(check.token->next->str, check.sep);
		if (check.sp_id != -1)
		{
			syntx_error(check.sep[check.sp_id]);
			here_doc_befor_error(check.all_tokens, check.index);
			return (1);
		}
	}
	return (0);
}

static int	check_operators(t_syntax_check check)
{
	if (check.sp_id > 3 && check.sp_id < 7)
	{
		if (!check.token->prev)
			return (syntx_error(check.sep[check.sp_id]), 1);
		if (!check.token->next)
		{
			here_doc_befor_error(check.all_tokens, check.index);
			return (syntx_error("newline"), 1);
		}
		check.sp_id = is_separator(check.token->next->str, check.sep);
		if (check.sp_id != -1 && check.sp_id > 3 && \
		check.sp_id != 8 && check.sp_id != 7)
		{
			syntx_error(check.sep[check.sp_id]);
			here_doc_befor_error(check.all_tokens, check.index);
			return (1);
		}
	}
	return (0);
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
		if (check.sp_id == -1)
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
