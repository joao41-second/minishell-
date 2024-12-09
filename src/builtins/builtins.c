/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:12:36 by jperpct           #+#    #+#             */
/*   Updated: 2024/11/14 16:11:48 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	chek_herdoc(t_minis	*mini, int set)
{
	int	i;

	i = -1;
	while (mini->split[++i] != NULL)
	{
		if (ft_strncmp(mini->split[i], ">", 4) == 0)
			change_file(mini, set, '>');
		if (ft_strncmp(mini->split[i], ">>", 4) == 0)
			change_file(mini, set, 'n');
		if (ft_strncmp(mini->split[i], "<<", 4) == 0)
			herdoc(mini, set, mini->split[i + 1]);
	}
}

t_token *get_token(t_list_ *list)
{
	t_token *set;

	set = (t_token *)list->content;
	return (set);
}

void	builtins(t_minis	*mini)
{
	t_token *token;
	if (ft_strlen(mini->line) < 1)
		return ;
	mini->split = ft_split(mini->line, ' ');

	chek_herdoc(mini, 0);
	if (mini->tokens == NULL)
		return ;
	token = get_token(mini->tokens);
	if (ft_strncmp(token->token, "env", 4) == 0)
		ft_env(mini);
	if (ft_strncmp(token->token, "exit", 10) == 0)
		ft_exit(mini);
	if (ft_strncmp(token->token, "cd", 10) == 0)
		ft_cd(mini);
	if (ft_strncmp(token->token, "pwd", 10) == 0)
		ft_pwd(mini);
	if (ft_strncmp(mini->split[0], "unset", 10) == 0)
		ft_unset(mini);
	if (ft_strncmp(mini->split[0], "export", 10) == 0)
		ft_export(mini);
	if (ft_strncmp(token->token, "echo", 10) == 0)
		ft_echo(mini);
	chek_herdoc(mini, 1);
	free_split(mini->split);
}
