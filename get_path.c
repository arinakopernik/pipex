/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 15:05:10 by lbrianna          #+#    #+#             */
/*   Updated: 2022/03/10 12:17:12 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**find_path(char **envp)
{
	char	**path;
	int		a;

	a = 0;
	path = NULL;
	while (envp[a])
	{
		if (ft_strncmp(envp[a], "PATH=", 5) == 0)
		{
			path = ft_split(envp[a], ':');
			break ;
		}
		a++;
	}
	if (path == NULL)
	{
		perror("No PATH");
		exit(1);
	}
	return (path);
}

char	*get_path(char **cmd, char **envp)
{
	int		a;
	char	**path;
	char	*directory;
	char	*command;

	a = 0;
	path = find_path(envp);
	while (path[a])
	{
		if (cmd[0][0] != '/')
		{
			directory = ft_strjoin(path[a], "/");
			command = ft_strjoin(directory, cmd[0]);
			free(directory);
		}
		else
			command = cmd[0];
		if (!(access(command, F_OK)))
			return (command);
		if (cmd[0][0] != '/')
			free(command);
		a++;
	}
	free_arr(path);
	return (NULL);
}

void	do_perror(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}
