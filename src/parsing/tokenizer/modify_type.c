/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:00:28 by rpires-c          #+#    #+#             */
/*   Updated: 2024/11/29 15:06:04 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	reset_first_command(int *first_command_seen, t_token *token)
{
	if (token && ft_strcmp(token->type, "pipe") == 0)
		*first_command_seen = 0;
}

char	*strip_quotes(char *stripped_token)
{
	char	*new_stripped_token;

	new_stripped_token = stripped_token;
	if ((stripped_token[0] == '"' || stripped_token[0] == '\'')
		&& stripped_token[0] == stripped_token[ft_strlen(stripped_token) - 1])
		new_stripped_token = ft_substr(stripped_token, 1,
				ft_strlen(stripped_token) - 2);
	return (new_stripped_token);
}

void	update_token_type(t_token *token, int *first_command_seen, char *path)
{
	if (path)
	{
		if (*first_command_seen)
		{
			free(token->type);
			token->type = ft_strdup("argument");
		}
		else
			*first_command_seen = 1;
		free(path);
	}
	else
	{
		free(token->type);
		token->type = ft_strdup("argument");
	}
}

void	handle_token_type(t_token *token, int *first_command_seen,
					t_minis *mini)
{
	char	*stripped_token;
	char	**env_matrix;
	char	*path;

	stripped_token = strip_quotes(token->token);
	env_matrix = env_to_matrix(mini);
	path = find_path(stripped_token, env_matrix);
	update_token_type(token, first_command_seen, path);
	free_env_matrix(env_matrix);
	if (stripped_token != token->token)
		free(stripped_token);
}

void	modify_token_types(t_list_ *token_list, t_minis *mini)
{
	int		first_command_seen;
	t_list_	*current;
	t_token	*token;

	first_command_seen = 0;
	current = token_list;
	while (current)
	{
		token = (t_token *)current->content;
		reset_first_command(&first_command_seen, token);
		if (token && (ft_strcmp(token->type, "command") == 0
				|| (ft_strncmp(token->token, "\"", 1) == 0
					|| ft_strncmp(token->token, "'", 1) == 0)))
			handle_token_type(token, &first_command_seen, mini);
		current = current->next;
	}
}
