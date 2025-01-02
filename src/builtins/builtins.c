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

void	change_and_free(t_minis *mini, int set, t_list_ **token, char chage)
{
	if (chage == 'h')
		herdoc(mini, set, get_token(*token)->redirection_source);
	else
		change_file(mini, set, chage, get_token(*token));
	ft_free_node(token, free_token);
	ft_free_node(token, free_token);
}

int	open_error(t_minis *mini, t_list_ **token)
{
	int	i;

	i = open(get_token(*token)->redirection_target, O_WRONLY);
	if (i == -1)
	{
		perror("bash");
		mini->comand = 1;
		mini->exit_code_error = 1;
		ft_free_node(token, free_token);
		ft_free_node(token, free_token);
		return (FALSE);
	}
	close(i);
	ft_free_node(token, free_token);
	ft_free_node(token, free_token);
	return (TRUE);
}

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
			change_and_free(mini, set, &token, '>');
		if (ft_strncmp(get_token(token)->token, ">>", 4) == 0)
			change_and_free(mini, set, &token, 'n');
		if (ft_strncmp(get_token(token)->token, "<<", 4) == 0)
			change_and_free(mini, set, &token, 'h');
		if (ft_strncmp(get_token(token)->token, "<", 4) == 0)
			if (open_error(mini, &token) == FALSE)
				return ;
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
	chek_herdoc(mini, 1);
}
