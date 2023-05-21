/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 10:52:56 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/20 19:44:40 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quote_cmd(char *str)
{
	int i;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

int	check_subshell(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if (str[i] == '(')
			return (1);
		i++;
	}
	return (0);
}

char	**init_args(t_tokens *tokens, t_cmds *cmds)
{
	t_tokens *tmp;
	char	**args;
	int		len;
	int		red_id_prev;

	tmp = tokens;
	len = 0;
	red_id_prev = -1;
	while (tmp && cmds->sp_id == -1)
	{
		cmds->red_id = check_sep_or_red(tmp->str, cmds->spl_redi);
		if (tmp->prev)
			red_id_prev = check_sep_or_red(tmp->prev->str, cmds->spl_redi);
		cmds->sp_id = check_sep_or_red(tmp->str, cmds->spl_sp_char);
		if (tmp->prev != NULL && cmds->red_id == -1 \
			&& cmds->sp_id == -1 && red_id_prev == -1)
			len++;
		tmp = tmp->next;
	}
	args = malloc(sizeof(char *) * (len + 1));
	if (!args)
		return (NULL);
	return (args);
}

char	**init_redi(t_tokens *tokens, t_cmds *cmds)
{
	t_tokens *tmp;
	char	**redi;
	int		len;
	int		i;
	
	i = 0;
	tmp = tokens;
	len = 0;
	while (tmp && cmds->sp_id == -1)
	{
		cmds->sp_id = check_sep_or_red(tmp->str, cmds->spl_sp_char);
		cmds->red_id = check_sep_or_red(tmp->str, cmds->spl_redi);
		if (cmds->red_id != -1 && check_quote_cmd(tmp->str) == 0)
			len++;
		tmp = tmp->next;
	}
	redi = malloc(sizeof(char *) * (len + 1));
	if (!redi)
		return (NULL);
	return (redi); 
}

void	init_cmd(t_cmds **cmds, t_tokens *tokens)
{
	(void) tokens;
	*cmds = malloc(sizeof(t_cmds));
	if (!cmds)
		return ;
	(*cmds)->sp_id = -1;
	(*cmds)->red_id = -1;
	(*cmds)->spl_redi = ft_split("<< < > >>", ' ');
	(*cmds)->spl_sp_char = ft_split("|| && |", ' ');
	(*cmds)->cmd = NULL;
	(*cmds)->args = init_args(tokens, *cmds);
	(*cmds)->redi = init_redi(tokens, *cmds);
	(*cmds)->sp_char = NULL;
	(*cmds)->subshell = NULL;
}
