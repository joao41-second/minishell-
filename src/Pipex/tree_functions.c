/* /* /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:42:28 by rpires-c          #+#    #+#             */
/*   Updated: 2024/12/06 15:15:04 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int handle_single_redirection(t_token *redir_token) {
    int fd;
    if (strcmp(redir_token->type, "redir") != 0)
        return 0;

    if (strcmp(redir_token->token, "<") == 0) {
        fd = open(redir_token->redirection_source, O_RDONLY);
        dup2(fd, STDIN_FILENO);
        close(fd);
    } else if (strcmp(redir_token->token, ">") == 0) {
        fd = open(redir_token->redirection_target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        dup2(fd, STDOUT_FILENO);
        close(fd);
    } else if (strcmp(redir_token->token, ">>") == 0) {
        fd = open(redir_token->redirection_target, O_WRONLY | O_CREAT | O_APPEND, 0644);
        dup2(fd, STDOUT_FILENO);
        close(fd);
    }
    return 1;
}

void apply_redirections(t_list_ *current) {
    t_list_ *look_ahead = current->next;
    while (look_ahead && strcmp(((t_token *)look_ahead->content)->type, "redir") == 0) {
        handle_single_redirection((t_token *)look_ahead->content);
        look_ahead = look_ahead->next;
    }
}

void execute_command(t_token *cmd_token, char **envp) {
    execute(cmd_token->token, envp);
    perror("execvp"); // If execvp fails
    exit(EXIT_FAILURE);
}

pid_t create_pipe_and_fork(int *pipe_fd) {
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
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

void process_merged_list(t_list_ *merged_list, char **envp)
{
    t_list_ *current = merged_list;
    int pipe_fd[2];
    pid_t pid;
    int original_stdin = dup(STDIN_FILENO);
    int original_stdout = dup(STDOUT_FILENO);

    while (current) {
        t_token *token = (t_token *)current->content;

        // Reset standard input/output for each command
        dup2(original_stdin, STDIN_FILENO);
        dup2(original_stdout, STDOUT_FILENO);

        if (strcmp(token->type, "command") == 0) {
            apply_redirections(current);
            pid = fork();
            if (pid == 0) {
                // Child process
                execute_command(token, envp);
            } else if (pid > 0) {
                // Parent process waits for child
                waitpid(pid, NULL, 0);
            } else {
                perror("fork");
                exit(EXIT_FAILURE);
            }
        } else if (strcmp(token->type, "pipe") == 0) {
            pid = create_pipe_and_fork(pipe_fd);
            if (pid == 0) {
                setup_child_pipe(pipe_fd);
                current = current->next;
                if (current && strcmp(((t_token *)current->content)->type, "command") == 0) {
                    execute_command((t_token *)current->content, envp);
                }
                exit(EXIT_SUCCESS);
            } else {
                setup_parent_pipe(pipe_fd);
                waitpid(pid, NULL, 0);
            }
        }
        current = current->next;
    }

    // Restore original stdin and stdout
    dup2(original_stdin, STDIN_FILENO);
    dup2(original_stdout, STDOUT_FILENO);
    close(original_stdin);
    close(original_stdout);
}
