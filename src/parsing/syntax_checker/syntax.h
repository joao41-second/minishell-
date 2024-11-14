/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:17:26 by rpires-c          #+#    #+#             */
/*   Updated: 2024/11/14 16:32:05 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define SYNTAX_H
#ifdef SYNTAX_H

# include "../../minishell.h"
# include <stdbool.h>
# include <ctype.h>

typedef struct s_cmd_state
{
	bool	in_single_quote;
	bool	in_double_quote;
	bool	last_char_is_pipe;
	bool	last_char_is_redirection;
	bool	env_variable;
	bool	command_started;
	int		consecutive_redirections;
	bool	redirection_needs_target;
	int		consecutive_dots;
	int		cd_arg_count;
	bool	in_cd_command;
	bool	wildcard_exception;
}	t_cmd_state;


bool	is_cd_command_start(
				const char *command,
				int current_index,
				struct s_cmd_state *state);
bool	handle_cd_arguments(
				char c,
				const char *command,
				int current_index,
				struct s_cmd_state *state);
bool	update_cd_state(
				char c,
				struct s_cmd_state *state);
bool	validate_cd_command(
				char c,
				const char *command,
				int current_index,
				struct s_cmd_state *state);
bool	is_in_quotes(
				const struct s_cmd_state *state);
void	handle_quotes(
				char c,
				struct s_cmd_state *state);
bool	validate_env_variable(
				char c,
				const char *command,
				int current_index,
				struct s_cmd_state *state);
bool	check_redirection_character(
				char c,
				struct s_cmd_state *state);
bool	handle_non_redirection_character(
				char c,
				struct s_cmd_state *state);
bool	validate_redirections(
				char c,
				struct s_cmd_state *state);
bool	validate_pipes(
				char c,
				const char *command,
				int current_index,
				struct s_cmd_state *state);
bool	validate_special_chars(
				char c,
				const struct s_cmd_state *state);
bool		initialize_command_state(
				char c,
				struct s_cmd_state *state);
bool		handle_quotes_and_spaces(
				char c,
				struct s_cmd_state *state);
bool		process_character(
				char c,
				const char *command,
				int i,
				struct s_cmd_state *state);
bool		validate_command_structure(
				const char *command,
				struct s_cmd_state *state);
bool		validate_syntax(
				const char *command);
#endif 