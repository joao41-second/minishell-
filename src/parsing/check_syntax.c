/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:01:16 by rpires-c          #+#    #+#             */
/*   Updated: 2024/10/22 16:56:55 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    bool in_single_quote;
    bool in_double_quote;
    bool escape_next;
    bool had_valid_command;
    int pipe_count;
    bool has_redirect_in;
    bool has_redirect_out;
    bool has_heredoc;
    bool has_append;
    char *error_msg;
} ParserState;

void init_parser_state(ParserState *state) {
    state->in_single_quote = false;
    state->in_double_quote = false;
    state->escape_next = false;
    state->had_valid_command = false;
    state->pipe_count = 0;
    state->has_redirect_in = false;
    state->has_redirect_out = false;
    state->has_heredoc = false;
    state->has_append = false;
    state->error_msg = NULL;
}

bool is_whitespace(char c) {
    return c == ' ' || c == '\t' || c == '\n';
}

bool is_valid_first_char(char c) {
    return (c >= 'A' && c <= 'Z') || 
           (c >= 'a' && c <= 'z') || 
           c == '_' || c == '/' || 
           c == '.' || c == '-';
}

bool check_env_var_syntax(const char *str, int *i, ParserState *state) {
    if (str[*i] != '$') return false;
    
    (*i)++;  // Move past $
    
    // Handle $?, $", $'
    if (str[*i] == '?' || str[*i] == '_') {
        return true;
    }
    
    // Handle $" and $' special cases
    if (str[*i] == '"' || str[*i] == '\'') {
        char quote_type = str[*i];
        (*i)++;  // Move past the opening quote
        
        // Find the matching closing quote
        while (str[*i] && str[*i] != quote_type) {
            (*i)++;
        }
        
        if (str[*i] == quote_type) {
            (*i)++;  // Move past the closing quote
            return true;
        }
    }
    
    // Accept any character after $ since it might be a valid env var
    return true;
}

bool check_pipe_syntax(const char *input, int i, ParserState *state)
{
    int len = strlen(input);
    bool found_command = false;
    
    // Check backwards for a command before the pipe
    if (!state->had_valid_command) {
        int j = i - 1;
        while (j >= 0 && is_whitespace(input[j])) j--;
        if (j < 0) return false;
        while (j >= 0 && !is_whitespace(input[j]) && input[j] != '|') j--;
        if (j < 0 || input[j] == '|') return false;
    }
    
    // Check forwards for a command after the pipe
    int j = i + 1;
    while (j < len && is_whitespace(input[j])) j++;
    if (j >= len || input[j] == '|') return false;
    
    state->had_valid_command = true;
    return true;
}

bool check_syntax(const char *input, char **error_msg) {
    ParserState state;
    int len = strlen(input);
    bool found_non_space = false;
    
    init_parser_state(&state);
    for (int i = 0; i < len; i++) {
        char c = input[i];
        
        if (!is_whitespace(c))
            found_non_space = true;
        
        // Handle escape character
        if (c == '\\' && !state.in_single_quote) {
            state.escape_next = true;
            continue;
        }
        
        if (state.escape_next) {
            state.escape_next = false;
            continue;
        }
        
        // Handle single quotes
        if (c == '\'' && !state.in_double_quote) {
            state.in_single_quote = !state.in_single_quote;
            continue;
        }
        
        // Handle double quotes
        if (c == '"' && !state.in_single_quote) {
            state.in_double_quote = !state.in_double_quote;
            continue;
        }
        
        // Handle environment variables
        if (c == '$' && !state.in_single_quote) {
            if (!check_env_var_syntax(input, &i, &state)) {
                *error_msg = "Invalid environment variable syntax";
                return false;
            }
            i--;  // Decrement i since the loop will increment it
            continue;
        }
        
        // If this is the first non-quote character of a command, check if it's valid
        if (!is_whitespace(c) && !state.in_single_quote && !state.in_double_quote)
            state.had_valid_command = true;
    }
    
    // Check for unclosed quotes
    if (state.in_single_quote)
	{
        *error_msg = "Unclosed single quote";
        return false;
    }
    if (state.in_double_quote)
	{
        *error_msg = "Unclosed double quote";
        return false;
    }
    
    // Empty input is invalid
    if (!found_non_space)
	{
        *error_msg = "Empty command";
        return false;
    }
    
    return true;
}

void test_syntax(const char *input)
{
    char *error_msg = NULL;
    bool is_valid = check_syntax(input, &error_msg);
    printf("Input: %s\n", input);
    printf("Result: %s\n", is_valid ? "Valid" : "Invalid");
    if (error_msg)
        printf("Error: %s\n", error_msg);
    printf("\n");
}

int main()
{
    // Test cases
    test_syntax("echo 'Hello World'");  // Valid
    test_syntax("echo \"\"\"\"\"\"\"\"");  // Valid
    test_syntax("echo \"Hello $USER\"");  // Valid
    test_syntax("cat file.txt | grep 'pattern'");  // Valid
    test_syntax("echo \"unclosed");  // Invalid
    test_syntax("cat < input.txt > output.txt");  // Valid
    test_syntax("echo $HOME");  // Valid
    test_syntax("echo $?");  // Valid
    test_syntax("cat << EOF");  // Valid
    test_syntax("echo >> output.txt");  // Valid
    test_syntax("|");  // Invalid
    test_syntax("||");  // Invalid
    test_syntax("| |");  // Invalid
    test_syntax("| invalid |invalid");  // Invalid
    test_syntax("valid|invalid");  // Valid
    test_syntax("echo $*valid");  // Valid
    test_syntax("echo $\"valid\"");  // Valid
    test_syntax("echo $\'valid\'");  // Valid
    test_syntax("echo \"$valid\"");  // Valid
    test_syntax("echo \"$valid\"asd");  // Valid
    test_syntax("echo asd\"$valid\"");  // Valid
    test_syntax("echo $\"valid\"asd");  // Valid
	test_syntax("echo $\'valid\'asd");  // Valid
	
    return 0;
}
