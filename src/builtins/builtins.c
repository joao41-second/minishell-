/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:12:36 by jperpct           #+#    #+#             */
/*   Updated: 2024/12/17 10:21:13 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

void	chek_herdoc(t_minis	*mini, int set)
{
	int		i;
	t_list_	*token;
	t_token	*element;

	i = -1;
	token = mini->tokens;
	if (set == 1)
		token = mini->tokens_copy;
	token = ft_node_start(token);
	while (token != NULL)
	{
		if (ft_strncmp(get_token(token)->token, ">", 4) == 0)
		{
			change_file(mini, set, '>', get_token(token));
			ft_free_node(&token, free_token);
			ft_free_node(&token, free_token);
		}
		if (ft_strncmp(get_token(token)->token, ">>", 4) == 0)
		{
			change_file(mini, set, 'n', get_token(token));
			ft_free_node(&token, free_token);
			ft_free_node(&token, free_token);
		}
		if (ft_strncmp(get_token(token)->token, "<<", 4) == 0)
		{
			herdoc(mini, set, get_token(token)->redirection_source);
			ft_free_node(&token, free_token);
			ft_free_node(&token, free_token);
		}
		if (ft_strncmp(get_token(token)->token, "<", 4) == 0)
		{
			i = open(get_token(token)->redirection_target, O_WRONLY);
			if (i == -1)
			{
				perror("bash");
				mini->comand = 1;
				mini->exit_code_error = 1;
				return ;
			}
			ft_free_node(&token, free_token);
			ft_free_node(&token, free_token);
		}
		token = token->next;
	}
}

t_token	*get_token(t_list_ *list)
{
	t_token	*set;

	set = (t_token *)list->content;
	return (set);
}

void	builtins(t_minis	*mini)
{
	t_token	*token;
	t_list_	*save;
	char	*comand;

	save = mini->tokens;
	if (mini->tokens == NULL)
		return ;
	chek_herdoc(mini, 0);
	token = get_token(mini->tokens);
	comand = expand_env(token->token, mini);
	if (mini->comand != 1)
	{
		if (ft_strncmp(comand, "env", 4) == 0)
			ft_env(mini);
		if (ft_strncmp(comand, "exit", 10) == 0)
			ft_exit(mini);
		if (ft_strncmp(comand, "cd", 10) == 0)
			ft_cd(mini);
		if (ft_strncmp(comand, "pwd", 10) == 0)
			ft_pwd(mini);
		if (ft_strncmp(comand, "unset", 10) == 0)
			ft_unset(mini);
		if (ft_strncmp(comand, "export", 10) == 0)
			ft_export(mini);
		if (ft_strncmp(comand, "echo", 10) == 0)
			ft_echo(mini);
	}
	else
		mini->comand = 0;
	ft_free(comand, NULL);
	mini->tokens = save;
	chek_herdoc(mini, 1);
}
