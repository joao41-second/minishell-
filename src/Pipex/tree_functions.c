/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:02:47 by jperpct           #+#    #+#             */
/*   Updated: 2025/01/09 16:21:59 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void handle_pipe_fork(t_btree *node, t_minis *mini, int original_stdout)
{
    int fd[2];
    pid_t pid;

    if (pipe(fd) == -1)
        pipe_error();
    pid = fork();
    if (pid == -1)
        fork_error();
    if (pid == 0)
    {
        if (node->right == NULL)
        {
			close(fd[0]);
			close(fd[1]);
			dup2(STDOUT_FILENO, original_stdout);
			close(original_stdout);
			process_tree(node->left, mini, original_stdout);
			exit(0);
        }
        else
        {
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
			process_tree(node->left, mini, original_stdout);
			exit(0);
        }
    }
    else
    {
        close(fd[1]);
        if (node->right && ft_strcmp(node->right->cmd, "|") == 0)
            dup2(fd[0], STDIN_FILENO);
        else
        {
            int terminal_fd = dup(STDOUT_FILENO);
            dup2(terminal_fd, STDOUT_FILENO);
        }
        close(fd[0]);
        process_tree(node->right, mini, original_stdout);
    }
}

void process_tree(t_btree *node, t_minis *mini, int original_stdout)
{
    if (node && ft_strcmp(node->cmd, "|") == 0)
    {
        handle_pipe_fork(node, mini, original_stdout);
    }
    else if (node)
    {
        execute(node->cmd, mini);
    }
}
