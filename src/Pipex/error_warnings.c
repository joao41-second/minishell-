/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_warnings.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:50:27 by rpires-c          #+#    #+#             */
/*   Updated: 2025/01/28 17:37:13 by rpires-c         ###   ########.fr       */
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

void check_execute_permissions(char *file_path)
{
    struct stat file_stat;

    if (stat(file_path, &file_stat) == -1)
    {
        ft_print_error(file_path, "", NOT_ACCESS, "");
        ft_exit_end(126);
    }
    if (!S_ISREG(file_stat.st_mode))
    {
        if (S_ISDIR(file_stat.st_mode))
            ft_print_error(file_path, "", DIR, "");
        else
            ft_print_error(file_path, "", NOT_REG_FILE, "");
        ft_exit_end(126);
    }
    if (access(file_path, X_OK) == -1)
    {
        ft_print_error(file_path, "", NOT_PERM, "");
        ft_exit_end(126);
    }
}

void no_path_error(char *cmd)
{
	struct stat file_stat;

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

void	command_error(void)
{ 
	ft_exit_end(EXIT_FAILURE);
}
