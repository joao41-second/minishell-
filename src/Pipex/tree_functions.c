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

void handle_redirection(t_list_ *redir_token)
{
    t_token *token = (t_token *)redir_token->content;
    int fd;
    
    if (ft_strcmp(token->type, "redir") != 0)
        return;
    
    if (ft_strcmp(token->token, "<") == 0)
    {
        fd = open(token->redirection_source, O_RDONLY);
        dup2(fd, STDIN_FILENO);
        close(fd);
    }
    else if (ft_strcmp(token->token, ">") == 0)
    {
        fd = open(token->redirection_target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        dup2(fd, STDOUT_FILENO);
        close(fd);
    }
    else if (ft_strcmp(token->token, ">>") == 0)
    {
        fd = open(token->redirection_target, O_WRONLY | O_CREAT | O_APPEND, 0644);
        dup2(fd, STDOUT_FILENO);
        close(fd);
    }
}

void process_merged_list(t_list_ *merged_list, char **envp)
{
    t_list_ *current = merged_list;
    pid_t pid;
    int pipe_fd[2];
    
    while (current)
    {
        t_token *token = (t_token *)current->content;
        if (ft_strcmp(token->type, "command") == 0)
        {
            t_list_ *look_ahead = current->next;
            while (look_ahead && ft_strcmp(((t_token *)look_ahead->content)->type, "redir") == 0)
            {
                handle_redirection(look_ahead);
                look_ahead = look_ahead->next;
            }
            execute(token->token, envp);
        }
        else if (ft_strcmp(token->type, "pipe") == 0)
        {
            if (pipe(pipe_fd) == -1)
                pipe_error();
            
            pid = fork();
            if (pid == -1)
                fork_error();
            
            if (pid == 0)
            {
                close(pipe_fd[0]);
                dup2(pipe_fd[1], STDOUT_FILENO);
                close(pipe_fd[1]);
                current = current->next;
                if (current && ft_strcmp(((t_token *)current->content)->type, "command") == 0)
                {
                    t_token *next_cmd = (t_token *)current->content;
                    execute(next_cmd->token, envp);
                }
                exit(0);
            }
            else
            {
                close(pipe_fd[1]);
                dup2(pipe_fd[0], STDIN_FILENO);
                close(pipe_fd[0]);
            }
        }
        
        current = current->next;
    }
}