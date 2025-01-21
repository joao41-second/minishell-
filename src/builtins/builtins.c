/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:12:36 by jperpct           #+#    #+#             */
/*   Updated: 2025/01/21 11:10:20 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
#include <unistd.h>

void	chek_herdoc(t_minis	*mini, int set)
{
	int		i;
	t_list_	*token;
	t_token	*element;

	i = 0;
	token = mini->tokens;
	if (set == 1)
		token = mini->tokens_copy;
	token = ft_node_start(token);
	while (token != NULL)
	{
		redir_if(mini, &token, set);
		token = token->next;
	}
}

void	if_builtins(t_minis *mini, char *comand)
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

void	builtins(t_minis	*mini)
{
	t_token	*token;
	t_list_	*save;
	char	*comand;
	int		term[2];

	pipe(term);
	dup2(1, term[0]);
	save = mini->tokens;
	if (mini->tokens == NULL)
		return ;
	chek_herdoc(mini, 0);
	token = get_token(mini->tokens);
	comand = expand_env(token->token, mini);
	if (mini->comand != 1)
		if_builtins(mini, comand);
	else
		mini->comand = 0;
	ft_free(comand, NULL);
	mini->tokens = save;
	dup2(term[0], 1);
	close(term[1]);
	close(term[0]);
}
