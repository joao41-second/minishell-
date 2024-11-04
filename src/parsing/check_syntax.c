#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

bool validate_syntax(const char *command) {
    bool in_single_quote = false;
    bool in_double_quote = false;
    bool last_char_is_pipe = false;
    bool last_char_is_redirection = false;
    bool env_variable = false;
    bool command_started = false;
    int consecutive_redirections = 0;
    bool redirection_needs_target = false;
    int consecutive_dots = 0;
    int cd_arg_count = 0;
    bool in_cd_command = false;
    
    int i = 0;
    while (command[i] != '\0') {
        char c = command[i];
        
        if (!command_started && isspace(c)) {
            i++;
            continue;
        }

        if (!command_started && !isspace(c)) {
            command_started = true;
        }

        if (c == '\'' && !in_double_quote) {
            in_single_quote = !in_single_quote;
            i++;
            continue;
        } else if (c == '"' && !in_single_quote) {
            in_double_quote = !in_double_quote;
            i++;
            continue;
        }

        if (in_double_quote || in_single_quote) {
            i++;
            continue;
        }

        if (i == 0 || isspace(command[i - 1])) {
            if (strncmp(command + i, "cd", 2) == 0 && 
                (command[i + 2] == '\0' || isspace(command[i + 2]))) {
                in_cd_command = true;
                cd_arg_count = 0;
            }
        }

        if (in_cd_command) {
            if (isspace(c)) {
                if (cd_arg_count > 0) {
                    int j = i + 1;
                    while (command[j] != '\0' && isspace(command[j])) j++;
                    if (command[j] == '|' || command[j] == '\0') {
                        in_cd_command = false;
                        consecutive_dots = 0;
                        i++;
                        continue;
                    }
                }
                cd_arg_count++;
                consecutive_dots = 0;
                if (cd_arg_count > 2) {
                    int j = i + 1;
                    while (command[j] != '\0' && isspace(command[j])) j++;
                    if (command[j] != '|') {
                        return false;
                    }
                }
            } else if (c == '.') {
                consecutive_dots++;
                if (consecutive_dots > 2) return false;
            } else if (c == '|') {
                in_cd_command = false;
                consecutive_dots = 0;
            } else if (!isalnum(c) && c != '/' && c != '-'
                    && c != '~' && c != '.') {
                in_cd_command = false;
            }
        }

        if (c == '$' && !in_single_quote && !in_double_quote) {
            if (command[i + 1] == '?') {
                i++;  
                i++;
                continue;
            }
            env_variable = true;
        } else if (env_variable) {
            if (!isalpha(c) && c != '_') {
                return false; 
            }
            env_variable = false;
        }

        if ((c == '>' || c == '<') && !in_single_quote && !in_double_quote) {
            consecutive_redirections++;
            if (consecutive_redirections > 2) {
                return false;
            }
            if (last_char_is_redirection) {
                if (c == '<' && command[i - 1] == '>') {
                    return false;
                }
            }
            redirection_needs_target = true;
            last_char_is_redirection = true;
        } else {
            if (redirection_needs_target) {
                if (isspace(c)) {
                    i++;
                    continue;
                }
                if (c == '|') {
                    return false;
                }
                redirection_needs_target = false;
            }
            consecutive_redirections = 0;
            last_char_is_redirection = false;
        }

        if (c == '|' && !in_single_quote && !in_double_quote) {
            if (i > 0 && command[i - 1] == '"') {
                i++;
                continue;
            }
            if (i == 0 || command[i + 1] == '\0' || 
                last_char_is_pipe || last_char_is_redirection) {
                return false;
            }
            last_char_is_pipe = true;
            in_cd_command = false;
        } else {
            last_char_is_pipe = false;
        }

        if (!in_single_quote && !in_double_quote &&
            (c == '*' || c == '?' || c == '[' || c == ']')) {
            return false;
        }
        i++;
    }

    if (in_single_quote || in_double_quote || last_char_is_pipe || 
        last_char_is_redirection || redirection_needs_target) return false;

    return true;
}

void test_syntax(const char *command, bool expected) {
    bool result = validate_syntax(command);
    printf("Command: %s | Expected: %d Result: %d | %s\n",
           command, expected, result, (result == expected) ? "PASS" : "FAIL");
}


int main() {
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
    test_syntax(">>>", false);
    test_syntax("<<<", false);
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
    test_syntax("cd ...", false);  
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
}