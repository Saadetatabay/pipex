/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satabay <satabay@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:31:58 by satabay           #+#    #+#             */
/*   Updated: 2025/10/08 15:40:43 by satabay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_splitt(char	**splitted)
{
	int	i;

	i = 0;
	if (!splitted)
		return ;
	while (splitted[i])
	{
		free(splitted[i]);
		i++;
	}
	free(splitted);
}

char	*find_path(char *arg, char *env[])
{
	int		i;
	int		j;
	char	**paths;
	char	*path1;
	char	*path2;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			paths = ft_split(env[i] + 5, ':');
			j = 0;
			while (paths[j])
			{
				path1 = ft_strjoin(paths[j], "/");
				path2 = ft_strjoin(path1, arg);
				free(path1);
				if (access(path2, X_OK) == 0)
				{
					free_splitt(paths);
					return (path2);
				}
				free(path2);
				j++;
			}
			free_splitt(paths);
		}
		i++;
	}
	return (NULL);
}

void	first_process(char *argv[], char *env[], int fd[])
{
	char	**arg;
	char	*path;
	int		infile_fd;

	infile_fd = open(argv[1], O_RDONLY);
	if (infile_fd < 0)
		exit(1);
	arg = ft_split(argv[2], ' ');
	if (!arg)
		exit(1);
	path = find_path(arg[0], env);
	if (!path)
	{
		free_splitt(arg);
		exit(1);
	}
	dup2(infile_fd, 0);
	dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
	execve(path, arg, env);
	free_splitt(arg);
	free(path);
	exit(1);
}

void	sec_process(char *argv[], char *env[], int fd[])
{
	char	**arg;
	char	*path;
	int		outfile_fd;

	outfile_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd < 0)
		return ;
	arg = ft_split(argv[3], ' ');
	if (!arg)
		exit(1);
	path = find_path(arg[0], env);
	if (!path)
	{
		free_splitt(arg);
		exit(1);
	}
	dup2(fd[0], 0);
	dup2(outfile_fd, 1);
	close(fd[1]);
	close(fd[0]);
	execve(path, arg, env);
	free_splitt(arg);
	free(path);
	exit(1);
}

int	main(int argc, char *argv[], char *env[])
{
	int	fd[2];
	int	pid1;
	int	pid2;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			return (1);
		pid1 = fork();
		if (pid1 < 0)
			exit(1);
		if (pid1 == 0)
			first_process(argv, env, fd);
		pid2 = fork();
		if (pid2 < 0)
			exit(1);
		if (pid2 == 0)
			sec_process(argv, env, fd);
		close(fd[0]);
		close(fd[1]);
		waitpid(pid1, NULL, 0);
		waitpid(pid2, NULL, 0);
	}
	else
	{
		printf("enter valid arg");
		return (1);
	}
}
