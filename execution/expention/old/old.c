/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 23:14:33 by kchaouki          #+#    #+#             */
/*   Updated: 2023/06/03 23:14:36 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// char	*expantion_dollar_case(t_tokens **tmp, t_env *env, char *old, int exit_status)
// {
// 	char	*output;
// 	char	*value;
// 	int		count_dollar;

// 	output = NULL;
// 	count_dollar = 1;
// 	while ((*tmp)->next && !ft_strcmp((*tmp)->str, "$"))
// 	{
// 		count_dollar++;
// 		(*tmp) = (*tmp)->next;
// 	}
// 	if (!(*tmp)->next && count_dollar % 2 != 0 && !ft_strcmp((*tmp)->str, "$"))
// 		output = ft_strjoin(output, (*tmp)->str);
// 	else if (!(*tmp)->next && count_dollar % 2 == 0 && !old && !ft_strcmp((*tmp)->str, "$"))
// 		return (NULL);
// 	else if (ft_strcmp((*tmp)->str, "$") && ft_strcmp((*tmp)->str, "'") \
// 	&& ft_strcmp((*tmp)->str, "\"") && count_dollar % 2 == 0)
// 	{
// 		if (!ft_isalnum((*tmp)->str[0]) && ft_strcmp((*tmp)->str, "?"))
// 		{
// 			output = ft_strjoin(output, (*tmp)->prev->str);
// 			output = ft_strjoin(output, (*tmp)->str);
// 		}
// 		else if (!ft_strcmp((*tmp)->str, "?"))
// 			output = ft_strjoin(output, ft_itoa(exit_status));
// 		else
// 		{
// 			value = get_value((*tmp)->str, env);
// 			if (ft_strlen(value) == 0 && !old)
// 				return (NULL);
// 			output = ft_strjoin(output, value);
// 			free(value);	
// 		}
// 	}
// 	else if (!ft_strcmp((*tmp)->str, "\"") || !ft_strcmp((*tmp)->str, "'"))
// 		(*tmp) = (*tmp)->prev;
// 	else
// 		output = ft_strjoin(output, (*tmp)->str);
// 	return (ft_strjoin(old, output));
// }