/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:01:39 by rpires-c          #+#    #+#             */
/*   Updated: 2024/11/18 16:41:39 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void printTokens(Node* head)
{
	Node* current = head;
	while (current != NULL)
	{
	printf("%s (%s)\n", current->token, current->type);
	current = current->next;
	}
}

Node* createNode(char* token, char* type)
{
	Node* newNode = malloc(sizeof(Node));
	newNode->token = strdup(token);
	strcpy(newNode->type, type);
	newNode->next = NULL;
	return newNode;
}

Node* tokenizeAndCheckBashCommand(t_minis *mini)
{
    Node* head = NULL;
    Node* current = NULL;
    char* token;
    char* type;
    token = strtok(mini->line, " ");
    
    while (token != NULL)
    {
        if (token[0] == '\'')
            type = "in_single_quotes";
        else if (token[0] == '"')
            type = "in_double_quotes";
        else if (strcmp(token, "|") == 0)
            type = "pipe";
        else if (strcmp(token, "<") == 0 || strcmp(token, ">") == 0)
            type = "redirection";
        else if (strcmp(token, "<<") == 0 || strcmp(token, ">>") == 0)
            type = "append";
        else if (token[0] == '$')
            type = "environment_variable";
        else 
        {
            if (find_path(token, mini->env)) 
                type = "command";
            else 
                type = "string";
        }
        
        Node* newNode = createNode(token, type);
        if (head == NULL)
        {
            head = newNode;
            current = head;
        } 
        else 
        {
            current->next = newNode;
            current = newNode;
        }
        
        token = strtok(NULL, " ");
    }
    
    printTokens(head);
    return head;
}