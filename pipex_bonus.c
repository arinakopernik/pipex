/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 16:10:27 by lbrianna          #+#    #+#             */
/*   Updated: 2022/03/10 12:10:41 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	make_cmd(char *arg, char **envp)
{
	char	**cmd;
	char	*path;

	if (!(*arg))
		return ;
	cmd = ft_split(arg, ' ');
	if (!cmd[0])
	{
		ft_putstr_fd("Command not found", 2);
		exit(127);
	}
	path = get_path(cmd, envp);
	if ((execve(path, cmd, envp) == -1))
	{
		ft_putstr_fd("Command not found", 2);
		exit(127);
	}
	free_arr(cmd);
}

static void	child_process(char *arg, char **envp)
{
	int	pid;
	int	fd[2];

	if (pipe(fd) == -1)
		do_perror("Couldn't pipe");
	pid = fork();
	if (pid == -1)
		do_perror("Fork error");
	if (pid == 0)
	{
		close (fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		make_cmd(arg, envp);
	}
	else
	{
		close (fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		waitpid(pid, NULL, 0);
	}
}

static void	ft_here_doc(char **argv, int argc)
{
	int		fd[2];
	int		rd;

	if (argc < 6)
		ft_putstr_fd("Wrong number of arguments", 2);
	if (pipe(fd) == -1)
		do_perror("Could not pipe");
	rd = fork();
	if (rd == -1)
		do_perror("Fork error");
	if (rd == 0)
		here_doc(argv[2], fd);
	else
	{
		close (fd[1]);
		dup2(fd[0], STDIN_FILENO);
		wait(NULL);
	}
}

void	pipex(int argc, char **argv, char **envp)
{
	int	infile;
	int	outfile;
	int	argument;

	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		argument = 3;
		ft_here_doc(argv, argc);
		outfile = open_file(argv[argc - 1], 0);
	}
	else
	{
		argument = 2;
		infile = open_file(argv[1], 2);
		outfile = open_file(argv[argc - 1], 1);
		dup2(infile, STDIN_FILENO);
	}
	while (argument < argc - 2)
		child_process(argv[argument++], envp);
	dup2(outfile, STDOUT_FILENO);
	make_cmd(argv[argc - 2], envp);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc >= 5)
		pipex(argc, argv, envp);
	ft_putstr_fd("Wrong number of commands\n", 1);
	exit(0);
}
