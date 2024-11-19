/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rui <rui@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:25:40 by rui               #+#    #+#             */
/*   Updated: 2024/11/19 11:30:41 by rui              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char **env_to_matrix(t_minis *mini)
{
    char **matrix;
    t_list_ *current;
    int size;
    int i;

    if (!mini || !mini->env)
        return (NULL);

    size = 0;
    current = mini->env;
    while (current)
    {
        size++;
        current = current->next;
    }

    matrix = (char **)ft_malloc(sizeof(char *) * (size + 1), NULL);
    if (!matrix)
        return (NULL);

    current = mini->env;
    i = 0;
    while (current)
    {
        t_env *env_node = (t_env *)current->content;
        if (env_node)
        {
            char *name = env_node->name ? env_node->name : "";
            char *content = env_node->content ? env_node->content : "";
            matrix[i] = ft_strjoin(name, "=");
            if (matrix[i])
            {
                char *temp = matrix[i];
                matrix[i] = ft_strjoin(temp, content);
                free(temp);
            }
        }
        else
            matrix[i] = ft_strjoin("", "");
        i++;
        current = current->next;
    }
    matrix[size] = NULL;
    
    return (matrix);
}
