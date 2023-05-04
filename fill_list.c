/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:32:16 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/03 16:32:42 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*command(char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	char *cmd;
	while (line[i] && line[i] != ' ')
		i++;
	cmd = malloc(sizeof(char) * i + 1);
	if (!cmd)
		return (NULL);
	while (j < i)
	{
		cmd[j] = line[j];
		j++;
	}
	cmd[j] = '\0';
	return (cmd);
}

void	*option(char *line)
{
	int		i;
	int		tmp;
	int		j;
	int		len;
	char	*opt;

	i = 0;
	len = 0;
	j = 0;
	while (line[i] && line[i] != '-')
		i++;
	if (line[i] == '-')
	{
		tmp = i;
		while(line[i] && line[i++] != ' ')
			len++;
		opt = malloc(sizeof(char) * len + 1);
		if (!opt)
			return (NULL);
		while (j < len)
			opt[j++] = line[tmp++];
		opt[j] = '\0';
		return (opt);
	}
	return (NULL);
}

void	*argument(char *line)
{
	int		i;
	int		j;
	int		tmp;
	int		len;
	char	*arg;

	i = 0;
	len = 0;
	j = 0;
	while (line[i] && line[i] != ' ')
		i++;
	if (line[i] == ' ')
	{
		while (line[i] && line[i] == ' ')
			i++;
		if (line[i] && line[i] != ' ')
		{
			if (line[i] != '>' && line[i] != '<' && line[i] != '-' && line[i] != '|' && line[i] != '$')
				{
					tmp = i;
					while (line[i] && line[i++] != ' ')
						len++;
					arg = malloc(sizeof(char) * len + 1);
					if (!arg)
						return (NULL);
					while (j < len)
						arg[j++] = line[tmp++];
					arg[j] = '\0';
					return (arg);
				}
		}
	}
	return (NULL);
}