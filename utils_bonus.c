/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 13:37:20 by lbrianna          #+#    #+#             */
/*   Updated: 2022/03/10 12:00:05 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_next_line(char **line)
{
	char	*buffer;
	int		bwr;
	int		i;
	char	ch;

	i = 0;
	bwr = 0;
	buffer = (char *)malloc(10000);
	if (!buffer)
		return (-1);
	bwr = read(0, &ch, 1);
	while (bwr && ch != '\n' && ch != '\0')
	{
		if (ch != '\n' && ch != '\0')
			buffer[i] = ch;
		i++;
		bwr = read(0, &ch, 1);
	}
	buffer[i] = '\n';
	buffer[++i] = '\0';
	*line = buffer;
	free(buffer);
	return (bwr);
}

void	here_doc(char *limiter, int *fd)
{
	char	*line;

	close(fd[0]);
	while (get_next_line(&line))
	{
		if ((ft_strncmp(limiter, line, ft_strlen(limiter)) == 0))
			exit(0);
		if (write(fd[1], line, ft_strlen(line)) == -1)
			perror("Write error");
	}
	close(fd[1]);
}

int	open_file(char *arg, int f)
{
	int	openfile;

	openfile = 0;
	if (f == 0)
		openfile = open(arg, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (f == 1)
		openfile = open(arg, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (f == 2)
		openfile = open(arg, O_RDONLY);
	if (openfile == -1)
	{
		perror("Open error");
		exit(EXIT_FAILURE);
	}
	return (openfile);
}
