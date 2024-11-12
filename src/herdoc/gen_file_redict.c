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

void	change_file(t_minis *mini, int set)
{
	static int file_origin;
	static int file_new[2];
	if (set == 0)
	{
	 // delete file_new  create file_new clean copy fd=1 change fd =1 for fd = file_new
		if (file_new > 0)
			close(file_new);
		file_origin = dup(1);
		pipe(file_new);
		dup2(file_new[0],1);

	}
	else if (set == 1)
	{

		dup2(file_origin,1);
	// fd = file_origin excute the redicion expecific
	}

}

