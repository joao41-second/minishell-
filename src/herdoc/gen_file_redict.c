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
#include <unistd.h>

void	change_file(t_minis *mini, int set, char sete)
{
	static int file_origin;
	static int file_new;
	(void)mini;
	if (set == 0)
	{

		file_origin = dup(1);
		if(sete == '>')
			file_new =  redirect_for_new_file(mini);
			//	file_new = open("ok.t", O_CREAT,777);
		dup2(file_new,STDOUT_FILENO);
		ft_putstr_fd("oal",  file_new);
	}
	else if (set == 1)
	{
		if(sete == '>')
			close(1);

		dup2(file_origin,1);
		//close(file_origin);
			// fd = file_origin excute the redicion expecific
	}

}

