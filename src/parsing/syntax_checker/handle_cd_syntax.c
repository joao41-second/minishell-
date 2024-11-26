/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cd_syntax.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:22:09 by rpires-c          #+#    #+#             */
/*   Updated: 2024/11/18 14:11:22 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

bool	is_cd_command_start(const char *command, int current_index,
								struct s_cmd_state *state)
{
	if (current_index == 0 || ft_isspace(command[current_index - 1]))
	{
		if (ft_strncmp(command + current_index, "cd", 2) == 0
			&& (command[current_index + 2] == '\0'
				|| ft_isspace(command[current_index + 2])))
		{
			state->in_cd_command = true;
			state->cd_arg_count = 0;
			return (true);
		}
	}
	return (false);
}

bool	handle_space_character(const char *command,
								int current_index,
								struct s_cmd_state *state)
{
	int	i;

	i = 0;
	if (state->cd_arg_count > 0)
	{
		i = current_index + 1;
		while (command[i] != '\0' && ft_isspace(command[i]))
			i++;
		if (command[i] == '|' || command[i] == '\0')
		{
			state->in_cd_command = false;
			return (true);
		}
	}
	state->cd_arg_count++;
	if (state->cd_arg_count > 2)
	{
		i = current_index + 1;
		while (command[i] != '\0' && ft_isspace(command[i]))
			i++;
		if (command[i] != '|')
			return (false);
	}
	return (true);
}

bool	handle_cd_arguments(char c, const char *command,
							int current_index,
							struct s_cmd_state *state)
{
	if (ft_isspace(c))
		return (handle_space_character(command, current_index, state));
	return (true);
}

bool	update_cd_state(char c, struct s_cmd_state *state)
{
	if (c == '|')
	{
		state->in_cd_command = false;
		state->consecutive_dots = 0;
	}
	else if (!ft_isalnum(c) && c != '/' && c != '-' && c != '~' && c != '.')
		state->in_cd_command = false;
	return (true);
}

bool	validate_cd_command(char c, const char *command,
								int current_index,
								struct s_cmd_state *state)
{
	if (is_cd_command_start(command, current_index, state))
		return (true);
	if (state->in_cd_command)
	{
		if (!handle_cd_arguments(c, command, current_index, state))
			return (false);
		if (!update_cd_state(c, state))
			return (false);
	}
	return (true);
}
