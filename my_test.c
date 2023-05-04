/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:51:57 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/04 11:03:31 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_cmdshell(t_cmdshell *cmdshell, char *line, int *i)
{
	// cmdshell->cmd = command(line);
	if (line[*i] == '|')
		(*i)++;
	while (line[*i] && line[*i] != '|')
	{
		(*i)++;
	}
	if (line[*i] == '|')
		cmdshell->pip = 5;
}

void	create_list(t_list **list, t_cmdshell *cmdshell)
{	
	t_list	*new;
	t_list	*tmp;
	
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

void	print_list2(t_list *lst)
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

int main(void)
{
	t_list		*lst;
	t_cmdshell	*shell;
	int			count;
	int			i;
	int			index;

	lst = NULL;
	i = 0;
	index = 0;
	count = count_cmd("cat Makefile | grep minishell  wc -l") + 1;
	shell = malloc(sizeof(t_cmdshell) * count);
	if (!shell)
		return (1);
	while (i++ < count)
	{
		fill_cmdshell(shell, "cat Makefile | grep minishell  wc -l", &index);
		create_list(&lst, shell);
	}
	print_list2(lst);
	return (0);
}