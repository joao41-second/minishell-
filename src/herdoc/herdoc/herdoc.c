/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:09:31 by jperpct           #+#    #+#             */
/*   Updated: 2024/11/13 11:14:11 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/resource.h>

void handle_signal(int sig)
{
	get_signal(sig+128);
    if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		ft_free_all(NULL);
		exit(sig+128);
	}
}

char* expand_heradoc(t_minis *mini, char *str)
{
	char *ret;
	int i;
	

	i = -1;
	while (str[++i] != '\0')
	{
		if(str[i] == '$')
		{

		}
	}
	return "o";
}

void herdoc_son_proceed(t_minis *mini, char*end)
{
	char *line;
	signal(SIGUSR1, handle_signal);
	if(end != NULL)
	{
		signal(SIGINT, handle_signal);
		if(get_signal(0) == 130)
		{
			ft_exit(mini);
		}
		line = readline(">");
		mini->exit_code_error = 1;
		while(ft_strncmp(line, end, ft_strlen(end) + 15) != 0)
		{
			free(line);
			line = readline(">");
		}
		free(line);
	}
	else
		ft_putstr_fd("error \n",2);
	ft_exit(mini);
}


void herdoc(t_minis *mini,int set,char *end)
{
	pid_t pid;
	int status;
	struct rusage usage;
	if(set != 1)
		return;
	pid = fork();
	if(pid < 0)
		ft_putstr_fd("error \n", 2);
	else if (pid == 0)
	{
		herdoc_son_proceed(mini,end);
	}
	else 
	{
		signal(SIGINT, SIG_IGN);
		usleep(1);
		wait3(&status, 0, &usage);
		printf("signal %d \n",WSTOPSIG(status));
		if(WSTOPSIG(status) == 0)
		{
			mini->readline++;
			ft_putstr_fd("bash: warning: here-document at line ",2);
			ft_putnbr_fd(mini->readline, 2);
			ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
			ft_putstr_fd(end, 2 );
			ft_putstr_fd("')\n", 2);
		}
		get_signal(WSTOPSIG(status));

	}
}
