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
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>


void handle_signal(int sig)
{

	get_signal(sig);

    if (sig == SIGINT)
	{
		ft_printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		//rl_redisplay();
		ft_free_all(NULL);
		exit(sig+128);
	}

}

void herdoc_son_proceed(t_minis *mini, char*end)
{
	char *line;
	signal(SIGUSR1, handle_signal);
	if(end != NULL)
	{
		printf("sou filho \n");
		signal(SIGINT, handle_signal);
		line = readline("herdoc:");
		signal(SIGINT, handle_signal);
		get_signal(1);
		while(ft_strncmp(line, end, ft_strlen(end) + 15) != 0)
		{
			free(line);
			line = readline("herdoc:");
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

	(void)mini;
	(void)set;
	(void)end;
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
		printf("main a espera\n");
		wait(NULL);
	}
}
