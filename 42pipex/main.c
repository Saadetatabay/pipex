/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main .c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satabay <satabay@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:31:58 by satabay           #+#    #+#             */
/*   Updated: 2025/10/08 15:40:43 by satabay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *env[])
{
	int	fd[2];
	int	pid1;
	int	pid2;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			return (1);
		children(argv, env, fd);
	}
	else
	{
		printf("enter valid arg");
		return (1);
	}
}
