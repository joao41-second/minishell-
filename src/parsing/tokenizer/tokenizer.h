#define MINISHELL_H
#ifdef MINISHELL_H

typedef struct s_token
{
    char *token;
    char *type;
    char *redirection_target;
    char *redirection_source;
}	t_token;

#endif
