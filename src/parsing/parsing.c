/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:01:16 by rpires-c          #+#    #+#             */
/*   Updated: 2024/10/17 17:16:42 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    bool in_single_quote;
    bool in_double_quote;
    bool escape_next;
    int pipe_count;
    bool has_redirect_in;
    bool has_redirect_out;
    bool has_heredoc;
    bool has_append;
    char *error_msg;
} ParserState;

// Initialize parser state
void init_parser_state(ParserState *state) {
    state->in_single_quote = false;
    state->in_double_quote = false;
    state->escape_next = false;
    state->pipe_count = 0;
    state->has_redirect_in = false;
    state->has_redirect_out = false;
    state->has_heredoc = false;
    state->has_append = false;
    state->error_msg = NULL;
}

// Check if character is a valid environment variable name character
bool is_valid_env_char(char c) {
    return (c >= 'A' && c <= 'Z') || 
           (c >= 'a' && c <= 'z') || 
           (c >= '0' && c <= '9') || 
           c == '_';
}

// Check environment variable syntax
bool check_env_var_syntax(const char *str, int *i) {
    if (str[*i] != '$') return false;
    
    (*i)++;
    // Handle $? special case
    if (str[*i] == '?') {
        (*i)++;
        return true;
    }
    
    // Check if there's at least one valid character after $
    if (!is_valid_env_char(str[*i])) {
        return false;
    }
    
    // Continue checking valid characters
    while (is_valid_env_char(str[*i])) {
        (*i)++;
    }
    (*i)--; // Back up one since loop will increment
    return true;
}

// Check redirection syntax
bool check_redirection_syntax(const char *str, int *i, ParserState *state) {
    char current = str[*i];
    char next = str[*i + 1];
    
    if (current == '<') {
        if (next == '<') {
            state->has_heredoc = true;
            (*i)++;
            // Should check for delimiter in actual implementation
        } else {
            state->has_redirect_in = true;
        }
        return true;
    } else if (current == '>') {
        if (next == '>') {
            state->has_append = true;
            (*i)++;
        } else {
            state->has_redirect_out = true;
        }
        return true;
    }
    return false;
}

// Main syntax checking function
bool check_syntax(const char *input, char **error_msg) {
    ParserState state;
    init_parser_state(&state);
    int len = strlen(input);
    
    for (int i = 0; i < len; i++) {
        char c = input[i];
        
        // Handle escape character
        if (c == '\\' && !state.in_single_quote) {
            if (i == len - 1) {
                *error_msg = "Incomplete escape sequence";
                return false;
            }
            i++;
            continue;
        }
        
        // Handle quotes
        if (c == '\'' && !state.in_double_quote) {
            state.in_single_quote = !state.in_single_quote;
            continue;
        }
        
        if (c == '"' && !state.in_single_quote) {
            state.in_double_quote = !state.in_double_quote;
            continue;
        }
        
        // Handle environment variables
        if (c == '$' && !state.in_single_quote) {
            if (!check_env_var_syntax(input, &i)) {
                *error_msg = "Invalid environment variable syntax";
                return false;
            }
            continue;
        }
        
        // Handle pipes
        if (c == '|' && !state.in_single_quote && !state.in_double_quote) {
            state.pipe_count++;
            if (i == 0 || i == len - 1 || input[i - 1] == '|' || input[i + 1] == '|') {
                *error_msg = "Invalid pipe syntax";
                return false;
            }
            continue;
        }
        
        // Handle redirections
        if ((c == '<' || c == '>') && !state.in_single_quote && !state.in_double_quote) {
            if (!check_redirection_syntax(input, &i, &state)) {
                *error_msg = "Invalid redirection syntax";
                return false;
            }
            continue;
        }
    }
    
    // Check for unclosed quotes
    if (state.in_single_quote) {
        *error_msg = "Unclosed single quote";
        return false;
    }
    if (state.in_double_quote) {
        *error_msg = "Unclosed double quote";
        return false;
    }
    
    return true;
}

// Test function
void test_syntax(const char *input) {
    char *error_msg = NULL;
    bool is_valid = check_syntax(input, &error_msg);
    
    printf("Input: %s\n", input);
    printf("Result: %s\n", is_valid ? "Valid" : "Invalid");
    if (error_msg) {
        printf("Error: %s\n", error_msg);
    }
    printf("\n");
}

int main()
{
    test_syntax("echo 'Hello World'");  // Valid
    test_syntax("echo \"Hello $USER\"");  // Valid
    test_syntax("cat file.txt | grep 'pattern'");  // Valid
    test_syntax("echo \"unclosed");  // Invalid
    test_syntax("cat < input.txt > output.txt");  // Valid
    test_syntax("echo $HOME");  // Valid
    test_syntax("echo $?");  // Valid
    test_syntax("cat << EOF");  // Valid
    test_syntax("echo >> output.txt");  // Valid
    test_syntax("|");  // Invalid
    test_syntax("echo $*invalid");  // Invalid
    
    return 0;
}
