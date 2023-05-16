/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 10:48:33 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/14 17:52:52 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_quote
{
	char			*str;
	struct s_quote	*next;
}	t_quote;

void	list_quote(t_quote **lst, char *str)
{
	t_quote	*new;
	t_quote	*tmp;

	new = malloc(sizeof(t_tokens));
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

char	*join_to_str(char *str, char c)
{
	char	*output;
	int		i;

	if (!str)
		output = malloc(2);
	else
		output = malloc(ft_strlen(str) + 2);
	if (!output)
		return (NULL);
	i = 0;
	while (str && str[i])
	{
		output[i] = str[i];
		i++;
	}
	output[i++] = c;
	output[i] = '\0';
	free (str);
	return (output);
}

int	is_quote(char c)
{
	if (c == '\'')
		return (1);
	else if (c == '\"')
		return (2);
	return (0);
}

// int	snytx_error_checker(char *arg)
// {
// 	char	**sep;
// 	int		quote;
// 	int		i;

// 	i = -1;
// 	sep = create_sp();
// 	while (arg[++i])
// 	{
// 		while (arg[i] && is_quote(arg[i]) == 0)
// 		{
// 			i++;
// 		}
// 		quote = is_quote(arg[i]);
// 		if (arg[i + 1] == '\0' && quote > 0)
// 			return (syntx_error(recognize_quote(quote)), free(arg), 258);
// 		else if (arg[i + 1] != '\0')
// 			i++;
// 		while (arg[i] && quote != is_quote(arg[i]))
// 			i++;
// 		if (arg[i] == '\0' && quote != is_quote(arg[i]))
// 			return (syntx_error(recognize_quote(quote)), free(arg), 258);
// 	}
// 	return (0);
// }

void	fill_list_quote(char *str, t_quote **lst)
{
	char	*output;
	int		i;
	int		single_quote;
	int		double_quote;
	int		count;

	i = -1;
	single_quote = 0;
	double_quote = 0;
	count = 0;
	while (str[++i])
	{
		if (str[i] && str[i] == '"' && double_quote == 0 && single_quote == 0)
			double_quote = 1;
		
		else if (str[i] && str[i] == '"' && double_quote == 1 && single_quote == 0)
			double_quote = 0;

		
		// if (str[i] && double_quote == 1)
		// 	output = join_to_str(output, str[i]);
		
		if (str[i] && str[i] == '\'' && double_quote == 0 && single_quote == 0)
			single_quote = 1;
		else if (str[i] && str[i] == '\'' && double_quote == 0 && single_quote == 1)
			single_quote = 0;
		
	}
	// int		i;
	// char	*output;
	// int		quote;

	// i = -1;
	// output = NULL;
	// while (str[++i])
	// {
	// 	while (str[i] && is_quote(str[i]) == 0)
	// 		output = join_to_str(output, str[i++]);
	// 	quote = is_quote(str[i]);
	// 	if (output)
	// 	{
	// 		list_quote(lst, output);
	// 		// free(output);
	// 		// output = NULL;
	// 	}
	// 	while (str[i] && str[i] != is_quote(str[i]))
	// 		output = join_to_str(output, str[i++]);
	// 	if (output)
	// 	{
	// 		list_quote(lst, output);
	// 		// free(output);
	// 		// output = NULL;
	// 	}
	// 	if (str[i])
	// 		i++;
	// }
	
	// int	i;

	// i = 0;
	// char *str_tmp;
	// str_tmp = NULL;
	// while (str[i])
	// {
	// 	if (str[i] == '"')
	// 	{
	// 		if (str_tmp)
	// 		{
	// 			list_quote(lst, str_tmp);
	// 			free(str_tmp);
	// 		}
	// 		str_tmp = join_to_str(str_tmp, str[i++]);
	// 		while (str[i] != '"')
	// 			str_tmp = join_to_str(str_tmp, str[i++]);
	// 		str_tmp = join_to_str(str_tmp, str[i++]);
	// 		list_quote(lst, str_tmp);
	// 		free(str_tmp);
	// 	}
	// 	else if (str[i] == '\'')
	// 	{
	// 		if (str_tmp)
	// 		{
	// 			list_quote(lst, str_tmp);
	// 			free(str_tmp);
	// 		}
	// 		str_tmp = join_to_str(str_tmp, str[i++]);
	// 		while (str[i] != '\'')
	// 			str_tmp = join_to_str(str_tmp, str[i++]);
	// 		str_tmp = join_to_str(str_tmp, str[i++]);
	// 		list_quote(lst, str_tmp);
	// 		free(str_tmp);
	// 	}
	// 	else
	// 	{
	// 		str_tmp = join_to_str(str_tmp, str[i]);
	// 		i++;
	// 	}
	// }
}

int main()
{
	char *read_line;
	t_quote	*list;

	list = NULL;
	while (1)
	{
		read_line = readline("> ");
		if (read_line[0] != 0)
			add_history(read_line);
		fill_list_quote(read_line, &list);
		while (list)
		{
			printf("here\n");
			printf("%s\n", list->str);
			list = list->next;
		}
		// printf("%s\n", read_line);
	}
}