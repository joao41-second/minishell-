/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:42:28 by rpires-c          #+#    #+#             */
/*   Updated: 2024/12/04 17:35:24 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int* handle_redirections(t_list_ *tokens)
{
    static int fds[2];

    fds[0] = STDIN_FILENO;
    fds[1] = STDOUT_FILENO;
    t_list_ *current = tokens;
    while (current)
    {
        t_token *token = (t_token *)current->content;
        if (token && ft_strcmp(token->type, "redir") == 0)
        {
            if (!ft_strcmp(token->token, ">"))
            {
                close(fds[1]);
                fds[1] = open(token->redirection_target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            }
            else if (!ft_strcmp(token->token, ">>"))
            {
                close(fds[1]);
                fds[1] = open(token->redirection_target, O_WRONLY | O_CREAT | O_APPEND, 0644);
            }
            else if (!ft_strcmp(token->token, "<"))
            {
                close(fds[0]);
                fds[0] = open(token->redirection_target, O_RDONLY);
            }
        }
        current = current->next;
    }
    return fds;
}

int execute_command_group(t_list_ *tokens, char **envp)
{
    char **command_argv;
    int command_argc = 0;
    int output_redirected = 0;
    char *full_path;

    full_path = find_path("ls", envp);
    if (!full_path) {
        perror("Command not found");
        return -1;
    }

    // Replace first argument with full path
    command_argv[0] = full_path;
    int i = 0;
    while (command_argv[i])
    {
        printf("%s", command_argv[i]);
        i++;
    }
    int *fds = handle_redirections(tokens);
    dup2(fds[0], STDIN_FILENO);
    if (!output_redirected)
        dup2(STDOUT_FILENO, fds[1]);
    else
        dup2(fds[1], STDOUT_FILENO);
	printf("%s\n", full_path);
    // execve(full_path, command_argv, envp);
    // perror("execve");
    free(full_path);
    free(command_argv);
    return -1;
}

void process_token_list(t_list_ *tokens, char **envp)
{
    int pipefd[2];
    pid_t pid;
    t_list_ *current;

	current = tokens;
    while (current)
    {
        t_token *token = (t_token *)current->content;
        
        if (ft_strcmp(token->type, "pipe") == 0)
        {
            if (pipe(pipefd) == -1)
                pipe_error();

            pid = fork();
            if (pid == -1)
                fork_error();

            if (pid == 0)
            {
                close(pipefd[0]);
                dup2(pipefd[1], STDOUT_FILENO);
                close(pipefd[1]);
                execute_command_group(tokens, envp);
                exit(1);
            }
            else
            {
                close(pipefd[1]);
                dup2(pipefd[0], STDIN_FILENO);
                close(pipefd[0]);
                current = current->next;
            }
        }
        
        current = current->next;
    }
    execute_command_group(tokens, envp);
}
