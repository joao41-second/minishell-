/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:16:13 by rpires-c          #+#    #+#             */
/*   Updated: 2025/01/29 15:00:13 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

void	init_validator_state(struct s_cmd_state *state)
{
	state->in_single_quote = false;
	state->in_double_quote = false;
	state->last_char_is_pipe = false;
	state->last_char_is_redirection = false;
	state->env_variable = false;
	state->command_started = false;
	state->consecutive_redirections = 0;
	state->redirection_needs_target = false;
	state->cd_arg_count = 0;
	state->in_cd_command = false;
	state->wildcard_exception = false;
}

bool	validate_special_chars(char c,
									const struct s_cmd_state *state)
{
	if (!is_in_quotes(state) && (c == '*'
			|| (c == '?' && state->wildcard_exception == false)
			|| c == '[' || c == ']'))
		return (false);
	return (true);
}

bool	process_character(char c, const char *command,
							int i, struct s_cmd_state *state)
{
	handle_quotes(c, state);
	if (is_in_quotes(state))
	{
		handle_quotes(c, state);
		return (true);
	}
	return (validate_cd_command(c, command, i, state)
		&& validate_env_variable(c, command, i, state)
		&& validate_redirections(c, command, i, state)
		&& validate_pipes(c, command, i, state)
		&& validate_special_chars(c, state));
}

int	check_syntax(const char *command)
{
	struct s_cmd_state	state;
	int					i;
	char				c;

	init_validator_state(&state);
	i = 0;
	while (command[i] != '\0')
	{
		c = command[i];
		if (!process_character(c, command, i, &state))
			return (2);
		i++;
	}
	if (state.in_single_quote || state.in_double_quote
		|| state.last_char_is_pipe || state.last_char_is_redirection
		|| state.redirection_needs_target)
		return (2);
	return (0);
}

/* void	test_syntax(const char *command, bool expected)
{
    bool result;

	result = validate_syntax(command);
    printf("Command: %s | Expected: %d Result: %d | %s\n",
           command, expected, result, (result == expected) ? "PASS" : "FAIL");
}

 int main()
{
    test_syntax("cd .....", true);  
    test_syntax("", true);
    test_syntax("''", true);
    test_syntax("\"|", false);
    test_syntax("a || b", false);
    test_syntax("'||'", true);
    test_syntax("\"||\"", true);
    test_syntax("\"", false);
    test_syntax("\"\"", true);
    test_syntax("\"\"\"", false);
    test_syntax("'''", false);
    test_syntax("       ", true);
    test_syntax("a", true);
    test_syntax("'a\"", false);
    test_syntax("echo '>abc'", true);
    test_syntax("echo '>>'", true);
    test_syntax("echo '>>>'", true);
    test_syntax("echo 'Hello World'", true);
    test_syntax("echo \"12\"", true);
    test_syntax("echo \"123\\$456\"", true);
    test_syntax("echo \"$=TEST\"", true);
    test_syntax("echo \"|$TEST|\"", true);
    test_syntax("echo \"'$HOME'\"\"''\"", true);
    test_syntax("echo '$HOME'\" ", false);
    test_syntax("echo '$HOME' ", true);
    test_syntax("echo \"$HOME\" ", true);
    test_syntax("echo \"'$HOME'\" ", true);
    test_syntax("echo '\"$HOME\"' ", true);
    test_syntax("echo \"\"\"\"", true);
    test_syntax("echo \"\"\"", false);
    test_syntax("echo \"'\"", true);
    test_syntax("echo '\"'", true);
    test_syntax("cat file.txt | grep 'pattern'", true);
    test_syntax("echo \"cat lol.c", false);
    test_syntax("echo 'unclosed", false);
    test_syntax("echo '|'", true);
    test_syntax("echo \"|\"", true);
    test_syntax("\"|\"\"ls\"\"-la\"\"|\"|\"ls\"", true);
    test_syntax("'|'\"ls\"\"-la\"\"|\"|'ls'", true);
    test_syntax(">", false);
    test_syntax("<", false);
    test_syntax(">>", false);
    test_syntax("<<", false);
    test_syntax("a >>> b", false);
    test_syntax("a <<< b", false);
    test_syntax("ls > ", false);
    test_syntax("ls < ", false);
    test_syntax("echo hi <", false);
    test_syntax("echo hi >< try", false);
    test_syntax("ls <> ls", true);
    test_syntax("ls < > ls", true);
    test_syntax(">a> output.txt", true);
    test_syntax("cat < input.txt > output.txt", true);
    test_syntax("cat << valid", true);
    test_syntax("echo >> output.txt", true);
    test_syntax("echo >> ", false);
    test_syntax("echo << ", false);
    test_syntax("<<'EOF", false);
    test_syntax("> cat", true);
    test_syntax("< cat", true);
    test_syntax("cat    <| ls", false);
    test_syntax("< $a |", false);
    test_syntax("< $a | ls", true);
    test_syntax("< $A", true);
    test_syntax("> $po", true);
    test_syntax("echo >>> invalid", false);
    test_syntax("echo <<< invalid", false);
    test_syntax("|", false);
    test_syntax("| $", false);
    test_syntax("ls |", false);
    test_syntax("| >", false);
    test_syntax("> $po |", false);
    test_syntax("> $po | echo", true);
    test_syntax("| echo oi", false);
    test_syntax("|     |", false);
    test_syntax("echo hi | >", false);
    test_syntax("echo hi | <", false);
    test_syntax("echo hi | < |", false);
    test_syntax("echo hi | > >>", false);
    test_syntax("echo hi |   |", false);
    test_syntax("echo hi |  \"|\"", true);
    test_syntax("| invalid |invalid", false);
    test_syntax("valid|invalid", true);
    test_syntax("$HOME", true);
    test_syntax("$_HOME", true);
    test_syntax("$1HOME", false);
    test_syntax("$_1HOME", true);
    test_syntax("$_1HO_M2E_", true);
    test_syntax("$_HO_ME_", true);
    test_syntax("$_1", true);
    test_syntax("$_1_2_3_4_", true);
    test_syntax("$1_2_3_4_", false);
    test_syntax("$HOME123", true);
    test_syntax("$\"HOME\"", true);
    test_syntax("$'HOME'", true);
    test_syntax("\"$HOME\"", true);
    test_syntax("'$HOME'", true);
    test_syntax("asd$HOME", true);
    test_syntax("$HOMEasd", true);
    test_syntax("$HOME asd", true);
    test_syntax("asd $HOME", true);
    test_syntax("echo $HOME", true);
    test_syntax("echo \"Hello $USER\"", true);
    test_syntax("echo $?", true);
    test_syntax("echo \"$?\"", true);
    test_syntax("echo $?>", false);
    test_syntax("echo $\"HOME\"", true);
    test_syntax("echo $'HOME'", true);
    test_syntax("echo \"$HOME\"", true);
    test_syntax("echo asd$HOME", true);
    test_syntax("echo \"$HOME\"asd", true);
    test_syntax("echo asd\"$HOME\"", true);
    test_syntax("echo $\"HOME\"asd", true);
    test_syntax("echo $'HOME'asd", true);
    test_syntax("echo asd$'HOME'", true);
    test_syntax("echo $HOME$PATH$USER", true);
    test_syntax("echo \"$HOME$PATH$USER\"", true);
    test_syntax("echo '$HOME$PATH$USER'", true);
    test_syntax("echo $HOME,$PATH,$USER", true);
    test_syntax("echo '$HOME,$PATH,$USER'", true);
    test_syntax("echo \"$HOME,$PATH,$USER\"", true);
    test_syntax("cd", true);  
    test_syntax("cd /", true);  
    test_syntax("cd .", true);  
    test_syntax("cd ..", true);  
    test_syntax("cd ...", true);  
    test_syntax("cd.", true);  
    test_syntax("cd..", true);  
    test_syntax("cd...", true);
    test_syntax("cd ./", true);
    test_syntax("cd -", true);  
    test_syntax("cd ~", true);  
    test_syntax("cd ~user", true);  
    test_syntax("cd ~user/", true);  
    test_syntax("cd ~user/..", true);  
    test_syntax("cd ~/", true);  
    test_syntax("cd ~/-", true);  
    test_syntax("cd ~/test", true);  
    test_syntax("cd ./", true);  
    test_syntax("cd ./test", true);
    test_syntax("cd ./-", true);  
    test_syntax("cd -L", true);  
    test_syntax("cd ..\"", false);  
    test_syntax("cd \"..", false);  
    test_syntax("cd a/b", true);  
    test_syntax("cd \"/\"", true);  
    test_syntax("cd .. pwd", true); 
    test_syntax("cd / /", true);
    test_syntax("cd ~user/", true);
    test_syntax("cd -L /", true);
    test_syntax("cd ~user ~another", true);
    test_syntax("cd ~user/..", true);
    test_syntax("cd ~/test", true);
    test_syntax("\"$", false);
    test_syntax("echo $*HOME", false);
    test_syntax("ls && ls", true);
    test_syntax("ls || cat", false);
    test_syntax("ls[1]", false);
    test_syntax("ls[]", false);
    test_syntax("$?", true);
    test_syntax("echo $? | echo $PATH", true);
    test_syntax("echo test?", false);
    test_syntax("echo *.c", false);
    test_syntax("echo \"test?\"", true);
    test_syntax("export $NOT_EXISTENT | unset ", true);
    test_syntax("echo -nknknknk Hello", true);
    test_syntax("echo '-n' Hello", true);
    test_syntax("echo \\\\\\\\$USER$USER", true);
    test_syntax("echo \\\\\\\\$USER", true);
    test_syntax("echo \\\\1$USER", true);
    test_syntax("echo \"\\$\\$USER\\\\$USER\"\"$USER\"", true);
    test_syntax("echo \"\\-\\-n\" \"\\h\\e\\l\\l\\o\"", true);
    test_syntax("> file | cat < no_such_file", true);
    test_syntax("cd .. | cd ..", true); 
    test_syntax("cd ..|cd ..", true); 
    test_syntax("cd ..||cd ..", false);
    test_syntax("parsing/ | ls", true); 
    test_syntax("echo a > $USER | echo b, unset USER", true);
    test_syntax("echo a > $USER | echo b unset USER", true);
    test_syntax("echo a > $USER | echo b | unset USER", true);
    test_syntax("echo a > $USER", true);
    test_syntax("echo a > $USER | echo b, unset USER", true);
} */
