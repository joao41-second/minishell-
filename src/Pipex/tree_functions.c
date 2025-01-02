/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rui <rui@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:02:47 by jperpct           #+#    #+#             */
/*   Updated: 2025/01/02 19:35:52 by rui              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int handle_single_redirection(t_token *redir_token) {
    int fd;
    if (ft_strcmp(redir_token->type, "redir") != 0)
        return 0;

    if (ft_strcmp(redir_token->token, "<") == 0) {
        fd = open(redir_token->redirection_source, O_RDONLY);
		if(fd == -1)
			return(-1);
        dup2(fd, STDIN_FILENO);
        close(fd);
    } else if (ft_strcmp(redir_token->token, ">") == 0) {
        fd = open(redir_token->redirection_target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if(fd == -1)
			return(-1);
        dup2(fd, STDOUT_FILENO);
        close(fd);
    } else if (ft_strcmp(redir_token->token, ">>") == 0) {
        fd = open(redir_token->redirection_target, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if(fd == -1)
			return(-1);
        dup2(fd, STDOUT_FILENO);
        close(fd);
    }
    return 1;
}

int apply_redirections(t_list_ *current)
{
    t_list_	*look_ahead = current->next;

	int		flag;
    while (look_ahead && strcmp(((t_token *)look_ahead->content)->type, "redir") == 0)
	{
        flag = handle_single_redirection((t_token *)look_ahead->content);
		if(flag == -1)
			return(1);
        look_ahead = look_ahead->next;
    }
	return(0);
}

void execute_command(t_token *cmd_token, t_minis *mini)
{
    execute(cmd_token->token, mini);
  //  perror("execvp"); // If execvp fails
	ft_exit_end(0);
}

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

void process_merged_list(t_list_ *merged_list, t_minis *mini)
{
    t_list_ *current = merged_list;
    int pipe_fd[2];
    int status;
    pid_t pid1, pid2;
    int original_stdin = dup(STDIN_FILENO);
    int original_stdout = dup(STDOUT_FILENO);
    char **str;

    while (current) {
        t_token *token = (t_token *)current->content;
        dup2(original_stdin, STDIN_FILENO);
        dup2(original_stdout, STDOUT_FILENO);
        
        str = ft_split(token->token, ' ');
        if (chek_biltin(str) == TRUE) {
            mini->tokens = tokenize_and_check_bash_command(mini);
            mini->tokens_copy = tokenize_and_check_bash_command(mini);
            builtins(mini);
        }
        else if (strcmp(token->type, "pipe") == 0) {
            t_token *cmd1 = (t_token *)current->previous->content;
            t_token *cmd2 = (t_token *)current->next->content;

            if (pipe(pipe_fd) == -1) {
                perror("pipe");
                ft_exit_end(126);
            }

            // First command
            pid1 = fork();
            if (pid1 == 0) {
                close(pipe_fd[0]);
                dup2(pipe_fd[1], STDOUT_FILENO);
                close(pipe_fd[1]);
                execute_command(cmd1, mini);
            }

            // Second command
            pid2 = fork();
            if (pid2 == 0) {
                close(pipe_fd[1]);
                dup2(pipe_fd[0], STDIN_FILENO);
                close(pipe_fd[0]);
                execute_command(cmd2, mini);
            }

            // Parent closes both ends of pipe
            close(pipe_fd[0]);
            close(pipe_fd[1]);

            // Wait for both processes
            waitpid(pid1, &status, 0);
            waitpid(pid2, &status, 0);
            
            if (WEXITSTATUS(status) != 0)
                mini->exit_code_error = WEXITSTATUS(status);

            current = current->next;  // Skip the next command as we've already handled it
        }
        else if (strcmp(token->type, "command") == 0) {
            if (apply_redirections(current) == 1) {
                dup2(original_stdin, STDIN_FILENO);
                dup2(original_stdout, STDOUT_FILENO);
                close(original_stdin);
                close(original_stdout);
                perror("bash");
                mini->exit_code_error = 1;
                return;
            }
            pid1 = fork();
            if (pid1 == 0) {
                execute_command(token, mini);
            }
            waitpid(pid1, &status, 0);
            if (WEXITSTATUS(status) != 0)
                mini->exit_code_error = WEXITSTATUS(status);
        }
        free_split(str);
        current = current->next;
    }
    dup2(original_stdin, STDIN_FILENO);
    dup2(original_stdout, STDOUT_FILENO);
    close(original_stdin);
    close(original_stdout);
}
