/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_file_redict.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:27:15 by jperpct           #+#    #+#             */
/*   Updated: 2025/01/02 16:49:00 by jperpct          ###   ########.fr       */
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

static void	redirect(t_minis *mini, char sete, int *file_new, t_token *name)
{
	if (sete == '>')
		*file_new = redirect_for_new_file(mini, name);
	if (sete == 'n')
		*file_new = redirect_for_add_file(mini, name);
}

void	change_file(t_minis *mini, int set, char sete, t_token *name)
{
	static int	file_origin = 0;
	static int	file_new = 0;
	static int	save[2];

	if (set == 0)
	{
		redirect(mini, sete, &file_new, name);
		if (file_new == -1)
		{
			perror("bash");
			mini->comand = 1;
			mini->exit_code_error = 1;
			return ;
		}
		pipe(save);
		file_origin = dup(1);
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
