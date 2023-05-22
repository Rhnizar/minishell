/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 22:36:28 by kchaouki          #+#    #+#             */
/*   Updated: 2023/05/22 23:54:28 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_bonus.h"

char	*handle_subshell(t_tokens **tmp)
{
	char	*output;
	int		par;

	output = NULL;
	par = 1;
	output = join_with_space(output, (*tmp)->str);
	while ((*tmp) && par != 0)
	{
		if (!ft_strcmp((*tmp)->str, "("))
			par++;
		if (!ft_strcmp((*tmp)->str, ")"))
			par--;
		output = join_with_space(output, (*tmp)->str);
		(*tmp) = (*tmp)->next;
	}
	return (output);	
}

t_tokens	*analyzer(t_tokens *tokens, int	*exit_status)
{
	t_tokens	*new_tokens;
	t_tokens	*tmp;
	
	*exit_status = syntax_error_handler(tokens);
	if (*exit_status == 258)
		return (NULL);
	tmp = tokens;
	new_tokens = NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->str, "("))
			create_tokens(&new_tokens, quotes_handler(tmp->str));
		else
			create_tokens(&new_tokens, handle_subshell(&tmp));
		tmp = tmp->next;
	}
	free_tokens(tokens);
	return (new_tokens);
}
