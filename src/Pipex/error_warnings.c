/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_warnings.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rui <rui@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:50:27 by rpires-c          #+#    #+#             */
/*   Updated: 2025/02/03 22:02:29 by rui              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	chek_dir_(char *file_path, char *orig, int set)
{
	int			i;
	struct stat	file_stat;

	i = 0;
	stat (file_path, &file_stat);
	while (orig[0] != '\0' && orig[++i] != '\0')
	{
		if (orig[i] == '/')
		{
			if (set == TRUE)
				ft_print_error(file_path, orig, DIR, "");
			if (set == FALSE)
				ft_print_error(file_path, "", NOT_PERM, "");
			ft_exit_end(126);
		}
	}
	if (file_stat.st_mode & S_IXUSR && !S_ISDIR(file_stat.st_mode))
	{
		ft_print_error(file_path, "origin", NOT_PERM, "");
		ft_exit_end(126);
	}
	ft_print_error(file_path, orig, NOT_COMAND, "");
	ft_exit_end(127);
}

void	chek_comand_permicion( char *file_path)
{
	struct stat	file_stat;

	stat(file_path, &file_stat);
	if (file_stat.st_mode & S_IXUSR)
	{
		ft_print_error(file_path, "", NOT_PERM, "");
		ft_exit_end(126);
	}
}

void	check_execute_permissions(char *file_path, char *orig)
{
	struct stat	file_stat;

	if (stat(file_path, &file_stat) == -1)
	{
		ft_print_error(file_path, "", NOT_ACCESS, "");
		ft_exit_end(126);
	}
	if (!S_ISREG(file_stat.st_mode))
	{
		if (S_ISDIR(file_stat.st_mode))
			chek_dir_(file_path, orig, TRUE);
		else
			ft_print_error(file_path, "", NOT_REG_FILE, "");
		ft_exit_end(126);
	}
	if (access(file_path, X_OK) == -1)
		chek_dir_(file_path, orig, FALSE);
}

void	no_path_error(char *cmd)
{
	struct stat	file_stat;

	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
	{
		if (stat(cmd, &file_stat) == -1)
		{
			ft_print_error(cmd, "", NOT_FILE, "");
			ft_exit_end(127);
		}
		if (S_ISDIR(file_stat.st_mode))
		{
			ft_print_error(cmd, "", DIR, "");
			ft_exit_end(126);
		}
		ft_print_error(cmd, "", NOT_PERM, "");
		ft_exit_end(126);
	}
	ft_print_error(cmd, "", NOT_COMAND, "");
	ft_exit_end(127);
}
