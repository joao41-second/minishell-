#include "../../minishell.h"

void free_env_matrix(char **env_matrix)
{
    int i;

    if (!env_matrix)
        return;
    i = 0;
    while (env_matrix[i])
    {
        free(env_matrix[i]);
        i++;
    }
    free(env_matrix);
}

int extract_quoted_string(char *line, int *i, char **token)
{
    char quote;
    int start;
    int len;

    quote = line[*i];
    start = *i;
    (*i)++;
    while (line[*i] && line[*i] != quote)
        (*i)++;
    if (line[*i] == quote)
        (*i)++;
    len = *i - start;
    *token = (char *)malloc(len + 1);
    if (!*token)
        return (0);
    ft_strlcpy(*token, line + start, len + 1);
    return (1);
}

int is_quoted_string_command(char *str, char **env_matrix)
{
    if ((str[0] == '"' || str[0] == '\'') && 
        str[0] == str[strlen(str) - 1])
    {
        char *stripped = ft_substr(str, 1, strlen(str) - 2);
        char *path = find_path(stripped, env_matrix);
        free(stripped);
        if (path)
        {
            free(path);
            return 1;
        }
    }
    return 0;
}