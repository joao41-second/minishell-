/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_warnings.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:50:27 by rpires-c          #+#    #+#             */
/*   Updated: 2024/11/18 17:04:31 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fork_error(void)
{
	perror("Error creating child process");
	ft_exit_end(EXIT_FAILURE);
}

void	pipe_error(void)
{
	perror("Error creating the pipe");
	ft_exit_end(EXIT_FAILURE);
}

void	open_file_error(void)
{
	perror("Error opening the file");
	ft_exit_end(EXIT_FAILURE);
}

void	no_path_error(char *cmd)
{
	int	i;
	struct stat file_status;

	i = 0;
	if (cmd[0]=='.' && cmd[1] != '/')
	{
		 ft_print_error(cmd,"",REC_FILE,"bash");
		 ft_exit_end(127);
	}
	if ((cmd[0]=='.' && cmd[1] == '/') || cmd[1] == '/')
	{
		lstat(ft_split(cmd,' ')[0],&file_status);
		if(S_ISREG(file_status.st_mode))
			ft_print_error(cmd,"",REC_FILE,"bash");
		if(S_ISDIR(file_status.st_mode) == 1)
		{
			ft_print_error("",cmd, DIR,"bash");
			ft_exit_end(126); 
		}
		
		ft_exit_end(127);
	}

	while (cmd[i])
	{
		write(2, &cmd[i], 1);
		i++;
	}
// trabalha aqui

			ft_print_error("",cmd, NOT_COMAND,"bash");

	ft_exit_end(127);
}

void	command_error(void)
{
	perror("Error executing the command");
	ft_exit_end(EXIT_FAILURE);
}
