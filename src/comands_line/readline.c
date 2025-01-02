/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:36:26 by jperpct           #+#    #+#             */
/*   Updated: 2025/01/02 16:46:03 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

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

char	*ft_strcpy(char *dst, const char *src)
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
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

void	print_token_list(t_list_ *list)
{
	t_list_	*current;
	t_token	*token;

	current = list;
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

void	set_error_env(t_minis *mini)
{
	t_env	*code_error_env;

	mini->env = ft_node_start(mini->env);
	code_error_env = list_to_env(
			(t_list_ *)get_list(mini->env, "?", get_env_node));
	ft_free(code_error_env->content, NULL);
	code_error_env->content = ft_itoa(mini->exit_code_error);
	code_error_env = list_to_env(
			(t_list_ *)get_list(mini->env_org, "?", get_env_node));
	ft_free(code_error_env->content, NULL);
	code_error_env->content = ft_itoa(mini->exit_code_error);
}

void excute_comand(t_minis *mini)
{
	t_list_	*exec_list;
	int		temp;

	temp = 0;
	if (get_signal(0) != 1)
		mini->exit_code_error = get_signal(0);
	set_error_env(mini);
	check_syntax(mini->line);
	mini->tokens = tokenize_and_check_bash_command(mini);
	exec_list = token_merger(mini);
	process_merged_list(exec_list, mini);
	fflush(stdout);
	free_list(exec_list, free_token);
	free_list(mini->tokens, free_token);
}

void	start_prompt_and_sig(t_minis *mini)
{
	char	*prompt;
	char	*line;

	server();
	line = readline("prompt " );
	if (line == NULL)
		ft_exit_end(0);
	if (mini->line)
	{
		ft_free(mini->line, NULL);
		mini->line = NULL;
	}
	mini->line = ft_strdup(line);
	add_history(line);
	free(line);
}

void	start_shell(t_minis mini)
{
	char	**envp;

	getcwd(mini.path, PATH_MAX);
	envp = NULL;
	mini.exit_code_error = 0;
	set_error_env(&mini);
	while (1)
	{
		get_signal(1);
		start_prompt_and_sig(&mini);
		if (mini.line[0] != '\0')
			excute_comand(&mini);
		set_error_env(&mini);
		getcwd(mini.path, PATH_MAX);
		mini.line = NULL;
	}
	free_list(mini.env, free_env);
	free_list(mini.env_org, free_env);
}
