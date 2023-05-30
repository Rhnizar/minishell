/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 16:31:38 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/30 10:49:51 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	check_new_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static void	*read_line(int fd, char *line)
{
	int		i;
	char	*buf;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	i = 0;
	while (1)
	{
		i = read(fd, buf, BUFFER_SIZE);
		if (i <= 0)
			break ;
		buf[i] = '\0';
		line = ft_strjoin(line, buf);
		if (check_new_line(buf))
			break ;
	}
	free(buf);
	return (line);
}

static void	*read_line_exact(char *line)
{
	int		i;
	int		count;
	char	*lineex;

	count = 0;
	i = 0;
	while (line[count] && line[count] != '\n')
		count++;
	lineex = malloc(sizeof(char) * (count + 2));
	if (!lineex)
		return (NULL);
	while (line[i] && line[i] != '\n')
	{
		lineex[i] = line[i];
		i++;
	}
	if (line[i] == '\n')
	{
		lineex[i] = line[i];
		i++;
	}
	lineex[i] = '\0';
	return (lineex);
}

char	*get_next_line(int fd)
{
	char		*lineex;
	char static	*line1;
	char		*linefree;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	line1 = read_line(fd, line1);
	if (!line1)
		return (NULL);
	lineex = read_line_exact(line1);
	linefree = line1;
	line1 = ft_strchrrida(linefree, '\n');
	free(linefree);
	return (lineex);
}
