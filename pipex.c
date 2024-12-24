/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsebasti <rsebasti@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 20:31:06 by rsebasti          #+#    #+#             */
/*   Updated: 2024/12/22 10:31:05 by rsebasti         ###   ########.fr       */
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

void	ft_exec(char *cmd, int fd1, int fd2, char **env)
{
	char		**splited_cmd;
	char		*path;

	if (dup2(fd1, STDIN_FILENO) == -1 || dup2(fd2, STDOUT_FILENO) == -1)
		perror("Error ");
	close(fd1);
	close(fd2);
	splited_cmd = ft_split(cmd, ' ');
	path = search_path(env, splited_cmd[0], cmd);
	execve(path, splited_cmd, env);
	perror("Error ");
	free(path);
	killsplit(splited_cmd);
	exit(EXIT_FAILURE);
}

pid_t	ft_pipe(int fd1, int fd2, char **argv, char **env)
{
	int		pipe_fd[2];
	pid_t	pid[2];

	if (pipe(pipe_fd) == -1)
		return (-1);
	pid[0] = fork();
	if (pid[0] == -1)
		return (-1);
	if (pid[0] == 0)
	{
		close(pipe_fd[0]);
		ft_exec(argv[2], fd1, pipe_fd[1], env);
	}
	pid[1] = fork();
	if (pid[1] == -1)
		return (-1);
	if (pid[1] == 0)
	{
		close(pipe_fd[1]);
		ft_exec(argv[3], pipe_fd[0], fd2, env);
	}
	fd_killer(fd1, fd2, pipe_fd[0], pipe_fd[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	int	fd1;
	int	fd2;

	if (argc != 5)
	{
		write(2, "Usage: pipex <FILE> <COMMAND> <COMMAND> <FILE>\n", 47);
		exit(EXIT_FAILURE);
	}
	fd1 = open(argv[1], O_RDONLY);
	if (fd1 == -1)
	{
		perror("Error ");
		exit(EXIT_FAILURE);
	}
	fd2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd2 == -1)
	{
		perror("Error ");
		exit(EXIT_FAILURE);
	}
	ft_pipe(fd1, fd2, argv, env);
	close(fd1);
	close(fd2);
}
