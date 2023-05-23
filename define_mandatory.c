/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_mandatory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:13:31 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/23 12:07:18 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_struct_utils(t_utils **utils)
{
	*utils = malloc(sizeof(t_utils));
	if (!(*utils))
		return (-1);
	(*utils)->spl_redi = ft_split(">> << < >", ' ');
	if (!((*utils)->spl_redi))
		return (-1);
	(*utils)->spl_sp_char = ft_split("|", ' ');
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
	if (tokens->prev == NULL || utils->sp_id_prev != -1)
		check_node1(&cmds, tokens, utils);
	else if (utils->red_id != -1)
	{
		if (tokens->next)
			fill_list_redis(&cmds->redis, \
				ft_strdup(tokens->next->str), utils->red_id);
		utils->red_id = -1;
	}
	else if (utils->red_id_prev_prev != -1 && utils->red_id == -1 \
		&& utils->sp_id == -1 && cmds->cmd == NULL)
			cmds->cmd = ft_strdup(tokens->str);
	else if (tokens->prev != NULL && utils->red_id_prev == -1 \
		&& utils->sp_id == -1 && utils->sp_id_prev == -1)
		fill_list_args(&cmds->args, ft_strdup(tokens->str));
}
///// start is builtin ////

static int	double_check(char *token, char *builtin)
{
	char	*exact_token;

	exact_token = ft_strnstr(token, builtin, ft_strlen(token));
	if (!exact_token || ft_strncmp(exact_token, \
	builtin, ft_strlen(exact_token)) != 0)
		return (0);
	return (1);
}

int	is_builtin(char *token)
{
	if (double_check(token, "echo"))
		return (1);
	else if (double_check(token, "cd"))
		return (1);
	else if (double_check(token, "pwd"))
		return (1);
	else if (double_check(token, "env"))
		return (1);
	else if (double_check(token, "export"))
		return (1);
	else if (double_check(token, "unset"))
		return (1);
	else if (double_check(token, "exit"))
		return (1);
	return (0);
}

//// end struct is builtin //////
t_tokens	*fill_struct_cmds(t_cmds *cmds, t_tokens *tokens, t_utils *utils)
{
	int	i;

	i = 0;
	while (tokens && utils->sp_id == -1)
	{
		utils->red_id = find_separator(utils->spl_redi, tokens->str);
		utils->sp_id = find_separator(utils->spl_sp_char, tokens->str);
		if (utils->sp_id != -1)
			utils->sp_id += 6;
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
		check_define(cmds, tokens, utils);
		cmds->operator = utils->sp_id;
		tokens = tokens->next;
	}
	cmds->is_builtin = is_builtin(cmds->cmd);
	return (tokens);
}
