/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe_syntax.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:24:09 by rpires-c          #+#    #+#             */
/*   Updated: 2024/11/11 14:28:52 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

bool	validate_pipes(char c, const char *command,
							int current_index,
							struct s_cmd_state *state)
{
	if (c == '|' && !is_in_quotes(state))
	{
		if (current_index > 0 && command[current_index - 1] == '"')
			return (true);
		if (current_index == 0 || command[current_index + 1] == '\0'
			|| state->last_char_is_pipe || state->last_char_is_redirection)
			return (false);
		state->last_char_is_pipe = true;
		state->in_cd_command = false;
	}
	else
		state->last_char_is_pipe = false;
	return (true);
}
