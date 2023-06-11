#include "../minishell.h"

// int	here_doc(char *delimiter)
// {
// 	char	*line;
// 	int		fd;

// 	unlink("/tmp/here_doc.txt");
// 	fd = open ("/tmp/here_doc.txt", O_CREAT|O_WRONLY|O_TRUNC, 0644);
// 	printf("value: %d\n", fd);
// 	if (fd == -1)
// 		return (print_error(NULL, NULL, -1), -1);
// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (ft_strcmp(line, delimiter) == 0)
// 			break ;
// 		ft_putstr_fd(line, fd);
// 		ft_putstr_fd("\n", fd);
// 		free(line);
// 	}
// 	free(line);
// 	printf("value: %d\n", fd);
// 	if (close (fd) != -1)
// 	{
// 		printf("here\n");
// 		return (print_error(NULL, NULL, -1), -1);
// 	}
// 	fd = open ("/tmp/here_doc.txt", O_RDONLY, 0644);
// 	if (fd == -1)
// 		return (print_error(NULL, NULL, -1), -1);
// 	return (fd);
// }

int here_doc(char *delimiter) {
    char *line;
    int fd;

    fd = open("/tmp/here_doc.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    printf("value: %d\n", fd);
    if (fd == -1)
        return (printf("Error opening file\n"), -1);
    while (1) {
        line = readline("> ");
        if (ft_strcmp(line, delimiter) == 0) {
            free(line);
            break;
        }
        ft_putstr_fd(line, fd);
        ft_putstr_fd("\n", fd);
        free(line);
    }
    printf("value: %d\n", fd);
    if (close(fd) == -1) {
        printf("Error closing file\n");
        return -1;
    }
    return fd;
}

int main()
{
	here_doc("eof");
	return (0);
}