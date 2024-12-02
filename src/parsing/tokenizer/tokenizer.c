/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:01:39 by rpires-c          #+#    #+#             */
/*   Updated: 2024/12/02 17:47:47 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void process_operator_tokens(const char *line, int *i, t_list_ **token_list)
{
    char *current_token;
    int token_length;

    token_length = ((line[*i] == '>' && line[*i + 1] == '>') ||
                    (line[*i] == '<' && line[*i + 1] == '<')) ? 2 : 1;

    current_token = ft_substr(line, *i, token_length);
    *i += token_length;

    if (current_token[0] == '|') {
        add_to_list(token_list, create_token(current_token, "pipe"));
    } else {
        add_to_list(token_list, create_token(current_token, get_redirection_type(current_token)));
    }

    ft_free(current_token, NULL);
}

void process_regular_token(const char *line, int *i, char ***env_matrix, t_list_ **token_list)
{
    char *current_token;
    char *path;
    int token_start;

    token_start = *i;
    while (line[*i] && !is_whitespace(line[*i]) && !is_quote(line[*i]) &&
           line[*i] != '>' && line[*i] != '<' && line[*i] != '|') {
        (*i)++;
    }
    current_token = ft_substr(line, token_start, *i - token_start);

    if (current_token[0] == '$') {
        add_to_list(token_list, create_token(current_token, "env_var"));
    } else {
        path = find_path(current_token, *env_matrix);
        if (path) {
            add_to_list(token_list, create_token(current_token, "command"));
            ft_free(path, NULL);
        } else {
            add_to_list(token_list, create_token(current_token, "argument"));
        }
    }
    ft_free(current_token, NULL); // Clean up token memory
}

void	tokenize_bash_command_core(char *line, t_list_ **token_list,
						char ***env_matrix)
{
	int	i;

	i = 0;
	while (line[i])
	{
		while (line[i] && is_whitespace(line[i]))
			i++;
		if (!line[i])
			break ;
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

t_list_	*tokenize_and_check_bash_command(t_minis *mini)
{
	t_list_	*token_list;
	char	**env_matrix;

	token_list = initialize_tokenizer(mini, &env_matrix);
	tokenize_bash_command_core(mini->line, &token_list, &env_matrix);
	finalize_tokens(token_list, env_matrix, mini);
	return (token_list);
}
