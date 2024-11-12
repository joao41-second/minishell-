/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote_syntax.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:11:19 by rpires-c          #+#    #+#             */
/*   Updated: 2024/11/11 14:28:15 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

bool	is_in_quotes(const struct s_cmd_state *state)
{
	return (state->in_single_quote || state->in_double_quote);
}

void	handle_quotes(char c, struct s_cmd_state *state)
{
	if (c == '\'' && !state->in_double_quote)
		state->in_single_quote = !state->in_single_quote;
	else if (c == '"' && !state->in_single_quote)
		state->in_double_quote = !state->in_double_quote;
}

bool	handle_quotes_and_spaces(char c, struct s_cmd_state *state)
{
	if (!state->command_started && isspace(c))
		return (false);
	if (!state->command_started && !isspace(c))
		state->command_started = true;
	if ((c == '\'' && !state->in_double_quote)
		|| (c == '"' && !state->in_single_quote))
	{
		handle_quotes(c, state);
		return (false);
	}
	return (true);
}
