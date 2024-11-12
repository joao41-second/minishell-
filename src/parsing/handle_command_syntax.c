/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command_syntax.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:22:57 by rpires-c          #+#    #+#             */
/*   Updated: 2024/11/11 14:21:12 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

bool	initialize_command_state(char c, struct s_cmd_state *state)
{
	if (!state->command_started && isspace(c))
		return (false);
	if (!state->command_started && !isspace(c))
		state->command_started = true;
	return (true);
}

bool	validate_command_structure(const char *command,
									struct s_cmd_state *state)
{
	int		i;
	char	c;

	i = 0;
	while (command[i] != '\0')
	{
		c = command[i];
		if (!handle_quotes_and_spaces(c, state))
		{
			i++;
			continue ;
		}
		if (!process_character(c, command, i, state))
			return (false);
		i++;
	}
	return (true);
}
