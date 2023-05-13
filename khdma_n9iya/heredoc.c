/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:29:14 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/11 13:40:29 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlenn(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char		*p;
	size_t		lens1;
	size_t		lens2;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	lens1 = ft_strlenn(s1);
	lens2 = ft_strlenn(s2);
	p = malloc(sizeof(char) * ((lens1 + lens2) + 1));
	if (!p)
		return (NULL);
	while (s1 && s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
		p[i++] = s2[j++];
	p[i] = '\0';
	free(s1);
	return (p);
}

char	*ft_strchrrida(char *str, char c)
{
	int		i;
	int		count;
	char	*new;

	count = 0;
	i = 0;
	while (str[count] && str[count] != c)
		count++;
	if (str[count] == '\0' || (str[count] == c && str[count + 1] == '\0'))
		return (NULL);
	new = malloc(sizeof(char) * (ft_strlenn(str) - count) + 1);
	if (!new)
		return (NULL);
	count += 1;
	while (str[count])
		new[i++] = str[count++];
	new[i] = '\0';
	return (new);
}

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
	char	buf[BUFFER_SIZE + 1];

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

// int	her_is_here(char *str)
// {
// 	int	i;
// 	i = 0;
// 	while(str[i])
// 	{
// 		if (str[i] == '<' && str[i + 1] == '<')
// 		{
// 			if (4)
// 		}
// 	}
// }
// int	count_her(char *str)
// {
// 	int	i;
// 	i = 0;

// 	while(str[i])
// 	{
// 		if ()
// 	}
// }
// int main(void)
// {
// 	printf("just test herdoc\n");
// 	return (0);
// }


// void	print_error(char *msg, char *arg, int status)
// {
// 	char	*error_msg;

// 	if (msg && !arg)
// 		ft_putstr_fd(msg, 2);
// 	else if (!msg && !arg)
// 	{
// 		error_msg = ft_strjoin("minishell: ", strerror(errno));
// 		ft_putstr_fd(error_msg, 2);
// 		ft_putchar_fd('\n', 2);
// 		free (error_msg);
// 	}
// 	else
// 	{
// 		arg = ft_strjoin("minishell: ", arg);
// 		error_msg = ft_strjoin(arg, msg);
// 		ft_putstr_fd(error_msg, 2);
// 		free (arg);
// 		free (error_msg);
// 	}
// 	if (status != -1)
// 		exit(status);
// }

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((((unsigned char *)s1)[i] || ((unsigned char *)s2)[i]) && i < n)
	{
		if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (write (fd, &s[i], 1) == -1)
			printf("Error in write inside ft_putstr_fd\n");
		i++;
	}
}

static void	write_to_pipe(int fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (ft_strncmp(line, delimiter, ft_strlenn(line) - 1) == 0)
			break ;
		ft_putstr_fd(line, fd);
		// printf("here\n");
		free(line);
	}
	free(line);
}

void	here_doc(char *delimiter)
{
	int		fd;
	// int		fd[2];
	// pid_t	pid;
	(void) delimiter;
	// if (pipe(fd) == -1)
	// 	printf("Error in pipe\n");
	// pid = fork();
	// if (pid == -1)
	// 	print_error(NULL, NULL, 1);
	// if (pid == 0)
	// {
	fd = open(".testing", O_CREAT | O_RDWR | O_APPEND, 0777);
	
	// close (fd[0]);
	// int i = 0;
	// while (1)
	// {
	// 	ft_putstr_fd("test", fd[1]);
	// 	// printf("here\n");
	// 	// if (i == 10)
	// 	// 	break;
	// 	i++;
	// }
	
	// dup2(fd[0], 0);
		
		// close (fd[0]);
		char *args[] = {"/bin/cat", "-n", NULL};
		write_to_pipe(fd, delimiter);
		// read(fd, buffer, 3);
		// printf("%s", buffer);
		close (fd);
-		char *str = get_next_line(fd);
		printf("%s", str);
		// exit(1);
		ft_putstr_fd(str, 0);
		// write(0, buffer, ft_strlenn(buffer));
		// close(fd);
		execve("/bin/cat", args, NULL);
		// write_to_pipe(fd[1], delimiter);
		// printf("test from last\n");
		// close (fd[1]);
		// exit(0);
	// }
	// if (close (fd[1]) == -1 || dup2(fd[0], STDIN_FILENO) == -1 || \
	// close (fd[0]) == -1)
	// 	print_error(NULL, NULL, 1);
	// waitpid(pid, NULL, 0);
}

int main(int ac, char **av)
{
	if (ac == 2)
		here_doc(av[1]);

	return (0);
}