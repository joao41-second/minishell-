/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rui <rui@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:12:36 by jperpct           #+#    #+#             */
/*   Updated: 2025/01/30 17:43:10 by rui              ###   ########.fr       */
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

void	setup_pipe(int term[2])
{
	pipe(term);
	dup2(1, term[0]);
}

void	restore_stdout(int term[2])
{
	dup2(term[0], 1);
	close(term[1]);
	close(term[0]);
}

void	process_builtin(t_minis *mini, t_list_ *save)
{
	t_token	*token;
	char	*comand;

	token = get_token(mini->tokens);
	comand = expand_env(token->token, mini);
	if (mini->comand != 1)
		if_builtins(mini, comand);
	else
		mini->comand = 0;
	ft_free(comand, NULL);
	mini->tokens = save;
}

void	builtins(t_minis *mini)
{
	int		term[2];
	t_list_	*save;

	save = mini->tokens;
	if (!save)
		return ;
	setup_pipe(term);
	redirect_bil(save, mini);
	dell_redir(&mini->tokens);
	set_new_comand(&mini->tokens);
	if (chek_comand_exit(&mini->tokens) != TRUE)
		return ;
	process_builtin(mini, save);
	restore_stdout(term);
}
