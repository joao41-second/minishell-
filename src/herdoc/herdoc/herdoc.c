/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rui <rui@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:09:31 by jperpct           #+#    #+#             */
/*   Updated: 2025/01/30 16:28:57 by rui              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

static void	handle_signal(int sig)
{
	get_signal(sig + 128);
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		ft_free_all(NULL);
		exit(sig + 128);
	}
}

static void	loop_heradoc(char *line, int fd, char *end, t_minis *mini)
{
	char	*new_line;

	new_line = NULL;
	while (ft_strncmp(line, end, ft_strlen(end) + 15) != 0)
	{
		if (line)
			free(line);
		line = readline(">");
		if (line == NULL)
		{
			ft_print_error_simple("","here-herdoc", "bas");
			ft_exit_end(0);
			line = NULL;
		}
		new_line = expand_heradoc(mini, line);
		ft_putstr_fd(new_line, fd);
		ft_putstr_fd("\n", fd);
	}
	free(line);
}

static void	herdoc_son_proceed(t_minis *mini, char*end, int fd)
{
	char	*line;

	signal(SIGUSR1, handle_signal);
	if (end != NULL)
	{
		signal(SIGINT, handle_signal);
		if (get_signal(0) == 130)
			ft_exit_end(130);
		line = malloc(2 * sizeof(char));
		line[0] = '1';
		line[0] = '\0';
		if (line == NULL)
		{
			ft_exit_end(1);
		}
		mini->exit_code_error = 1;
		loop_heradoc(line, fd, end, mini);
	}
	else
		ft_putstr_fd("error \n", 2);
	ft_exit_end(0);
}

int	herdoc(t_minis *mini, int set, char *end)
{
	pid_t			pid;
	int				status;
	int				fd[2];
	struct rusage	usage;

	if (set != 0)
		return (1);
	pipe(fd);
	pid = fork();
	if (pid < 0)
		ft_putstr_fd("error \n", 2);
	else if (pid == 0)
		herdoc_son_proceed(mini, end, fd[1]);
	else
	{
		signal(SIGINT, SIG_IGN);
		wait4(pid,&status, 0, &usage);
		get_signal(WSTOPSIG(status));
	}
	close(fd[1]);
	return (fd[0]);
}
