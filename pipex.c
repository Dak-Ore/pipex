/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsebasti <rsebasti@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 20:31:06 by rsebasti          #+#    #+#             */
/*   Updated: 2024/12/09 06:01:11 by rsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	fd_killer(int fd1, int fd2, int fd3, int fd4)
{
	close(fd1);
	close(fd2);
	close(fd3);
	close(fd4);
}

void	ft_exec(char *cmd, int fd1, int fd2)
{
	static char	*arg[] = {"/bin/sh", "-c", NULL, NULL};

	if ((dup2(fd1, STDIN_FILENO) == -1))
		perror("Error dup2 input");
	if (dup2(fd2, STDOUT_FILENO) == -1)
		perror("Error dup2 ouput");
	close(fd1);
	close(fd2);
	arg[2] = cmd;
	execve("/bin/sh", arg, NULL);
	perror("Error invalid cmd");
	exit(EXIT_FAILURE);
}

pid_t	ft_pipe(int fd1, int fd2, char *cmd1, char *cmd2)
{
	int		pipe_fd[2];
	pid_t	pid[2];

	if (pipe(pipe_fd) == -1)
		return (perror("Error when creating pipe"), -1);
	pid[0] = fork();
	if (pid[0] == -1)
		return (perror("Error when creating children 1"), -1);
	if (pid[0] == 0)
	{
		close(pipe_fd[0]);
		ft_exec(cmd1, fd1, pipe_fd[1]);
	}
	pid[1] = fork();
	if (pid[1] == -1)
		return (perror("Error when creating children 2"), -1);
	if (pid[1] == 0)
	{
		close(pipe_fd[1]);
		ft_exec(cmd2, pipe_fd[0], fd2);
	}
	fd_killer(fd1, fd2, pipe_fd[0], pipe_fd[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	int		fd1;
	int		fd2;
	pid_t	pid;

	if (argc < 5)
	{
		write(2, "Usage: pipex <FILE> <COMMAND> <COMMAND> <FILE>\n", 47);
		exit(EXIT_FAILURE);
	}
	fd1 = open(argv[1], O_RDONLY);
	if (fd1 == -1)
	{
		perror("Error when opening file 1");
		exit(EXIT_FAILURE);
	}
	fd2 = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd2 == -1)
	{
		perror("Error when opening file 2");
		exit(EXIT_FAILURE);
	}
	pid = ft_pipe(fd1, fd2, argv[2], argv[3]);
	close(fd1);
	close(fd2);
	waitpid(pid, NULL, 0);
}
