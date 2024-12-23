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

t_token	*get_token(t_list_ *list)
{
	t_token	*set;

	set = (t_token *)list->content;
	return (set);
}

void	builtins(t_minis	*mini)
{
	t_token	*token;
	t_list_ *save;
	char *comand;

	save = mini->tokens;
	//chek_herdoc(mini, 0);
	if (mini->tokens == NULL)
		return ;
	token = get_token(mini->tokens);
	comand = expand_env(token->token,mini);
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
	ft_free(comand,NULL);
	//chek_herdoc(mini, 1);
	mini->tokens = save;
}
