/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 09:36:17 by kchaouki          #+#    #+#             */
/*   Updated: 2023/05/18 11:12:47 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_word(char *arg)
{
	char	*word;
	char	**sep;
	int		sp;
	int		i;

	i = 0;
	sep = create_separator();
	i += skip_spaces(arg);
	sp = 0;
	word = NULL;
	while (arg[i] && arg[i] != ' ' && arg[i] != '\t' 
	&& !find_separator(sep, &arg[i], &sp))
		word = join_to_str(word, arg[i++]);
	free_double_ptr(sep);
	return (word);
}	

int	check_can_be_at_start(char *arg, char **sep, int sp_id, int *j)
{
	int	i;
	int	old_sp;

	i = 0;
	old_sp = sp_id;
	if (sp_id < 4 || sp_id == 7)
	{
		i += arg_len(sep[sp_id]) + skip_spaces(&arg[i + arg_len(sep[sp_id])]);
		if (!arg[i])
			return (syntx_error("newline"), 1);
		find_separator(sep, &arg[i], &sp_id);
		// if ((old_sp == 7 && sp_id > 3 && sp_id != 7) || (old_sp < 4 && sp_id > 3))
		// if (sp_id < 9 && (old_sp == 7 && sp_id != 7))
		if (sp_id < 9 || (old_sp == 7 && sp_id != 7))
			return (syntx_error(sep[sp_id]), 1);
		(*j) += i;
	}
	return (0);
}

int	check_sequel(char *arg, char **sep, int sp_id, int *j)
{
	int		old_sp_id;
	char	*word;

	// printf("here: %s\n", &arg[(*j)]);
	old_sp_id = sp_id;
	(*j) += arg_len(sep[sp_id]) + skip_spaces(&arg[*j + arg_len(sep[sp_id])]);
	if (!arg[*j] && sp_id != 8)
		return (syntx_error("newline"), 1);
	find_separator(sep, &arg[*j], &sp_id);
	if (old_sp_id == 8 && sp_id == 7)
		return (syntx_error(sep[sp_id]), 1);
	if (old_sp_id == 8 && sp_id > 3 && sp_id < 8 && !arg[*j+ arg_len(sep[sp_id])])
		return (syntx_error("newline"), 1);
	// if (old_sp_id == 7 && sp_id == 9 && arg[*j+ arg_len(sep[sp_id])])
	if (old_sp_id == 8 && sp_id == 9 && arg[*j+ arg_len(sep[sp_id])])
	{
		word = get_word(&arg[*j]);
		syntx_error(word);
		return (free(word), 1);
	}
	if (sp_id > 3 && sp_id != 7 && sp_id < 9 && old_sp_id != 8)
		return (syntx_error(sep[sp_id]), 1);
	return (0);
}

// int	check_befor_separator(char *full_str, int sp_id, int i)
// {
// 	printf("befor: %s\n", full_str);
// 	if (sp_id < 9)
// 	{
// 		if (sp_id == 7)
// 		{
// 			while (full_str[i] == ' ' || full_str[i] == '\t')
// 				i--;
// 			while (i > 0 && full_str[i])
// 			printf("%s\n", &full_str[i]);
// 			exit(1);
// 			// while (i--)
				
// 		}
// 	}
// 	return (0);
// }

int	separator_checker(char **sep, char *arg, char *arg_from_start, int *i)
{
	int		j;
	int		sp_id;

	j = 0;
	find_separator(sep, &arg[j], &sp_id);
	(void) arg_from_start;
	// if (check_befor_separator(arg_from_start, sp_id, *i))
	// 	return (1);
	if (check_can_be_at_start(&arg[j], sep, sp_id, &j))
		return (1);
	if (sp_id > 3 && sp_id != 7 && sp_id < 9)
	{
		if (*i == 0)
			return (syntx_error(sep[sp_id]), 1);
		if (check_sequel(&arg[j], sep, sp_id, &j))
			return (1);
	}
	return (((*i) += j), 0);
}

int	skip_normale_characters(char **sep, char *str, int *sp_id)
{
	int		i;

	i = 0;
	while (str[i] && !is_quote(str[i]) && !find_separator(sep , &str[i], sp_id))
		i++;
	return (i);	
}

int	find_snytx_error(char *arg)
{
	char	**sep;
	int		quote;
	int		sp_id;
	int		i;

	sp_id = ((sep = create_separator()), (i = 0), 0);
	while (arg[i])
	{
		i += skip_normale_characters(sep, &arg[i], &sp_id);
		if (sp_id < 9 && separator_checker(sep, &arg[i], arg, &i))
			return (free_double_ptr(sep), i - 1);
		quote = is_quote(arg[i]);
		if (arg[i + 1] == '\0' && quote > 0)
			return (free_double_ptr(sep), syntx_error(recognize_quote(quote)), i - 1);
		else if (arg[i + 1] != '\0')
			i++;
		while (arg[i] && quote != is_quote(arg[i]))
			i++;
		if (arg[i] == '\0' && quote != is_quote(arg[i]))
			return (free_double_ptr(sep), syntx_error(recognize_quote(quote)), i - 1);
		else if (quote == is_quote(arg[i]))
			i++;
	}
	check_parentheses(arg);
	return (i - 1);
}

int	syntax_error_handler(char *arg)
{
	int		error_index;
	char	*here_docs;
	char	*exact_arg;
	char	*ret;
	int		j;

	j = 0;
	here_docs = NULL;
	error_index = find_snytx_error(arg);
	if (arg_len(arg) == error_index)
		return (0);
	while (j < error_index)
	{
		ret = ft_strnstr(&arg[j], "<<", error_index);
		if (!ret)
			break ;
		j += arg_len(&arg[j]) - arg_len(ret) - 1;
		exact_arg = get_word(&ret[2]);
		here_docs = join_with_space(here_docs, exact_arg);
		j += arg_len(exact_arg);
	}
	run_here_docs(here_docs);
	free(here_docs);
	return (258);
}