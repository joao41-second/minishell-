/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_file_redict.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:27:15 by jperpct           #+#    #+#             */
/*   Updated: 2024/11/12 12:04:01 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
#include <unistd.h>

void	change_file(t_minis *mini, int set, char sete)
{
	static int file_origin;
	static int file_new;
	static int save[2];
	(void)mini;
	if (set == 0)
	{
		pipe(save);
		file_origin = dup(1);
		if(sete == '>')
			file_new =  redirect_for_new_file(mini);
		if(sete == 'n')
			file_new  = redirect_for_add_file(mini);
		if(file_new == -1)
		{
			perror("raiva");
			file_new = save[0];
		}

		dup2(file_new,STDOUT_FILENO);
	}
	else if (set == 1)
	{
		if(sete == '>' || sete == 'n')
			close(1);
		dup2(file_origin,1);
		close(file_origin);
		close(save[0]);
		close(save[1]); 
	}
}

