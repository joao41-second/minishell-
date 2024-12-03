/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_file_redict.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:27:15 by jperpct           #+#    #+#             */
/*   Updated: 2024/12/03 10:17:00 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_close_all(int fd1, int fd2, int fd3, int fd4)
{
	close(fd1);
	close(fd2);
	close(fd3);
	close(fd4);
}

static void	redirect(t_minis *mini, char sete, int *file_new)
{
	if (sete == '>')
		*file_new = redirect_for_new_file(mini);
	if (sete == 'n')
		*file_new = redirect_for_add_file(mini);
}

void	change_file(t_minis *mini, int set, char sete)
{
	static int	file_origin;
	static int	file_new;
	static int	save[2];

	if (set == 0)
	{
		pipe(save);
		file_origin = dup(1);
		redirect(mini, sete, &file_new);
		if (file_new == -1)
		{
			perror("raiva");
			file_new = save[0];
		}
		dup2(file_new, STDOUT_FILENO);
	}
	else if (set == 1)
	{
		if (sete == '>' || sete == 'n')
			close(1);
		dup2(file_origin, 1);
		ft_close_all(file_new, file_origin, save[0], save[1]);
	}
}
