/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection_syntax.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:31:11 by rpires-c          #+#    #+#             */
/*   Updated: 2025/01/29 15:59:11 by rpires-c         ###   ########.fr       */
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

bool	handle_non_redirection_character(char c, struct s_cmd_state *state)
{
	if (state->redirection_needs_target)
	{
		if (!ft_isspace(c))
		{
			if (c == '|')
				return (false);
			if (c == '\'' || c == '"')
			{
				state->redirection_needs_target = false;
				return (true);
			}
			state->redirection_needs_target = false;
		}
	}
	state->consecutive_redirections = 0;
	state->last_char_is_redirection = false;
	return (true);
}

bool	handle_redirection_char(char c, const char *command,
								int current_index,
								struct s_cmd_state *state)
{
	if (c == '<' || c == '>')
	{
		if (state->redirection_needs_target)  
			return (false);
		state->consecutive_redirections++;
		if (command[current_index + 1] == c)
		{
			if (state->consecutive_redirections > 1)
				return (false);
			state->redirection_needs_target = true;
			state->consecutive_redirections = 0;
			return (true);
		}
		int next_index = current_index + 1;
		while (command[next_index] && ft_isspace(command[next_index])) 
			next_index++;

		if (command[next_index] == '>' || command[next_index] == '<'
			|| command[next_index] == '|')
			return (false);
		state->redirection_needs_target = true;
		return (true);
	}
	return (true);
}

bool	validate_redirections(char c, const char *command,
							int current_index,
							struct s_cmd_state *state)
{
	if (is_in_quotes(state))
		return (true);
	if (!handle_redirection_char(c, command, current_index, state))
		return (false);
	if (state->redirection_needs_target)
	{
		if (!ft_isspace(c))
		{
			state->redirection_needs_target = false;
			state->consecutive_redirections = 0;
		}
	}
	return (true);
}
