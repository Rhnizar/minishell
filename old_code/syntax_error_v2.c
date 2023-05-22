/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_v2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 08:56:35 by kchaouki          #+#    #+#             */
/*   Updated: 2023/05/21 08:44:49 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

int	check_quotes(char *token)
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
			return (syntx_error(&quote[0]) , 1);
		else if (token[i + 1])
			i++;
		while (token[i] && quote[0] != token[i])
			i++;
		if (!token[i] && quote[0] != token[i])
			return (syntx_error(&quote[0]), 1);
	}
	return (0);
}

void	here_doc_befor_error(t_tokens *tokens, int index)
{
	t_tokens	*here_docs;
	t_tokens	*tmp;
	int			j;

	tmp = tokens;
	if (index == count_tokens(tokens))
		return ;
	here_docs = ((j = 0), NULL);
	while (tmp && j < index)
	{
		if (ft_strnstr(tmp->str, "<<", 2))
		{
			tmp = tmp->next;
			j++;
			create_tokens(&here_docs, ft_strdup(tmp->str), 0);
		}
		j++;
		tmp = tmp->next;
	}
	run_here_docs(here_docs);
}

// int	redirections_check(char **sep, t_tokens *all_tokens, t_tokens *token, int i)
// {
// 	int	old_sp_id;


// 	return (0);
// }

int	check_separators(char **sep, t_tokens *all_tokens, t_tokens *token, int i)
{
	int			sp_id;
	int			old_sp_id;

	sp_id = is_separator(token->str, sep);
	if (sp_id != -1)
	{
		// redirections_check(sep, all_tokens, token, i);
		if (sp_id < 4 || sp_id == 7)
		{
			if (!token->next)
			{
				here_doc_befor_error(all_tokens, i);
				return (syntx_error("newline"), 1);
			}
			old_sp_id = sp_id;
			if (token->next)
				sp_id = is_separator(token->next->str, sep);
			if (old_sp_id == 7)
			{
				if (token->prev && is_separator(token->prev->str, sep) == -1)
				{
					syntx_error(token->next->str);
					here_doc_befor_error(all_tokens, i);
					return (1);
				}
			}
			if (sp_id != -1 && (old_sp_id < 4 || (old_sp_id == 7 && sp_id > 3 && sp_id != 7)))
			{
				here_doc_befor_error(all_tokens, i);
				syntx_error(sep[sp_id]);
				return (1);
			}
		}
		else if (sp_id > 3 && sp_id != 7)
		{
			if (token->prev == NULL && sp_id > 3 && sp_id != 7)
				return(syntx_error(sep[sp_id]), 1);
			if (!token->next && sp_id != 8)
			{
				here_doc_befor_error(all_tokens, i);
				return (syntx_error("newline"), 1);
			}
			old_sp_id = sp_id;
			if (token->next)
				sp_id = is_separator(token->next->str, sep);
			// if (old_sp_id == 7 && sp_id == -1)
			// {
			// 	if (token->prev)
			// 		sp_id = is_separator(token->prev->str, sep);
			// 	if (sp_id == -1)
			// 	{
					
			// 	}
				
			// 	// <<eof ewf(ls) | <eof wrge(lss)
			// 	// ewf(ls)
			// }
			if (old_sp_id == 8)
			{
				if (sp_id == -1)
				{
					here_doc_befor_error(all_tokens, i);
					return (syntx_error(token->next->str), 1);
				}
				if (sp_id != -1 && sp_id < 4 && token->next->next->next)
				{
					i += 2;
					here_doc_befor_error(all_tokens, i);
					return (syntx_error(token->next->next->next->str), 1);
				}
			}
			if (old_sp_id > 3)
			{
				if (old_sp_id == 7 && sp_id > 3)
				{
					here_doc_befor_error(all_tokens, i);
					syntx_error(sep[sp_id]);
					return (1);
				}
				// if (sp_id > 3 && sp_id != 7)
				// {
				// 	// printf("here\n");
				// 	syntx_error(sep[sp_id]);
				// 	here_doc_befor_error(all_tokens, i);
				// 	return (1);
				// }
			}
		}
	}
	return (0);
}

int	syntax_error_handler(t_tokens *tokens)
{
	t_tokens	*tmp;
	int			index;
	char		**sep;
	int			par;

	tmp = tokens;
	index = 0;
	par = 0;
	sep = ft_split(">> << > < || && | ( )", ' ');
	while (tmp)
	{
		if(check_quotes(tmp->str))
		{
			here_doc_befor_error(tokens, index);
			return (free_double_ptr(sep), 258);
		}
		// if (check_separators(sep, tokens, tmp, index))
		// 	return (free_double_ptr(sep), 258);
		// if (!ft_strcmp(tmp->str, "("))
		// 	par++;
		// if (!ft_strcmp(tmp->str, ")"))
		// 	par--;
		tmp = tmp->next;
		index++;
	}
	// if (par > 0)
	// {
	// 	here_doc_befor_error(tokens, index);
	// 	syntx_error("(");
	// }
	// if (par < 0)
	// {
	// 	here_doc_befor_error(tokens, index);
	// 	syntx_error(")");
	// }
	return (free_double_ptr(sep), 0);
}










// int	find_syntax_error(t_tokens *tokens)
// {
// 	t_tokens	*tmp;
// 	char		**sep;
// 	// int			sep_id;
// 	int			index;

// 	tmp = tokens;
// 	index = 0;
// 	sep = ft_split(">> << > < || && | ( )", ' ');
// 	while (tmp)
// 	{
// 		if(check_quotes(tmp->str))
// 			break ;
// 		if (check_separators(tmp);
// 		// sep_id = is_separator(sep, tmp->str);
// 		tmp = tmp->next;
// 		index++;
// 	}
// 	return (index);
// }

// int	syntax_error_handler(t_tokens *tokens)
// {
// 	t_tokens	*here_docs;
// 	t_tokens	*tmp;
// 	int			index;
// 	int			j;

// 	tmp = tokens;
// 	index = find_syntax_error(tokens);
// 	if (index == count_tokens(tokens))
// 		return (0);
// 	here_docs = ((j = 0), NULL);
// 	while (tmp && j < index)
// 	{
// 		if (ft_strnstr(tmp->str, "<<", 2))
// 		{
// 			tmp = tmp->next;
// 			j++;
// 			create_tokens(&here_docs, ft_strdup(tmp->str), 0);
// 		}
// 		j++;
// 		tmp = tmp->next;
// 	}
// 	run_here_docs(here_docs);
// 	return (258);
// }
