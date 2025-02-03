/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:12:36 by jperpct           #+#    #+#             */
/*   Updated: 2025/01/29 11:31:32 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
#include <unistd.h>

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

void	set_term(int *term)
{
	pipe(term);
	dup2(1, term[1]);
	dup2(0, term[0]);
}

void	set_ute_files(int *term)
{
	dup2(term[1], 1);
	dup2(term[0], 0);
	close(term[1]);
	close(term[0]);
}

void	builtins(t_minis	*mini)
{
	t_token	*token;
	t_list_	*save;
	char	*comand;
	int		term[2];

	set_term(term);
	token = NULL;
	save = mini->tokens;
	if (mini->tokens == NULL)
		return ;
	redirect_bil(save, mini);
	dell_redir(&mini->tokens);
	set_new_comand(&mini->tokens);
	if (chek_comand_exit(&mini->tokens) != TRUE)
		return ;
	save = mini->tokens;
	token = get_token(mini->tokens);
	comand = expand_env(token->token, mini);
	if (mini->comand != 1)
		if_builtins(mini, comand);
	else
		mini->comand = 0;
	ft_free(comand, NULL);
	mini->tokens = save;
	set_ute_files(term);
}
