/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:01:39 by rpires-c          #+#    #+#             */
/*   Updated: 2024/11/20 17:22:49 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	*delete_token(void *node)
{
	t_token *token_node;

	token_node = (t_token *)node;
	ft_free(token_node->type, NULL);
	ft_free(token_node->token, NULL);
	ft_free(token_node->redirection_target, NULL);
	ft_free(token_node->redirection_source, NULL);
}

void	*print_token(void *node)
{
    t_token *token_node;

	token_node = (t_token *)node;
    printf("\nType: %s\n", token_node->type);
    printf("\nToken: %s\n", token_node->token);
    if (token_node->redirection_source || token_node->redirection_target)
    {
        printf("\nTarget: %s\n", token_node->redirection_target);
        printf("\nSource: %s\n", token_node->redirection_source);
    }
}

t_token	*create_token(char *token, char *type)
{
	t_token *node;
	
	node = ft_malloc(1 * sizeof(t_token), NULL);
	node->token = ft_strdup(token);
	ft_strcpy(node->type, type);
	node->token = ft_strdup(token);
	return (node);
}

t_token	*tokenizeAndCheckBashCommand(t_minis *mini)
{
    t_list_	*head = NULL;
    t_list_	*current = NULL;
	t_list_	*node;
    char	*token;
    char	*type;
	bool	flag;
	
	flag = true;
    token = strtok(mini->line, " ");
    while (token != NULL)
    {
        if (token[0] == '\'')
            type = "in_single_quotes";
        else if (token[0] == '"')
            type = "in_double_quotes";
        else if (strcmp(token, "|") == 0)
            {
				type = "pipe";
				flag = true;
			}
        else if (strcmp(token, "<") == 0 || strcmp(token, ">") == 0)
            type = "redirection";
        else if (strcmp(token, "<<") == 0 || strcmp(token, ">>") == 0)
            type = "append";
        else if (token[0] == '$')
            type = "environment_variable";
        else 
        {
            if (find_path(token, env_to_matrix(mini)) && flag) 
			{
				type = "command";
				flag = false;
			}
            else 
                type = "argument";
        }
        node = ft_node_new((void *)create_token(token, type));
		ft_node_add_front(&node, node);
        if (head == NULL)
            head = node;
        else
			current->next = node;
		current = node;
        token = strtok(NULL, " ");
    }
	print_list(head, print_token);
    return (head);
}