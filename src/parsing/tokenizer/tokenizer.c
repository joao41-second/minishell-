/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:22:36 by rpires-c          #+#    #+#             */
/*   Updated: 2025/02/10 22:17:22 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	process_regular_token(char *line, int *i,
			t_list_ **token_list, bool command)
{
	char	*current_token;
	int		token_start;
	char	quote;

	token_start = *i;
	quote = '\0';
	while (line[*i] && (!is_whitespace(line[*i])
			&& line[*i] != '>' && line[*i] != '<' && line[*i] != '|'))
		process_regular_token_extra(line, quote, i);
	current_token = ft_substr(line, token_start, *i - token_start);
	if (command)
		add_to_list(token_list,
			create_token(current_token, "command", NULL, NULL));
	else
		add_to_list(token_list,
			create_token(current_token, "argument", NULL, NULL));
	ft_free(current_token, NULL);
}

void	process_operator_tokens(const char *line, int *i, t_list_ **token_list)
{
	char	*current_token;
	int		token_length;

	if ((line[*i] == '>' && line[*i + 1] == '>')
		|| (line[*i] == '<' && line[*i + 1] == '<'))
		token_length = 2;
	else
		token_length = 1;
	current_token = ft_substr(line, *i, token_length);
	*i += token_length;
	if (current_token[0] == '|')
		add_to_list(token_list,
			create_token(current_token, "pipe", NULL, NULL));
	else
		add_to_list(token_list,
			create_token(current_token, "redir", NULL, NULL));
	ft_free(current_token, NULL);
}



void tokenize_bash_command_core(char *line, t_list_ **token_list)
{
    int i;
    t_flags flags; 

    i = 0;
    flags.command = true;  
    flags.master = false;
    flags.override = false;

    while (line[i])
    {
        while (line[i] && is_whitespace(line[i]))
            i++;
        if (!line[i])
            break;
        if (((line[i] == '>' && line[i + 1] == '>') || (line[i] == '<' && line[i + 1] == '<'))
            || line[i] == '>' || line[i] == '<' || line[i] == '|')
        {
            process_pipe_or_redirection1(line, &i, token_list, &flags);
        }
        else
        {
            process_regular_command(line, &i, token_list, &flags);
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
