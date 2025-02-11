/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection_syntax.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:31:11 by rpires-c          #+#    #+#             */
/*   Updated: 2025/02/10 19:17:27 by rpires-c         ###   ########.fr       */
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
		state->consecutive_redirections++;
		if (command[current_index + 1] == c)
		{
			if (state->consecutive_redirections > 1)
				return (false);
			state->redirection_needs_target = true;
			state->consecutive_redirections = 0;
			return (true);
		}
		if (state->consecutive_redirections > 1)
			return (false);
		state->redirection_needs_target = true;
		return (true);
	}
	return (true);
}

bool	is_invalid_redirection(const char *command, int *index)
{
	int	i;

	i = *index;
	if ((command[i] == '>' && command[i + 1] == '>')
		|| (command[i] == '<' && command[i + 1] == '<'))
		i += 2;
	else
		i++;
	while (command[i] != '\0')
	{
		if (ft_isspace(command[i]))
		{
			i++;
			continue ;
		}
		if (command[i] != '<' && command[i] != '>' && command[i] != '|')
		{
			*index = i;
			return (false);
		}
		break ;
	}
	return (true);
}

bool	validate_redirections(char c, const char *command,
								int current_index,
								struct s_cmd_state *state)
{
	if (is_in_quotes(state))
		return (true);
	if (command[current_index] == '<' || command[current_index] == '>'
		|| (command[current_index] == '>' && command[current_index + 1] == '>')
		|| (command[current_index] == '<' && command[current_index + 1] == '<'))
	{
		if (is_invalid_redirection(command, &current_index))
			return (false);
	}
	if (!handle_redirection_char(c, command, current_index, state))
		return (false);
	if (state->redirection_needs_target && !ft_isspace(c))
	{
		state->redirection_needs_target = false;
		state->consecutive_redirections = 0;
	}
	return (true);
}
