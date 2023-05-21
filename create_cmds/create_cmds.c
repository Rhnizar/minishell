/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 09:01:12 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/20 09:01:47 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_sep_or_red(char *str, char **str_to_check)
{
	int re;

	re = -1;
	if (check_quote_cmd(str) == 0)
		re = find_separator(str_to_check, str);
	return(re);
}

void	check_node1(t_cmds **cmd, t_tokens *tmp)
{
	int	red_id;
	int	sep_id;

	red_id = check_sep_or_red(tmp->str, (*cmd)->spl_redi);
	sep_id = check_sep_or_red(tmp->str, (*cmd)->spl_sp_char);
	if (red_id != -1 && check_quote_cmd(tmp->str) == 0 && (tmp->prev == NULL || sep_id != -1))
	{
		(*cmd)->redi[red_id] = ft_strjoin(ft_strdup((*cmd)->redi[red_id]), tmp->str);
		(*cmd)->redi[red_id] = ft_strjoin(ft_strdup((*cmd)->redi[red_id]), tmp->next->str);
	}
	else
		(*cmd)->cmd = tmp->str;
}

t_tokens	*fill_struct_cmds(t_cmds **cmd, t_tokens *tokens)
{
	t_tokens *tmp;
	int		arg_i;
	int		red_id_prev;

	tmp = tokens;
	arg_i = 0;
	red_id_prev = -1;
	while (tmp != NULL || (*cmd)->sp_id == -1)
	{
		(*cmd)->red_id = check_sep_or_red(tmp->str, (*cmd)->spl_redi);
		(*cmd)->sp_id = check_sep_or_red(tmp->str, (*cmd)->spl_sp_char);
		if (tmp->prev)
			red_id_prev = check_sep_or_red(tmp->prev->str, (*cmd)->spl_redi);
		if (check_subshell(tmp->str) == 1)
			(*cmd)->subshell = ft_strdup(tmp->str);
		else if (tmp->prev == NULL || (*cmd)->sp_id != -1)
			check_node1(cmd, tmp);
		else if ((tmp->prev != NULL && (*cmd)->red_id == -1) || (((*cmd)->sp_id == -1) && (red_id_prev == -1)))
			(*cmd)->args[arg_i++] = ft_strdup(tmp->str);
		else if ((*cmd)->sp_id != -1)
			(*cmd)->sp_char = (*cmd)->spl_sp_char[(*cmd)->sp_id];
		if (!tmp->next)
			return (NULL);
		tmp = tmp->next;
	}
	return (tmp);
}

t_cmdshell	*fill_list_cmds(t_cmdshell *lst, t_tokens *token)
{
	t_tokens	*tmp;
	t_cmds		*cmds;

	tmp = token;
	cmds = NULL;
	lst = NULL;
	while (tmp)
	{
		init_cmd(&cmds, tmp);
		tmp = fill_struct_cmds(&cmds, tmp);
		create_cmds(&lst, cmds);
		free_double_ptr(cmds->args);
		free_double_ptr(cmds->redi);
		free_double_ptr(cmds->spl_redi);
		free_double_ptr(cmds->spl_sp_char);
		free(cmds);
	}
	return (lst);
}
