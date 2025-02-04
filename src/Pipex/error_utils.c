/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rui <rui@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 22:00:32 by rui               #+#    #+#             */
/*   Updated: 2025/02/03 22:00:54 by rui              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fork_error(void)
{
	perror ("Error creating child process");
	ft_exit_end (EXIT_FAILURE);
}

void	pipe_error(void)
{
	perror ("Error creating the pipe");
	ft_exit_end (EXIT_FAILURE);
}

void	open_file_error(void)
{
	perror ("Error opening the file");
	ft_exit_end (EXIT_FAILURE);
}

void	command_error(void)
{
	ft_exit_end(EXIT_FAILURE);
}
