/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rui <rui@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:36:26 by jperpct           #+#    #+#             */
/*   Updated: 2025/01/30 16:30:00 by rui              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

int chek_expand(char *str,t_minis *mini)
{
	char *line;

	line = expand_env(ft_strdup(str), mini);
	if(ft_strncmp(line, "", 10) == 0)
	{
		ft_free(line, NULL);
		return (FALSE);
	}
	ft_free(line, NULL);
	return (TRUE);
}
bool	is_allspace(char *str)
{
	int i;

	i = -1;
	while (str[++i] != '\0')
	{
        if (!is_whitespace(str[i]))
            return (false);
    }
	ft_free(str,NULL);
	return (true);
}

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
//	printf("Token List:\n");
//	printf("-----------------------------------\n");
	if(current == NULL)
		return;
	current = ft_node_start(current);
	while (current)
	{
		token = (t_token *)current->content;
		if (token)
		{
			printf("Token: %s\n", token->token ? token->token : "NULL");
			
            printf("Type: %s\n", token->type ? token->type : "NULL");
			/*
			if (token->redirection_target)
				printf("Redirection Target: %s\n", token->redirection_target);
			if (token->redirection_source)
				printf("Redirection Source: %s\n", token->redirection_source);*/
		}
		else
			printf("Empty token\n");
	//	printf("-----------------------------------\n");
		current = current->next;
	}
}
/*
void print_command_tree(t_btree *node, int level)
{
    if (!node)
        return;
    for (int i = 0; i < level; i++)
        printf("  ");
		if (node->cmd)
        printf("%s\n", node->cmd);
		if(node->redir != NULL)
		print_token_list(node->redir);
    if (node->left)
    {
        for (int i = 0; i < level; i++)
            printf("  ");
        printf("Left:\n");	
        print_command_tree(node->left, level + 1);
    }
    if (node->right)
    {
        for (int i = 0; i < level; i++)
            printf("  ");
        printf("Right:\n");
        print_command_tree(node->right, level + 1);
    }
}*/

void print_btree(t_btree *node)
{
    if (node == NULL) {
        return;
    }
	print_btree(node->left);
	printf("%s\n", node->cmd);
	print_btree(node->right);
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

void	free_tree(t_btree *node)
{
	if (node == NULL)
		return ;
	free_tree(node->left);
	free_tree(node->right);
	ft_free(node, NULL);
}

void excute_comand_ve(t_minis *mini)
{
	pid_t pid;
	t_btree *exec_list;
	int temp;
	int status;

	temp = 0;
    if (get_signal(0) != 1)
        mini->exit_code_error = get_signal(0);
    set_error_env(mini);
    mini->tokens = tokenize_and_check_bash_command(mini);
    exec_list = token_merger(mini);
    pid = fork();
    if (pid == 0)
    {
		set_redir(mini->tokens,&exec_list);
        temp = process_tree(exec_list, mini, 1);
        ft_exit_end(temp);
    }
	waitpid(pid, &status, 0);

//	printf("status error %d\n", WSTOPSIG(status));
	mini->exit_code_error =  WSTOPSIG(status);
	
	
    free_tree(exec_list);
	
}

void	start_prompt_and_sig(t_minis *mini)
{
//	char	*prompt;
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
	if (!is_allspace(line))
	{
		mini->line = ft_strdup(ft_strdup(line));
		add_history(line);
	}else
	{
		ft_free(mini->line, NULL);
		mini->line = NULL;
	}
	free(line);
}

int	chek_comand(t_minis mini)
{
	t_list_	*list;
	int		bil;
	int		pipe;

	list = mini.tokens;
	pipe = 0;
	bil = 0;
	while (list != NULL)
	{
		if (ft_strncmp(get_token(list)->type, "pipe", 10) == 0)
			pipe++;
		if (chek_biltin(&get_token(list)->token) == TRUE && ft_strncmp(get_token(list)->type,"command",30) == 0)
			bil = 1; 
		list = list->next;
	}
	if(pipe != 0)
		return (FALSE);
	if(bil != 0 && pipe == 0)
		return (TRUE);
	return (FALSE);
}

void	excute_comand(t_minis *mini)
{
	if (get_signal(0) != 1)
		mini->exit_code_error = get_signal(0);
	set_error_env(mini);
	mini->exit_code_error = 0;	
	mini->tokens = tokenize_and_check_bash_command(mini);
	mini->tokens_copy = tokenize_and_check_bash_command(mini);
	convert_chekline(mini);
	if(chek_comand(*mini) == TRUE)
	 	builtins(mini);
	else
		excute_comand_ve(mini);
	//print_token_list(mini->tokens);
	free_list(mini->tokens, free_token);
	free_list(mini->tokens_copy, free_token);
	mini->tokens = NULL;
	mini->tokens_copy = NULL;
	
}

void	start_shell(t_minis mini)
{
	getcwd(mini.path, PATH_MAX);
	mini.exit_code_error = 0;
	set_error_env(&mini);
	while (1)
	{
		get_signal(1);
		start_prompt_and_sig(&mini);

	//	check_syntax(mini.line);
		if ( mini.line != NULL && chek_expand(mini.line, &mini) == TRUE &&  !is_allspace(ft_strdup(mini.line)))
			excute_comand(&mini);
		else
		 mini.exit_code_error = 0;
		set_error_env(&mini);
		getcwd(mini.path, PATH_MAX);
		ft_free(mini.line,NULL);
		mini.line = NULL;
	}
	free_list(mini.env, free_env);
	free_list(mini.env_org, free_env);
}
