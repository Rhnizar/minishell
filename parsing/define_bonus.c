/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:14:25 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/31 16:24:05 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_subshell(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '(')
			return (1);
		i++;
	}
	return (0);
}

int	init_struct_utils(t_utils **utils)
{
	*utils = malloc(sizeof(t_utils));
	if (!(*utils))
		return (-1);
	(*utils)->spl_redi = ft_split(">> << < >", ' ');
	if (!((*utils)->spl_redi))
		return (-1);
	(*utils)->spl_sp_char = ft_split("|| && |", ' ');
	if (!((*utils)->spl_sp_char))
		return (-1);
	(*utils)->sp_id = -1;
	(*utils)->red_id = -1;
	(*utils)->red_id_prev = -1;
	(*utils)->sp_id_prev = -1;
	(*utils)->red_id_prev_prev = -1;
	return (0);
}

void	check_define(t_cmds *cmds, t_tokens *tokens, t_utils *utils)
{
	if (check_subshell(tokens->str) == 1)
		cmds->subshell = ft_strdup(tokens->str);
	else if (tokens->prev == NULL || utils->sp_id_prev != -1)
		check_node1(&cmds, tokens, utils);
	else if (utils->red_id != -1)
	{
		fill_list_redis(&cmds->redis, \
			ft_strdup(tokens->next->str), utils->red_id);
		utils->red_id = -1;
	}
	else if (utils->red_id_prev_prev != -1 && utils->red_id == -1 \
		&& utils->sp_id == -1 && cmds->args == NULL)
		fill_list_args(&cmds->args, ft_strdup(tokens->str));
	else if (tokens->prev != NULL && utils->red_id_prev == -1 \
		&& utils->sp_id == -1 && utils->sp_id_prev == -1)
		fill_list_args(&cmds->args, ft_strdup(tokens->str));
}

t_tokens	*fill_struct_cmds(t_cmds *cmds, t_tokens *tokens, t_utils *utils)
{
	int	i;

	i = 0;
	while (tokens && utils->sp_id == -1)
	{
		utils->red_id = find_separator(utils->spl_redi, tokens->str);
		utils->sp_id = find_separator(utils->spl_sp_char, tokens->str);
		if (utils->sp_id != -1)
			utils->sp_id += 4;
		if (tokens->prev)
		{
			utils->red_id_prev = find_separator(utils->spl_redi, \
				tokens->prev->str);
			utils->sp_id_prev = find_separator(utils->spl_sp_char, \
				tokens->prev->str);
		}
		if (i++ >= 2)
			utils->red_id_prev_prev = find_separator(utils->spl_redi, \
				tokens->prev->prev->str);
		cmds->operator = ((check_define(cmds, tokens, utils)), utils->sp_id);
		tokens = tokens->next;
	}
	if (cmds->args)
		cmds->is_builtin = is_builtin(cmds->args->str);
	return (tokens);
}

t_tokens	*analyzer(t_tokens *tokens, int	*exit_status)
{
	t_tokens	*new_tokens;
	t_tokens	*tmp;

	*exit_status = syntax_error_handler(tokens);
	if (*exit_status == 258)
	{
		free_tokens(tokens);
		return (NULL);
	}
	new_tokens = NULL;
	tmp = tokens;
	while (tmp)
	{	
		if (ft_strcmp(tmp->str, "(") != 0)
			create_tokens(&new_tokens, ft_strdup(tmp->str));
		else
			create_tokens(&new_tokens, handle_subshell(&tmp));
		tmp = tmp->next;
	}
	free_tokens(tokens);
	return (new_tokens);
}
