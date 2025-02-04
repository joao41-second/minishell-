/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prefix_user.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 18:22:15 by rpires-c          #+#    #+#             */
/*   Updated: 2025/02/04 14:24:08 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_fd(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

void	prefix_child_process(int *fd)
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	execve("/usr/bin/whoami", (char *[]){"whoami", NULL}, NULL);
	exit(EXIT_SUCCESS);
}

void	prefix_parent_process(int *fd, char **user)
{
	wait(NULL);
	close(fd[1]);
	*user = get_next_line(fd[0]);
	close(fd[0]);
}

char	*process_user(char *user)
{
	int		i;
	char	*final_user;

	i = ft_strlen(user);
	final_user = ft_strndup(user, --i);
	return (final_user);
}

char	*get_user(void)
{
	int		fd[2];
	pid_t	pid;
	char	*user;
	char	*final_user;

	final_user = NULL;
	if (pipe(fd) == -1)
		return ("");
	pid = fork();
	if (pid == -1)
		return ("");
	if (pid == 0)
		prefix_child_process(fd);
	else
	{
		prefix_parent_process(fd, &user);
		final_user = process_user(user);
		free(user);
	}
	return (final_user);
}
