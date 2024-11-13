/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:09:31 by jperpct           #+#    #+#             */
/*   Updated: 2024/11/13 10:59:23 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

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
		printf("sou filho \n");
		line = readline("herdoc:");
		while(ft_strncmp(line, end, ft_strlen(end) + 15) != 0)
		{
			free(line);
			line = readline("herdoc:");
		}
	free(line);
	}
	else 
	{
		printf("main a espera\n");
		wait(NULL);
		printf("end\n");
	}
}
