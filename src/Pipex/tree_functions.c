/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rui <rui@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:02:47 by jperpct           #+#    #+#             */
/*   Updated: 2025/01/22 21:06:20 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void handle_pipe_fork(t_btree *node, t_minis *mini, int original_stdout)
{
    int     fd[2];
    int     status;
	int		save;
    pid_t   pid;
	
	status = 0;
    if (pipe(fd) == -1)
    {
        close(original_stdout);
        pipe_error();
    }
    pid = fork();
    if (pid == -1)
    {
        close(fd[0]);
        close(fd[1]);
        close(original_stdout);
        fork_error();
    }
    if (pid == 0)
    {
        if (node->right == NULL)
        {
            close(fd[0]);
            close(fd[1]);
            save = process_tree(node->left, mini, original_stdout);
            close(original_stdout);
            ft_exit_end(WSTOPSIG(status));
        }
        else
        {
            close(fd[0]);
            dup2(fd[1], STDOUT_FILENO);
            close(fd[1]);
            save = process_tree(node->left, mini, original_stdout);
            close(original_stdout);
            ft_exit_end(save);
        }
    }
    else
    {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        process_tree(node->right, mini, original_stdout);
        waitpid(pid, &status, 0);
		mini->exit_code_error =  WSTOPSIG(status);
    }
}

int process_tree(t_btree *node, t_minis *mini, int original_stdout)
{
	if (node && ft_strcmp(node->cmd, "|") == 0)
		handle_pipe_fork(node, mini, original_stdout);
	else if (node){
		redirect_(node->redir,mini);
		execute(node->cmd, mini);
	}
	return (mini->exit_code_error);
}
