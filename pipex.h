/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 13:18:21 by lbrianna          #+#    #+#             */
/*   Updated: 2022/03/10 12:16:07 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

int		main(int argc, char **argv, char **envp);
void	create_child(char **argv, char **envp, int *fd);
void	child_process1(int *fd, char **argv, char **envp);
void	child_process2(int *fd, char **argv, char **envp);

char	*get_path(char **cmd, char **envp);
char	**find_path(char **envp);
void	do_perror(char *str);

char	**ft_split(char const *s, char c);
void	free_arr(char **arr);
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char	*str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);

int		open_file(char *arg, int f);
int		get_next_line(char **line);

int		main(int argc, char **argv, char **envp);
void	pipex(int argc, char **argv, char **envp);
void	here_doc(char *limiter, int *fd);
int		get_next_line(char **line);
int		open_file(char *arg, int f);

#endif