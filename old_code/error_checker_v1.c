/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checker_v1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 09:36:17 by kchaouki          #+#    #+#             */
/*   Updated: 2023/05/16 11:20:22 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <limits.h>

// char	*sp_char_handler(char *str)
// {
// 	char	**sp;
// 	if (BONUS == 0)
// 		sp = create_sp();
// } ft_strchr("\"'", c);

static int	is_quote(char c)
{
	if (c == '\'')
		return (1);
	else if (c == '\"')
		return (2);
	return (0);
}

char	**create_separator(void)
{
	if (BONUS == 0)
		return (ft_split(">> << > < |", ' '));
	return (ft_split(">> << > < || && | * ( )", ' '));
}

// {">>", "<<", "||", "&&", ">", "<", "|", "*", "(", ")"}

//i need to chang the exit status inside the struct
// so i need to pass the struct
static void	syntx_error(char *arg)
{
	ft_putstr_fd(ESYNTX, 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("\'\n", 2);
}

static char	*recognize_quote(int quote)
{
	if (quote == 1)
		return ("\'");
	return ("\"");
}

char	*find_separator(char **sep, char *str, int *sp)
{
	char	*output;
	int		j;

	j = 0;
	output = NULL;
	while (sep[j])
	{
		output = ft_strnstr(str, sep[j], ft_strlen(sep[j]));
		if (output != NULL)
			break ;
		j++;
	}
	(*sp) = j;
	return (output);
}

// int	text_befor_separator(char *s1, char *s2)
// {
// 	int	count;

// 	count = 0;
// 	while (s1[count])
// 	{
// 		if (s1[count] == s2[0])
// 			break ;
// 		// exit(1);
// 		count++;
// 	}
// 	return (count);	
// }

// int	is_separator(char *str, char **sp)
// {
	
// }


// int	separator_checker(char *arg, int *i)
// {
// 	char	**sep;
// 	char	*ret;
// 	int		sp_id;
// 	int		j;

// 	sp_id = 0;
// 	j = -1;
// 	sep = create_separator();

// 	// skip normal characters
// 	while (arg[++j])
// 	{
// 		ret = find_separator(sep, &arg[j], &sp_id);
// 		if (ret)
// 			break ;
// 	}
// 	if (j == 0 && sp_id > 3 && sp_id != 8)
// 		return (syntx_error(sep[sp_id]), 1);
// 	if (!arg[j + 1])
// 		return (syntx_error("newline"), 1);
// 	if (arg[j + ft_arg_len(sep[sp_id])])
// 		j += ft_arg_len(sep[sp_id]);
// 	// skip spaces
// 	while (arg[j] && arg[j] == ' ')
// 		j++;
// 	ret = find_separator(sep, &arg[j], &sp_id);
// 	if (!arg[j] || (sp_id < 4 && !arg[j + ft_arg_len(sep[sp_id])]))
// 		return (syntx_error("newline"), 1);
// 	if (ret)
// 		return (syntx_error(sep[sp_id]), 1);
// 	exit(1);


// 	(*i) = j;
// 	return (1);
// }


int	separator_checker(char *arg, int *i)
{
	char	**sep;
	char	*ret;
	int		sp_id;
	int		j;

	sp_id = 0;
	j = -1;
	sep = create_separator();
	while (arg[++j] && is_quote(arg[j]) == 0)
	{
		ret = find_separator(sep, &arg[j], &sp_id);
		if (ret)
			break ;
	}
	if (j == 0 && sp_id > 3 && sp_id != 8)
		return (syntx_error(sep[sp_id]), 1);
	if (ret && !arg[j + 1])
		return (syntx_error("newline"), 1);
	if (arg[j + ft_arg_len(sep[sp_id])])
		j += ft_arg_len(sep[sp_id]);
	while (arg[j] && arg[j] == ' ')
		j++;
	if (ret && !arg[j])
		return (syntx_error("newline"), 1);
	ret = find_separator(sep, &arg[j], &sp_id);
	if (sp_id < 4 && !arg[j + ft_arg_len(sep[sp_id])])
		return (syntx_error("newline"), 1);
	if (ret)
		return (syntx_error(sep[sp_id]), 1);
	return (((*i) = j), 0);
}

int	snytx_error_checker(char *arg)
{
	int		quote;
	int		i;
	int		j;

	i = -1;
	while (arg[++i])
	{
		while (arg[i] && is_quote(arg[i]) == 0)
		{
			j = 0;
			if (separator_checker(&arg[i], &j) > 0)
				return (258);
			i += j;
		}
		quote = is_quote(arg[i]);
		if (arg[i + 1] == '\0' && quote > 0)
			return (syntx_error(recognize_quote(quote)), 258);
		else if (arg[i + 1] != '\0')
			i++;
		while (arg[i] && quote != is_quote(arg[i]))
			i++;
		if (arg[i] == '\0' && quote != is_quote(arg[i]))
			return (syntx_error(recognize_quote(quote)), 258);
	}
	return (0);
}


/*	separator_checker v_2 */

// int	separator_checker(char *arg, int *i)
// {
// 	char	**sep;
// 	char	*ret;
// 	int		sp_id;
// 	int		j;

// 	sp_id = 0;
// 	j = -1;
// 	sep = create_separator();
// 	while (arg[++j] && is_quote(arg[j]) == 0)
// 	{
// 		ret = find_separator(sep, &arg[j], &sp_id);
// 		if (ret)
// 			break ;
// 	}
// 	if (j == 0 && sp_id > 3 && sp_id != 8)
// 		return (syntx_error(sep[sp_id]), 1);
// 	if (ret && !arg[j + ft_arg_len(sep[sp_id])])
// 		return (syntx_error("newline"), 1);
// 	if (arg[j + ft_arg_len(sep[sp_id])])
// 		j += ft_arg_len(sep[sp_id]);
// 	while (arg[j] && arg[j] == ' ')
// 		j++;
// 	if (ret && !arg[j])
// 		return (syntx_error("newline"), 1);
// 	ret = find_separator(sep, &arg[j], &sp_id);
// 	if ((sp_id < 4 || sp_id == 8)&& !arg[j + ft_arg_len(sep[sp_id])])
// 	{
// 		printf("here\n");
// 		j += ft_arg_len(sep[sp_id]);
// 		if (!arg[j + 1])
// 			return (syntx_error("newline"), 1);	
// 	}
// 	// 	return (syntx_error("newline"), 1);
// 	// printf("value is: %s\n", &arg[j]);
// 	// if (ret)
// 	// 	return (syntx_error(sep[sp_id]), 1);
// 	return (((*i) = j), 0);
// }