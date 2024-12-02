/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_type_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:10:21 by rpires-c          #+#    #+#             */
/*   Updated: 2024/12/02 17:23:02 by rpires-c         ###   ########.fr       */
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

int	is_quoted_string_command(char *str, char **env_matrix)
{
	char	*stripped;
	char	*path;

	stripped = NULL;
	path = NULL;
	if ((str[0] == '"' || str[0] == '\'')
		&& str[0] == str[ft_strlen(str) - 1])
	{
		stripped = ft_substr(str, 1, ft_strlen(str) - 2);
		path = find_path(stripped, env_matrix);
		ft_free(stripped, NULL);
		if (path)
		{
			ft_free(path, NULL);
			return (1);
		}
	}
	return (0);
}
