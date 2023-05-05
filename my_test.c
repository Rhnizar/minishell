/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:51:57 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/05 17:09:48 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// // void	cheack_pip(t_cmdshell *cmdshell, char *line)
// // {
// // 	int	i;

// // 	i = 0;
// // 	while (line[i] && line[i] != '|')
// // 		i++;
// // 	if (line[i] == '|')
// // 		cmdshell->pip = 1;
// // }
// // void	fill_cmdshell(t_cmdshell *cmdshell, char *line)
// // {
// // 	cmdshell->cmd = command(line);
// // 	int	i;

// // 	i = 0;
// // 	while (line[i] && line[i] != '|')
// // 	{
// // 		i++;
// // 	}
// // }

// void	create_list(t_listt **list, t_cmdshell *cmdshell)
// {	
// 	t_listt	*new;
// 	t_listt	*tmp;
	
// 	new = malloc(sizeof(t_list));
// 	if (!new)
// 		return ;
// 	new->cmdshell = cmdshell;
// 	new->next = NULL;
// 	if (!(*list))
// 	{
// 		*list = new;
// 		return ;
// 	}
// 	tmp = *list;
// 	while (tmp->next)
// 		tmp = tmp->next;
// 	tmp->next = new;
// }

// void	print_list2(t_listt *lst)
// {
// 	while (lst)
// 	{
// 		// printf("\n ======= >>>>    %d\n", lst->cmdshell->pip);
// 		// printf("\n\n ======= >>>>    %s\n\n", lst->cmdshell->cmd);
// 		lst = lst->next;
// 	}
// }

// int	count_cmd(char *line)
// {
// 	int	i;
// 	int	count;
	
// 	i = 0;
// 	count = 0;
// 	while (line[i])
// 	{
// 		if (line[i] == '|')
// 			count++;
// 		i++;
// 	}
// 	return(count);
// }

// int	len_dou_poi(char **str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 		i++;
// 	return (i);
// }

// char	**split_in_pip(char *line)
// {
// 	char	**sp_pip;
// 	// char	**sp_and;
// 	// char	**sp_or;
// 	int		i;
// 	int		len;

// 	i = 0;
// 	sp_pip = ft_split(line, '|');
// 	len = len_dou_poi(sp_pip) - 1;
// 	while (len != 0)
// 	{
// 		sp_pip[i] = ft_strjoin(sp_pip[i], "|");
// 		i++;
// 		len--;
// 	}
// 	return (sp_pip);
// }

// int main(void)
// {
// 	t_listt		*lst;
// 	t_cmdshell	*shell;
// 	int			count;
// 	// int			i;
// 	// int			index;

// 	lst = NULL;
// 	// i = 0;
// 	// index = 0;
// 	count = count_cmd("cat Makefile | grep minishell | wc -l");
// 	shell = malloc(sizeof(t_cmdshell));
// 	if (!shell)
// 		return (1);

// 	char	**sp_pip;
// 	int		i = 0;
// 	sp_pip = split_in_pip("cat Makefile | grep minishell | wc -l");
// 	while (sp_pip[i])
// 	{
// 		// cheack_pip(shell, sp_pip[i]);
// 		// shell->cmd = sp_pip[i];
// 		// fill_cmdshell(shell, sp_pip[i]);
// 		create_list(&lst, shell);
// 		printf("%s\n", sp_pip[i]);
// 		i++;
// 	}
// 	print_list2(lst);
// 	return (0);
// }
// [ "<<", ">>", "||", "&&"]

// [ '<', '>', '(', ')', '*', '|']



// echo CMD
// test
// && AND
// echo
// lala 
// > RED_OUT
// lala /ARG_RED_IN
// > RED_OUT
// baba /ARG_RED_IN
// > RED_OUT
// tata /ARG_RED_IN
// | PIPE
// ls 
// ( PREN

// cat
// -t -e
// <
// tata 