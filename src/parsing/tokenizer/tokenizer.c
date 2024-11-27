/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:01:39 by rpires-c          #+#    #+#             */
/*   Updated: 2024/11/27 18:27:14 by rpires-c         ###   ########.fr       */
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

void	process_quoted_string(char *line, int *i, char ***env_matrix, t_list_ **token_list)
{
	char	*current_token;
	int		is_command;

	if (!extract_quoted_string(line, i, &current_token))
		return;
	is_command = is_quoted_string_command(current_token, *env_matrix);
	if (is_command)
		add_to_list(token_list, create_token(current_token, "command"));
	else
		add_to_list(token_list, create_token(current_token, "argument"));
	free(current_token);
}

void	process_operator_tokens(const char *line, int *i, t_list_ **token_list)
{
	char	*current_token;
	int		token_length;

	if ((line[*i] == '>' && line[*i + 1] == '>') || 
		(line[*i] == '<' && line[*i + 1] == '<'))
		token_length = 2;
	else
		token_length = 1;
	current_token = ft_substr(line, *i, token_length);
	*i += token_length;
	if (current_token[0] == '|')
		add_to_list(token_list, create_token(current_token, "pipe"));
	else
		add_to_list(token_list, create_token(current_token, 
					get_redirection_type(current_token)));
	free(current_token);
}

void	process_regular_token(const char *line, int *i, char ***env_matrix, t_list_ **token_list)
{
	char	*current_token;
	char	*path;
	int		token_start;

	token_start = *i;
	while (line[*i] && !is_whitespace(line[*i]) && 
			!is_quote(line[*i]) && line[*i] != '>' && 
			line[*i] != '<' && line[*i] != '|')
		(*i)++;
	current_token = ft_substr(line, token_start, *i - token_start);
	if (current_token[0] == '$')
		add_to_list(token_list, create_token(current_token, "env_var"));
	else
	{
		path = find_path(current_token, *env_matrix);
		if (path)
		{
			add_to_list(token_list, create_token(current_token, "command"));
			free(path);
		}
		else
			add_to_list(token_list, create_token(current_token, "argument"));
	}
	free(current_token);
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

t_list_	*initializeAndFinalizeTokenizer(t_minis *mini, char ***env_matrix)
{
	t_list_ *token_list;

	token_list = initialize_tokenizer(mini, env_matrix);
	finalize_tokens(token_list, *env_matrix, mini);
	return (token_list);
}

void	tokenizeBashCommandCore(char *line, t_list_ **token_list, char ***env_matrix)
{
	int i = 0;

	while (line[i])
	{
		while (line[i] && is_whitespace(line[i]))
			i++;
		if (!line[i])
			break;
		if (is_quote(line[i]))
		{
			process_quoted_string(line, &i, env_matrix, token_list);
			continue ;
		}
		if (line[i] == '>' || line[i] == '<' || line[i] == '|')
		{
			process_operator_tokens(line, &i, token_list);
			continue ;
		}
		process_regular_token(line, &i, env_matrix, token_list);
	}
}

t_list_	*tokenizeAndCheckBashCommand(t_minis *mini)
{
	t_list_ *token_list;
	char **env_matrix;

	token_list = initialize_tokenizer(mini, &env_matrix);
	tokenizeBashCommandCore(mini->line, &token_list, &env_matrix);
	finalize_tokens(token_list, env_matrix, mini);
	return (token_list);
}
