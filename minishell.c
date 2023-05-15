/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:20:11 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/15 14:38:06 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	*fill_with_nonpr_char(char *str)
{
	int	i;
	int	dq;
	int	sq;
	char *output;

	dq = 0;
	sq = 0;
	i = 0;
	output = NULL;
	while (str[i])
	{
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
		else if (str[i] && char_in_string(str[i], "|<>*&") != -1 && sq == 0 && dq == 0)
		{
			output = join_to_str(output, '\x07');
			output = join_to_str(output, str[i]);
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
			output = join_to_str(output, str[i]);
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
	char	**split1;
	int		i;
	char	*output;

	output = NULL;
	while (1)
	{
		read_line = readline("minishell ~ ");
		if (read_line[0] != 0)
			add_history(read_line);
		output = fill_with_nonpr_char(read_line);
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

