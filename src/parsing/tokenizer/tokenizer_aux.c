/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:41:07 by rpires-c          #+#    #+#             */
/*   Updated: 2024/11/29 15:55:13 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_list_	*initialize_tokenizer(t_minis *mini, char ***env_matrix)
{
	t_list_	*token_list;

	token_list = NULL;
	*env_matrix = env_to_matrix(mini);
	return (token_list);
}

void	finalize_tokens(t_list_ *token_list, char **env_matrix, t_minis *mini)
{
	int	i;

	set_redirection_relations(token_list);
	if (env_matrix)
	{
		i = 0;
		while (env_matrix[i])
			free(env_matrix[i++]);
		free(env_matrix);
	}
	modify_token_types(token_list, mini);
}

t_list_	*initialize_and_finalize_tokenizer(t_minis *mini, char ***env_matrix)
{
	t_list_	*token_list;

	token_list = initialize_tokenizer(mini, env_matrix);
	finalize_tokens(token_list, *env_matrix, mini);
	return (token_list);
}

void	process_quoted_string(char *line, int *i,
						char ***env_matrix, t_list_ **token_list)
{
	char	*current_token;
	int		is_command;

	if (!extract_quoted_string(line, i, &current_token))
		return ;
	is_command = is_quoted_string_command(current_token, *env_matrix);
	if (is_command)
		add_to_list(token_list, create_token(current_token, "command"));
	else
		add_to_list(token_list, create_token(current_token, "argument"));
	free(current_token);
}
