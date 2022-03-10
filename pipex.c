/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 13:23:44 by lbrianna          #+#    #+#             */
/*   Updated: 2022/03/10 12:11:36 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process2(int *fd, char **argv, char **envp)
{
	char	**cmd2;
	int		outfile;

	outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (outfile < 0)
		do_perror("Could not make an outfile\n");
	dup2(outfile, 1);
	dup2(fd[0], 0);
	close(outfile);
	close(fd[1]);
	cmd2 = ft_split(argv[3], ' ');
	if (execve(get_path(cmd2, envp), cmd2, envp) == -1)
	{
		perror("Command not found");
		exit(127);
	}
}

void	child_process1(int *fd, char **argv, char **envp)
{
	char	**cmd1;
	int		infile;

	infile = open(argv[1], O_RDONLY);
	if (infile < 0)
		do_perror("Could not open file");
	dup2(fd[1], 1);
	dup2(infile, 0);
	close(fd[0]);
	close(infile);
	cmd1 = ft_split(argv[2], ' ');
	if ((execve(get_path(cmd1, envp), cmd1, envp) == -1))
	{
		perror("Command not found");
		exit(127);
	}
}

void	create_child(char **argv, char **envp, int *fd)
{
	int	child1;
	int	child2;

	child1 = fork();
	if (child1 < 0)
		do_perror("Fork: ");
	if (child1 == 0)
		child_process1(fd, argv, envp);
	child2 = fork();
	if (child2 < 0)
		do_perror("Fork: ");
	if (child2 == 0)
		child_process2(fd, argv, envp);
	close(fd[0]);
	close(fd[1]);
}

int	main(int argc, char **argv, char **envp)
{
	int	fd[2];
	int	status;

	if (argc != 5)
	{
		ft_putstr_fd("Wrong number of commands\n", 2);
		return (1);
	}
	if (pipe(fd) == -1)
	{
		perror("Could not pipe");
		return (1);
	}
	create_child(argv, envp, fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(-1, &status, 0);
	return (0);
}
