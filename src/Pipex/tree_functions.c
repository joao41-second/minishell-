/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rui <rui@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:02:47 by jperpct           #+#    #+#             */
/*   Updated: 2025/01/07 16:55:04 by rui              ###   ########.fr       */
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

pid_t create_pipe_and_fork(int *pipe_fd)
{
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

void setup_child_pipe(int *pipe_fd)
{
    close(pipe_fd[0]);
    dup2(pipe_fd[1], STDOUT_FILENO);
    close(pipe_fd[1]);
}

void setup_parent_pipe(int *pipe_fd)
{
    close(pipe_fd[1]);
    dup2(pipe_fd[0], STDIN_FILENO);
    close(pipe_fd[0]);
}

void process_builtin(t_token *token, t_minis *mini) {
    mini->tokens = tokenize_and_check_bash_command(mini);
    mini->tokens_copy = tokenize_and_check_bash_command(mini);
    builtins(mini);
}

void process_pipe(t_list_ *current, t_minis *mini)
{
	pid_t	pid;
	int		fd[2];

	if(pipe(fd) == -1)
	{
		perror("pipe");
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return ;
	}
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
}

void process_merged_list(t_list_ *merged_list, t_minis *mini)
{
	t_list_ *current = merged_list;

	while (current)
	{
		t_token *token = (t_token *)current->content;
		if (ft_strcmp(token->type, "builtin") == 0)
			process_builtin(token, mini);
		else if (ft_strcmp(token->type, "pipe") == 0)
		{
			if (current->previous && current->next)
				process_pipe(current, mini);
		}
		else if (ft_strcmp(token->type, "command") == 0)
			execute(token->token, mini);
		current = current->next;
	}
}
