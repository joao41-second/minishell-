/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_extra.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 20:52:48 by rpires-c          #+#    #+#             */
/*   Updated: 2025/02/11 11:11:15 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	process_regular_token_extra(const char *line,
			char quote, int *i)
{
	if (line[*i] == '\'' || line[*i] == '"')
	{
		quote = line[*i];
		(*i)++;
		while (line[*i] && line[*i] != quote)
			(*i)++;
		if (line[*i])
			(*i)++;
	}
	else
		(*i)++;
}

void	reset_flags(bool *command, bool *master, bool *override)
{
	if (*master)
		*master = false;
	if (*override)
		*override = false;
	*command = true;
}

void	process_pipe_or_redirection1(char *line, int *i,
			t_list_ **token_list, t_flags *flags)
{
	if (line[*i] == '|')
	{
		reset_flags(&flags->command, &flags->master, &flags->override);
		process_operator_tokens(line, i, token_list);
	}
	else
	{
		flags->override = true;
		process_operator_tokens(line, i, token_list);
	}
}

void	process_regular_command(char *line, int *i, t_list_ **token_list,
					t_flags *flags)
{
	if (flags->override)
		flags->command = false;
	if (!flags->master && flags->command)
		flags->master = true;
	process_regular_token(line, i, token_list, flags->command);
	if (flags->override && !flags->master)
	{
		flags->command = true;
		flags->override = false;
	}
	else
		flags->command = false;
}
