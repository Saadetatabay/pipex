/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satabay <satabay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:31:58 by satabay           #+#    #+#             */
/*   Updated: 2025/09/10 13:04:56 by satabay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



// <infile ls -l | wc -l > outfile
// ./a.out infile "ls -l" "wc -l" outfile

#include "pipex.h"

void first_process(char *argv[], char *env[], int fd[])
{
	char	**arg;
	int		infile_fd;
	
	infile_fd = open(argv[1], O_RDONLY);
	if (infile_fd < 0)
		return;
	arg = ft_split(argv[2]," ");
	dup2(infile_fd, 0);
	dup2(fd[1], 1);
	close(fd[0]);
	execve(find_path(arg[0]),arg,env);
}

void sec_process(char *argv[], char *env[], int fd[])
{
	char	**arg;
	int		outfile_fd;

	outfile_fd = open(argv[4], O_WRONLY | O_CREAT);
	if (outfile_fd < 0)
		return;
	arg = ft_split(argv[3]," ");
	dup2(fd[0], 0);
	dup2(outfile_fd, 1);
	close(fd[1]);
	execve(find_path(arg[0]), arg, env);
}

int main(int argc, char *argv[], char *env[])
{
    int	fd[2];
	int	pid1;
	int	pid2;
	
	if (pipe(fd) == -1)
		return;
	pid1 = fork();
	if (pid1 == 0)
		first_process(argv,env,fd);
	pid2 = fork();
	if (pid2 == 0)
		sec_process(argv,env,fd);
	waitpid(pid1, NULL,0);
	waitpid(pid2, NULL,0);
	close(fd[0]);
	close(fd[1]);
}