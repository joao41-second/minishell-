/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rui <rui@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:02:47 by jperpct           #+#    #+#             */
/*   Updated: 2025/01/24 18:22:10 by rui              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void handle_pipe_fork(t_btree *node, t_minis *mini)
{
    int     fd[2];
    int     status;
    pid_t   pid;

    if (pipe(fd) == -1)
    {
        pipe_error();
    }
    pid = fork();
    if (pid == -1)
    {
        close(fd[0]);
        close(fd[1]);
        fork_error();
    }
    if (pid == 0)

	{
		if (node->right == NULL)
		{
			close(fd[0]);
			close(fd[1]);
			process_tree(node->left, mini);
			exit(0);
		}
		else
		{
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
			process_tree(node->left, mini);
			exit(0);
		}
    }
    else
{
    close(fd[1]);
    dup2(fd[0], STDIN_FILENO); 
    close(fd[0]);
    process_tree(node->right, mini);
    waitpid(pid, &status, 0);
}
}

int process_tree(t_btree *node, t_minis *mini)
{
    if (node && ft_strcmp(node->cmd, "|") == 0)
    {
        handle_pipe_fork(node, mini);
    }
    else if (node)
    {
		redirect_(node->redir,mini);
		execute(node->cmd, mini);
    }
	return (mini->exit_code_error);
}
