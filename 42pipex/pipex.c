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

char	*find_path(char *arg, char *env[])
{
	int		i;
	char	*ret;
	char	**envs;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			envs = ft_split(env[i] + 5, ':');
			if (!envs)
				return (NULL);
			ret = accesible(envs, arg);
			if (ret)
				return (ret);
		}
		i++;
	}
	return (NULL);
}

char	*accesible(char	**envs, char *arg)
{
	int		j;
	char	*temp;
	char	*acces_path;

	j = 0;
	while (envs[j])
	{
		temp = ft_strjoin(envs[j], "/");
		if (!temp)
			break ;
		acces_path = ft_strjoin(temp, arg);
		free(temp);
		if (!acces_path)
			break ;
		if (access(acces_path, X_OK) == 0)
		{
			free_splitt(envs);
			return (acces_path);
		}
		free(acces_path);
		j++;
	}
	free_splitt(envs);
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
		exit(1);
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

void	children(char *argv[], char *env[], int fd[])
{
	int	pid1;
	int	pid2;

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
