/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:20:11 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/15 19:07:58 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_separator(char **sep, char *str)
{
	int		sp_id;
	int		j;
	char	*output;

	j = 0;
	output = NULL;
	sp_id = -1;
	while (sep[j])
	{
		output = ft_strnstr(str, sep[j], ft_strlen(sep[j]));
		if (output != NULL)
			break ;
		j++;
	}
	if (output)
		sp_id = j;
	return (sp_id);
}

int	str_in_string(char *str)
{
	int i;
	int	sp_id;
	char **sp;

	i = 0;
	sp = ft_split(">> << || && > < | *", ' ');
	sp_id = find_separator(sp, &str[i]);
	free_double_ptr(sp);
	return (sp_id);
}

char	*fill_with_nonpr_char(char *str, char **split)
{
	int	i;
	int	dq;
	int	sq;
	char *output;
	int sp_id;

	dq = 0;
	sq = 0;
	i = 0;
	output = NULL;
	while (str[i])
	{
		sp_id = str_in_string(&str[i]);
		if (str[i] && str[i] == '"' && sq == 0 && dq == 0)
		{
			output = join_to_str(output, str[i]);
			dq = 1;
		}
		else if (str[i] && str[i] == '\'' && sq == 0 && dq == 0)
		{
			output = join_to_str(output, str[i]);
			sq = 1;
		}
		else if (str[i] && sp_id != -1 && sq == 0 && dq == 0)
		{
			output = ft_strjoin(output, split[sp_id]);
			i += ft_strlen(split[sp_id]) - 1;
			output = join_to_str(output, '\x07');
		}
		else if (str[i] && str[i] == '"' && sq == 0 && dq == 1)
		{
			dq = 0;
			output = join_to_str(output, str[i]);
			output = join_to_str(output, '\x07');
		}
		else if (str[i] && str[i] == '\'' && sq == 1 && dq == 0)
		{
			sq = 0;
			output = join_to_str(output, str[i]);
			output = join_to_str(output, '\x07');
		}
		else if (str[i] && str[i] == '\t' && sq == 0 && dq == 0)
			output = join_to_str(output, str[i]);
		else if (str[i] && str[i] == ' ' && sq == 0 && dq == 0)
		{
			while (str[i] && str[i] == ' ')
				i++;
			output = join_to_str(output, '\x07');
			output = join_to_str(output, str[i]);
			if (str[i] == '"')
				dq = 1;
			if (str[i] == '\'')
				sq = 1;
		}
		else
		{
			output = join_to_str(output, str[i]);
			if (str[i + 1] && str_in_string(&str[i + 1]) != -1)
				output = join_to_str(output, '\x07');
		}
		i++;
	}
	return (output);
}

void	free_tokens(t_tokens *tokens)
{
	t_tokens	*tmp;
	t_tokens	*tmp2;

	tmp = tokens;
	while (tmp)
	{
		tmp2 = tmp->next;
		free (tmp->str);
		free (tmp);
		tmp = tmp2;
	}
}

int main(void)
{
	char	*read_line;
	char	**split;
	char	**split1;
	
	int		i;
	char	*output;
	output = NULL;
	split = ft_split(">> << || && > < | * ( )", ' ');
	while (1)
	{
		read_line = readline("minishell ~ ");
		if (read_line[0] != 0)
			add_history(read_line);
		output = fill_with_nonpr_char(read_line, split);
		split1 = ft_split(output, '\x07');
		i = 0;
		while (split1[i])
		{
			printf("%s\n", split1[i]);
			i++;
		}
		free_double_ptr(split1);
	}
	return (0);
}



// char_in_string(&str[i], "|<>*&")


// char	**create_sp(void)
// {
// 	if (BONUS == 0)
// 		return (ft_split(">> << > < |", ' '));
// 	return (ft_split(">> << || && > < | * ( )", ' '));
// }


// char	*find_separator(char **sep, char *str, int *sp)
// {
// 	char	*output;
// 	int		j;

// 	j = 0;
// 	output = NULL;
// 	while (sep[j])
// 	{
// 		output = ft_strnstr(str, sep[j], ft_strlen(sep[j]));
// 		if (output != NULL)
// 			break ;
// 		j++;
// 	}
// 	(*sp) = j;
// 	return (output);
// }


// int main()
// {
// 	while (not_spetial_char)
// 	{
// 		skip_characters
// 	}
	
// 	char **sp = ft_split(">> << || && > < | * ( )", ' ');
// 	[">>", "<<", "||"...]
// 	find_separator(sp, &str[i], &sp_id);
// 	sp[sp_id];
// }