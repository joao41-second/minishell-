/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:23:14 by rpires-c          #+#    #+#             */
/*   Updated: 2024/12/04 14:23:16 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	treat_current(t_list_ *current, char **matrix, int i)
{
	t_env	*env_node;
	char	*temp;
	char	*name;
	char	*content;

	env_node = (t_env *)current->content;
	name = "";
	if (env_node->name)
		name = env_node->name;
	content = "";
	if (env_node->content)
		content = env_node->content;
	matrix[i] = ft_strjoin(name, "=");
	if (matrix[i])
	{
		temp = matrix[i];
		matrix[i] = ft_strjoin(temp, content);
		ft_free(temp, NULL);
	}
}

void	env_to_matrix_aux(t_list_ *current, char **matrix, int i)
{
	if (current->content)
		treat_current(current, matrix, i);
	else
		matrix[i] = ft_strjoin("", "");
}

int	count_env_size(t_list_ *env)
{
	int		size;
	t_list_	*current;

	size = 0;
	current = env;
	while (current)
	{
		size++;
		current = current->next;
	}
	return (size);
}

char	**env_to_matrix(t_minis *mini)
{
	char	**matrix;
	t_list_	*current;
	int		size;
	int		i;

	if (!mini || !mini->env)
		return (NULL);
	size = count_env_size(mini->env);
	matrix = (char **)ft_malloc(sizeof(char *) * (size + 1), NULL);
	if (!matrix)
		return (NULL);
	current = mini->env;
	i = 0;
	while (current)
	{
		env_to_matrix_aux(current, matrix, i);
		i++;
		current = current->next;
	}
	matrix[size] = NULL;
	return (matrix);
}
