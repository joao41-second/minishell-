/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rui <rui@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:22:36 by rpires-c          #+#    #+#             */
/*   Updated: 2024/12/13 16:59:46 by rui              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void process_operator_tokens(const char *line, int *i, t_list_ **token_list)
{
    char *current_token;
    char *redir_type;
    int token_length;

    if ((line[*i] == '>' && line[*i + 1] == '>') || 
        (line[*i] == '<' && line[*i + 1] == '<'))
        token_length = 2;
    else
        token_length = 1;
    current_token = ft_substr(line, *i, token_length);
    *i += token_length;
    if (current_token[0] == '|')
        add_to_list(token_list, create_token(current_token, "pipe", NULL, NULL));
    else
    {
        redir_type = get_redirection_type(current_token);
        add_to_list(token_list, create_token(current_token, redir_type, NULL, NULL));
    }
    ft_free(redir_type, NULL);
    ft_free(current_token, NULL);
}

void process_regular_token(const char *line, int *i, t_list_ **token_list, bool command)
{
    char *current_token;
    char *path;
    int token_start;

    token_start = *i;
    while (line[*i] && !is_whitespace(line[*i]) 
        	&& line[*i] != '>' && line[*i] != '<' && line[*i] != '|')
        (*i)++;
    current_token = ft_substr(line, token_start, *i - token_start);
    if (command)
		add_to_list(token_list, create_token(current_token, "command", NULL, NULL));
    else
        add_to_list(token_list, create_token(current_token, "argument", NULL, NULL));
    ft_free(current_token, NULL);
}

void	tokenize_bash_command_core(char *line, t_list_ **token_list)
{
	int		i;
	bool	command;

	i = 0;
	command = true;
	while (line[i])
	{
		while (line[i] && is_whitespace(line[i]))
			i++;
		if (!line[i])
			break ;
		if ((line[i] == '>' || (line[i] == '>' && line[i + 1] == '>'))
			|| (line[i] == '<' || (line[i] == '<' && line[i + 1] == '<'))
			|| line[i] == '|')
		{
			if (line[i] == '|')
				command = true;
			else
				command = false;
			process_operator_tokens(line, &i, token_list);
		}
		else
		{
			process_regular_token(line, &i, token_list, command);
			command = false;
		}
		
	}
}

t_list_	*tokenize_and_check_bash_command(t_minis *mini)
{
	t_list_	*token_list;
	char	**env_matrix;

	token_list = initialize_tokenizer(mini, &env_matrix);
	tokenize_bash_command_core(mini->line, &token_list);
	finalize_tokens(token_list, env_matrix, mini);
    ft_free_node(&token_list, free_token);
	return (token_list);
}
