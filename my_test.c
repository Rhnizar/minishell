/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:51:57 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/04 11:49:12 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_cmdshell(t_cmdshell *cmdshell, char *line)
{
	// cmdshell->cmd = command(line);
	(void)cmdshell;
	int	i;

	i = 0;
	while (line[i] && line[i] != '|')
	{
		i++;
	}
}

void	create_list(t_listt **list, t_cmdshell *cmdshell)
{	
	t_listt	*new;
	t_listt	*tmp;
	
	new = malloc(sizeof(t_list));
	if (!new)
		return ;
	new->cmdshell = cmdshell;
	new->next = NULL;
	if (!(*list))
	{
		*list = new;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	print_list2(t_listt *lst)
{
	while (lst)
	{
		printf("\n\n ======= >>>>    %d\n\n", lst->cmdshell->pip);
		lst = lst->next;
	}
}

int	count_cmd(char *line)
{
	int	i;
	int	count;
	
	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '|')
			count++;
		i++;
	}
	return(count);
}

char	**split_in_pip(char *line)
{
	return (ft_split(line, '|'));
}

int main(void)
{
	t_listt		*lst;
	t_cmdshell	*shell;
	int			count;
	// int			i;
	// int			index;

	lst = NULL;
	// i = 0;
	// index = 0;
	count = count_cmd("cat Makefile | grep minishell | wc -l");
	shell = malloc(sizeof(t_cmdshell));
	if (!shell)
		return (1);

	char	**sp_pip;
	int		i = 0;
	sp_pip = split_in_pip("cat Makefile | grep minishell | wc -l");
	while (sp_pip[i])
	{
		// shell->pip = 1;
		// fill_cmdshell(shell, sp_pip[i]);
		// create_list(&lst, shell);
		printf("%s\n", sp_pip[i]);
		i++;
	}
	// print_list2(lst);
	return (0);
}