/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 15:45:32 by lbrianna          #+#    #+#             */
/*   Updated: 2022/02/25 16:47:47 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_arr(char **arr)
{
	int	a;

	a = 0;
	while (arr[a])
		free(arr[a++]);
	free(arr);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	a;

	a = 0;
	if (!s)
		return ;
	if (fd < 0)
		return ;
	while (s[a])
		a++;
	write(fd, s, a);
}

size_t	ft_strlen(const char	*str)
{
	int	a;

	a = 0;
	while (str[a] != '\0')
		a++;
	return (a);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	a;

	a = 0;
	while (a < n && s1[a] && s2[a])
	{
		if (s1[a] != s2[a])
			return (((unsigned char *)s1)[a] - ((unsigned char *)s2)[a]);
		a++;
	}
	if (a < n)
		return (((unsigned char *)s1)[a] - ((unsigned char *)s2)[a]);
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		a;
	int		b;
	char	*p;

	if (!s1)
		return (0);
	a = ft_strlen(s1);
	b = ft_strlen(s2);
	p = (char *)malloc((a + b + 1) * sizeof(char));
	if (p == 0)
		return (0);
	a = 0;
	b = 0;
	while (s1[a])
	{
		p[a] = s1[a];
		a++;
	}
	while (s2[b])
	{
		p[a + b] = s2[b];
		b++;
	}
	p[a + b] = '\0';
	return (p);
}
