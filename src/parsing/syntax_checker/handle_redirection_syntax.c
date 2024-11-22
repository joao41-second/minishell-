/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection_syntax.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:31:11 by rpires-c          #+#    #+#             */
/*   Updated: 2024/11/18 14:08:36 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

bool	check_redirection_character(char c,
										struct s_cmd_state *state)
{
	state->consecutive_redirections++;
	if (state->consecutive_redirections > 2)
		return (false);
	if (c == '<' && state->last_char_is_redirection)
		return (false);
	state->redirection_needs_target = true;
	if (c == '>')
		state->last_char_is_redirection = true;
	return (true);
}

bool	handle_non_redirection_character(char c,
											struct s_cmd_state *state)
{
	if (state->redirection_needs_target)
	{
		if (!ft_isspace(c))
		{
			if (c == '|')
				return (false);
			state->redirection_needs_target = false;
		}
	}
	state->consecutive_redirections = 0;
	state->last_char_is_redirection = false;
	return (true);
}

bool	validate_redirections(char c, struct s_cmd_state *state)
{
	if ((c == '>' || c == '<') && !is_in_quotes(state))
		return (check_redirection_character(c, state));
	else
		return (handle_non_redirection_character(c, state));
}
