/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:36:26 by jperpct           #+#    #+#             */
/*   Updated: 2024/12/05 16:31:05 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stddef.h>

char	*ft_strndup(const char *src, size_t n)
{
	size_t	len;
	char	*dst;
	int		i;

	len = 0;
	i = 0;
	while (len < n && src[len])
		len++;
	dst = (char *)ft_malloc(len + 1, NULL);
	if (!dst)
		return (NULL);
	while ((size_t)i < len)
	{
		dst[i] = src[i];
		i++;
	}
	dst[len] = 0;
	return (dst);
}

char *ft_strcpy(char *dst, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return *(unsigned char *)s1 - *(unsigned char *)s2;
}

void print_token_list(t_list_ *list)
{
    t_list_ *current = list;
    t_token *token;

    printf("Token List:\n");
    printf("-----------------------------------\n");
    while (current)
    {
        token = (t_token *)current->content;
        if (token)
        {
            printf("Token: %s\n", token->token ? token->token : "NULL");
            printf("Type: %s\n", token->type ? token->type : "NULL");
			if (token->redirection_target)
                printf("Redirection Target: %s\n", token->redirection_target);
            if (token->redirection_source)
                printf("Redirection Source: %s\n", token->redirection_source);
        }
        else
            printf("Empty token\n");
        printf("-----------------------------------\n");
        current = current->next;
    }
}

void	start_shell(t_minis mini)
{
	char	*line;
	char	*prompt;

	server();
	while (1)
	{
		get_signal(1);
		server();
		prompt = get_shell_prefix(&mini);
		line = readline(prompt);
		mini.readline++;
		ft_free(prompt, NULL);
		if (line == NULL)
			break ;
		mini.line = line;
		if (mini.line[0] != '\0')
		{
			mini.exit_code_error = check_syntax(mini.line);
			mini.tokens = tokenize_and_check_bash_command(&mini);
			print_token_list(mini.tokens);
			free_list(mini.tokens, free_token);
		}
		builtins(&mini);
		getcwd(mini.path, PATH_MAX);
		add_history(line);
		free(line);
		mini.line = NULL;
	}
	free_list(mini.env, free_env);
	free_list(mini.env_org, free_env);
}
