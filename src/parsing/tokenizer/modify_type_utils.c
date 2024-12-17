/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_type_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rui <rui@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:10:21 by rpires-c          #+#    #+#             */
/*   Updated: 2024/12/16 14:12:00 by rui              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_env_matrix(char **env_matrix)
{
	int	i;

	if (!env_matrix)
		return ;
	i = 0;
	while (env_matrix[i])
	{
		ft_free(env_matrix[i], NULL);
		i++;
	}
	ft_free(env_matrix, NULL);
}

int	extract_quoted_string(char *line, int *i, char **token)
{
	char	quote;
	int		start;
	int		len;

	quote = line[*i];
	start = *i;
	(*i)++;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (line[*i] == quote)
		(*i)++;
	len = *i - start;
	*token = (char *)ft_malloc(len + 1, NULL);
	if (!*token)
		return (0);
	ft_strlcpy(*token, line + start, len + 1);
	return (1);
}

int	is_quoted_string(char *str)
{
	if ((str[0] == '"' || str[0] == '\'')
		&& str[0] == str[ft_strlen(str) - 1])
		return (1);
	return (0);
}
