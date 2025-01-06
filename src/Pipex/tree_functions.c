/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rui <rui@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:02:47 by jperpct           #+#    #+#             */
/*   Updated: 2025/01/06 15:57:21 by rui              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int handle_single_redirection(t_token *redir_token) {
    int fd;
    if (ft_strcmp(redir_token->type, "redir") != 0)
        return 0;

    if (ft_strcmp(redir_token->token, "<") == 0) {
        fd = open(redir_token->redirection_source, O_RDONLY);
        if (fd == -1)
            return -1;
        dup2(fd, STDIN_FILENO);
        close(fd);
    } else if (ft_strcmp(redir_token->token, ">") == 0) {
        fd = open(redir_token->redirection_target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1)
            return -1;
        dup2(fd, STDOUT_FILENO);
        close(fd);
    } else if (ft_strcmp(redir_token->token, ">>") == 0) {
        fd = open(redir_token->redirection_target, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd == -1)
            return -1;
        dup2(fd, STDOUT_FILENO);
        close(fd);
    }
    return 1;
}

int apply_redirections(t_list_ *current) {
    t_list_ *look_ahead = current->next;
    int flag;
    while (look_ahead && strcmp(((t_token *)look_ahead->content)->type, "redir") == 0) {
        flag = handle_single_redirection((t_token *)look_ahead->content);
        if (flag == -1)
            return 1;
        look_ahead = look_ahead->next;
    }
    return 0;
}

// Command Execution
void execute_command(t_token *cmd_token, t_minis *mini) {
    execute(cmd_token->token, mini);
    ft_exit_end(0);
}

// Pipe Handling
pid_t create_pipe_and_fork(int *pipe_fd) {
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        ft_exit_end(126);
    }
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        ft_exit_end(126);
    }
    return pid;
}

void setup_child_pipe(int *pipe_fd) {
    close(pipe_fd[0]);
    dup2(pipe_fd[1], STDOUT_FILENO);
    close(pipe_fd[1]);
}

void setup_parent_pipe(int *pipe_fd) {
    close(pipe_fd[1]);
    dup2(pipe_fd[0], STDIN_FILENO);
    close(pipe_fd[0]);
}

// Helper Functions for Pipeline Processing
void process_builtin(t_token *token, t_minis *mini) {
    mini->tokens = tokenize_and_check_bash_command(mini);
    mini->tokens_copy = tokenize_and_check_bash_command(mini);
    builtins(mini);
}

void process_pipe(t_list_ *current, t_minis *mini, int *status) {
    t_token *cmd1 = (t_token *)current->previous->content;
    t_token *cmd2 = (t_token *)current->next->content;

    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        ft_exit_end(126);
    }

    pid_t pid1 = fork();
    if (pid1 == 0) {
        // First child process: handle cmd1 (e.g., cat)
        close(pipe_fd[0]);             // Close unused read end
        dup2(pipe_fd[1], STDOUT_FILENO); // Redirect stdout to pipe write end
        close(pipe_fd[1]);             // Close write end after dup2
        execute_command(cmd1, mini);  // Execute command
    }

    pid_t pid2 = fork();
    if (pid2 == 0) {
        // Second child process: handle cmd2 (e.g., ls)
        close(pipe_fd[1]);             // Close unused write end
        dup2(pipe_fd[0], STDIN_FILENO); // Redirect stdin to pipe read end
        close(pipe_fd[0]);             // Close read end after dup2
        execute_command(cmd2, mini);  // Execute command
    }

    // Parent process: close both pipe ends
    close(pipe_fd[0]);
    close(pipe_fd[1]);

    // Wait for both child processes
    waitpid(pid1, status, 0);
    waitpid(pid2, status, 0);
}

void process_command(t_list_ *current, t_minis *mini, int *status)
{
    if (apply_redirections(current) == 1) {
        perror("bash");
        mini->exit_code_error = 1;
        return;
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return;
    }
    if (pid == 0) {
        if (setsid() == -1) {
            perror("setsid");
            exit(1);
        }
        execute_command((t_token *)current->content, mini);
    }
    // Only wait if it's not part of a pipeline
    if (!current->next || strcmp(((t_token *)current->next->content)->type, "pipe") != 0) {
        waitpid(pid, status, 0);
    }
}

// Main Pipeline Processing
void process_merged_list(t_list_ *merged_list, t_minis *mini) {
    t_list_ *current = merged_list;
    int status;

    // Reset the pipes to prevent issues with multiple pipes
    while (current)
    {
        t_token *token = (t_token *)current->content;
        if (strcmp(token->type, "builtin") == 0)
            process_builtin(token, mini);
        else if (strcmp(token->type, "pipe") == 0)
        {
            process_pipe(current, mini, &status);
            current = current->next;
        }
        else if (strcmp(token->type, "command") == 0)
            process_command(current, mini, &status);
        current = current->next;
    }
}
