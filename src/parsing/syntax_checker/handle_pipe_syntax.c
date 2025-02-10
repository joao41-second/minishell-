/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe_syntax.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:24:09 by rpires-c          #+#    #+#             */
/*   Updated: 2025/02/10 22:19:46 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

bool	check_pipe_surroundings(const char *command, int current_index)
{
	int	prev_index;
	int	next_index;

	if (!command || current_index == 0 || command[current_index + 1] == '\0')
		return (false);
	prev_index = current_index - 1;
	while (prev_index >= 0 && command[prev_index] == ' ')
		prev_index--;
	next_index = current_index + 1;
	while (command[next_index] && command[next_index] == ' ')
		next_index++;
	if (prev_index < 0 || command[next_index] == '\0')
		return (false);
	if (command[prev_index] == '|' || command[prev_index] == '<'
		|| command[prev_index] == '>')
		return (false);
	if (command[next_index] == '|' || command[next_index] == '\0')
		return (false);
	return (true);
}

bool	validate_pipes(char c, const char *command, int current_index,
	struct s_cmd_state *state)
{
	if (!command || !state)
		return (false);
	if (is_in_quotes(state))
		return (true);
	if (c == '|')
	{
		if (!check_pipe_surroundings(command, current_index))
			return (false);
		state->last_char_is_pipe = true;
		state->in_cd_command = false;
		state->command_started = false;
	}
	else
	{
		if (!isspace(c))
			state->command_started = true;
		state->last_char_is_pipe = false;
	}
	return ((true));
}
