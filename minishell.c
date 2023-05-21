/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:20:11 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/21 15:16:56 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redis(t_redis *redis)
{
	t_redis	*tmp;
	t_redis	*tmp2;

	tmp = redis;
	while (tmp)
	{
		tmp2 = tmp->next;
		free (tmp->str);
		free (tmp);
		tmp = tmp2;
	}
}

void	free_args(t_args *args)
{
	t_args	*tmp;
	t_args	*tmp2;

	tmp = args;
	while (tmp)
	{
		tmp2 = tmp->next;
		free (tmp->str);
		free (tmp);
		tmp = tmp2;
	}
}

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

int	check_sep_or_red(char *str, char **str_to_check)
{
	int re;

	re = -1;
	if (check_quote_cmd(str) == 0)
		re = find_separator(str_to_check, str);
	return(re);
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

void	fill_list_args(t_args **lst, char *str)
{
	t_args	*new;
	t_args	*tmp;

	new = malloc(sizeof(t_args));
	if (!new)
		return ;
	new->str = str;
	new->next = NULL;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while(tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}


void	fill_list_redis(t_redis **lst, char *str, int type)
{
	t_redis	*new;
	t_redis	*tmp;

	new = malloc(sizeof(t_redis));
	if (!new)
		return ;
	new->str = str;
	new->type = type;
	new->next = NULL;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while(tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	check_node1(t_cmds **cmd, t_tokens *tmp)
{
	if ((*cmd)->red_id != -1)
	{
		fill_list_redis(&(*cmd)->redis, ft_strdup(tmp->next->str), (*cmd)->red_id);
		(*cmd)->red_id = -1;
	}
	else if ((*cmd)->sp_id != -1)
		(*cmd)->cmd = ft_strdup(tmp->next->str);
	else
		(*cmd)->cmd = ft_strdup(tmp->str);
}

t_tokens *fill_struct_cmds(t_cmds *cmds, t_tokens *tokens)
{
	t_tokens	*tmp;
	int			red_id_prev;
	int			sp_id_prev;

	tmp = tokens;
	red_id_prev = -1;
	sp_id_prev = -1;
	while (tmp && cmds->sp_id == -1)
	{
		cmds->red_id = check_sep_or_red(tmp->str, cmds->utils->spl_redi);
		cmds->sp_id = check_sep_or_red(tmp->str, cmds->utils->spl_sp_char);
		if (tmp->prev)
		{
			red_id_prev = check_sep_or_red(tmp->prev->str, cmds->utils->spl_redi);
			sp_id_prev = check_sep_or_red(tmp->prev->str, cmds->utils->spl_sp_char);
		}
		if (check_subshell(tmp->str) == 1)
			cmds->subshell = ft_strdup(tmp->str);
		else if ((tmp->prev == NULL || cmds->sp_id != -1) && cmds->cmd == NULL)
			check_node1(&cmds, tmp);
		else if (cmds->red_id != -1)
		{
			fill_list_redis(&cmds->redis, ft_strdup(tmp->next->str), cmds->red_id);
			cmds->red_id = -1;
		}
		else if (tmp->prev != NULL && red_id_prev == -1 && cmds->sp_id == -1 && sp_id_prev == -1)
			fill_list_args(&cmds->args, ft_strdup(tmp->str));
		tmp = tmp->next;
	}
	return(tmp);
}

void	create_cmds(t_cmdshell **lst, t_cmds *cmds)
{
	t_cmdshell	*new;
	t_cmdshell	*tmp;

	new = malloc(sizeof(t_tokens));
	if (!new)
		return ;
	new->cmds = cmds;
	new->next = NULL;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while(tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_cmdshell	*fill_list_cmds(t_cmdshell *lst, t_tokens *tokens)
{
	t_tokens	*tmp;
	t_cmds		*cmds;

	tmp = tokens;
	lst = NULL;
	cmds = malloc(sizeof(t_cmds));
	while (tmp)
	{
		init_struct_cmds(&cmds);
		tmp = fill_struct_cmds(cmds, tmp);
		// printf("heeeere  %s\n", tmp->str);
		// exit(1);
		create_cmds(&lst, cmds);
		free_double_ptr(cmds->utils->spl_sp_char);
		free_double_ptr(cmds->utils->spl_redi);
		// free_redis(cmds->redis);
		// free_args(cmds->args);
		free(cmds->cmd);
		free(cmds->subshell);
	}
	free_tokens(tokens);
	return (lst);
}

int	main(void)
{
	char	*read_line;
	t_tokens	*tokens;
	t_cmdshell *lst_cmd;
	int			nred = 1;
	int			narg = 1;
	// t_global	*glob;

	lst_cmd = NULL;
	while (1)
	{
		read_line = readline("minishell ~ ");
		if (read_line)
		{
			if (read_line[0] != 0)
				add_history(read_line);
			tokens = split_and_fill_list(read_line);
			// while (tokens)
			// {
			// 	printf("%s\n", tokens->str);
			// 	tokens = tokens->next;
			// }
			// glob = malloc(sizeof(t_global));
			// if (!glob)
			// 	return (-1);
			lst_cmd = fill_list_cmds(lst_cmd, tokens);
			printf("\n--------------------------------------------------------------------------\n");
			while (lst_cmd)
			{
				printf("cmd ==> %s\n", lst_cmd->cmds->cmd);
				printf("subshell ===> %s\n", lst_cmd->cmds->subshell);
				printf("\n=======  all arguments  =======\n");
				while(lst_cmd->cmds->args)
				{
					printf("=======  argument %d =======\n", narg++);
					printf("arg : %s\n", lst_cmd->cmds->args->str);
					
					lst_cmd->cmds->args = lst_cmd->cmds->args->next;
				}
				printf("\n======= all redirections =======\n");
				while(lst_cmd->cmds->redis)
				{
					printf("======= redirection %d =======\n", nred++);
					printf("red : %s\n", lst_cmd->cmds->redis->str);
					printf("type red : %d\n", lst_cmd->cmds->redis->type);
					lst_cmd->cmds->redis = lst_cmd->cmds->redis->next;
				}
				lst_cmd = lst_cmd->next;
			}
			printf("\n--------------------------------------------------------------------------\n");
		}
		else
			break ;
	}
	printf("exit\n");
	return (0);
}
