/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:02:47 by jperpct           #+#    #+#             */
/*   Updated: 2025/01/08 17:42:55 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void handle_pipe_fork(t_btree *node, char **envp)
{
    int     fd[2];
    pid_t   pid;

    if (pipe(fd) == -1)
        pipe_error();
    pid = fork();
    if (pid == -1)
        fork_error();
    
    if (pid == 0)  // Child process
    {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        process_tree(node->left, envp);
        exit(0);  // Exit after executing command
    }
    else  // Parent process
    {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        process_tree(node->right, envp);
        waitpid(pid, NULL, 0);  // Wait for child process
    }
}

void process_tree(t_btree *node, char **envp)
{
    char    **cmd_args;

    if (!node)
        return;
        
    if (ft_strcmp(node->cmd, "|") == 0)
    {
        handle_pipe_fork(node, envp);
    }
    else
    {
        cmd_args = ft_split(node->cmd, ' ');
        if (execve(cmd_args[0], cmd_args, envp) == -1)
        {
            ft_free_array(cmd_args);
            exec_error();
        }
    }
}

void execute_command_tree(t_btree *root, char **envp)
{
    pid_t   pid;
    
    if (!root)
        return;
        
    // Start execution in a new process
    pid = fork();
    if (pid == -1)
        fork_error();
        
    if (pid == 0)
    {
        process_tree(root, envp);
        exit(0);
    }
    else
    {
        // Wait for all child processes to complete
        waitpid(pid, NULL, 0);
    }
}