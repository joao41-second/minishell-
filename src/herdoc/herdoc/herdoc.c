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
	printf("sig %d\n",sig);
    if (sig == SIGINT)
	{
	
		rl_replace_line("", 0);
		rl_on_new_line();
		//rl_redisplay();
		ft_free_all(NULL);
		exit(sig+128);
	}

}

void herdoc(t_minis *mini,int set,char *end)
{
	pid_t pid;
	char *line; 

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
		signal(SIGUSR1, handle_signal);
		if(end != NULL)
		{
			printf("sou filho \n");
			signal(SIGINT, handle_signal);

			line = readline("herdoc:");

			get_signal(1);
			while(ft_strncmp(line, end, ft_strlen(end) + 15) != 0)
			{
				free(line);
				line = readline("herdoc:");
				if(get_signal(0) == 2)
				{
					free(line);
					ft_exit(mini);
				}
			}
			free(line);
		}
		else
		 ft_putstr_fd("error \n",2);
		ft_exit(mini);
	}
	else 
	{
		usleep(1);
		printf("main a espera\n");
		wait(NULL);
		server();
		printf("end\n");
	}
}
