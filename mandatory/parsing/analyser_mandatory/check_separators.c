/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_separators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 19:29:32 by kchaouki          #+#    #+#             */
/*   Updated: 2023/05/22 20:15:57 by kchaouki         ###   ########.fr       */
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
		if (check.sp_id != -1 && check.sp_id > 3 && check.sp_id != 8 && check.sp_id != 7)
		{
			syntx_error(check.sep[check.sp_id]);
			here_doc_befor_error(check.all_tokens, check.index);
			return (1);
		}
	}
	return (0);
}

int	check_separators_mandatory(t_syntax_check check)
{
	if (check.sp_id != -1)
	{
		if (check_redirections(check))
			return (1);
		if (check_operators(check))
			return (1);
	}
	return (0);
}
