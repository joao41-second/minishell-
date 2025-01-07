/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rui <rui@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:02:47 by jperpct           #+#    #+#             */
/*   Updated: 2025/01/07 17:49:41 by rui              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void process_pipe(t_list_ *current, t_minis *mini)
{
   pid_t pid;
   int fd[2];
   t_token *token;

   if (pipe(fd) == -1)
   {
       perror("pipe");
       return;
   }
   pid = fork();
   if (pid == -1)
   {
       perror("fork"); 
       return;
   }
   if (pid == 0) // Child process
   {
       close(fd[0]);
       dup2(fd[1], STDOUT_FILENO);
       close(fd[1]);
       token = (t_token *)current->content;
       if (current->previous && ((t_token *)current->previous->content)->type 
           && strcmp(((t_token *)current->previous->content)->type, "command") == 0)
           execute(((t_token *)current->previous->content)->token, mini);
       exit(1);
   }
   else // Parent process 
   {
       int status;
       close(fd[1]);
       dup2(fd[0], STDIN_FILENO); 
       close(fd[0]);
       waitpid(pid, &status, 0);
       if (current->next && ((t_token *)current->next->content)->type
           && strcmp(((t_token *)current->next->content)->type, "command") == 0)
           execute(((t_token *)current->next->content)->token, mini);
   }
}

void process_merged_list(t_list_ *merged_list, t_minis *mini)
{
   t_list_ *current = merged_list;
   pid_t last_pid = 0;
   int status;

   while (current)
   {
       t_token *token = (t_token *)current->content;
       if (strcmp(token->type, "pipe") == 0)
       {
           process_pipe(current, mini);
           // Skip next node since it was handled in process_pipe
           if (current->next)
               current = current->next;
       }
       else if (strcmp(token->type, "command") == 0)
       {
           last_pid = fork();
           if (last_pid == 0)
           {
               execute(token->token, mini);
               exit(0);
           }
       }
       current = current->next;
   }
   if (last_pid > 0)
       waitpid(last_pid, &status, 0);
}