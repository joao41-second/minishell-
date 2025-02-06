/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_variables_syntax.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:26:06 by rpires-c          #+#    #+#             */
/*   Updated: 2024/11/18 14:12:15 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

bool	validate_env_variable(char c, const char *command,
								int current_index,
								struct s_cmd_state *state)
{
	if (c == '$' && !state->in_single_quote && !state->in_double_quote)
	{
		if (command[current_index + 1] == '?')
		{
			state->wildcard_exception = true;
			return (true);
		}
		state->env_variable = true;
	}
	return (true);
}
