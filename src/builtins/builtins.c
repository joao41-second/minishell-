/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:12:36 by jperpct           #+#    #+#             */
/*   Updated: 2024/11/12 12:35:14 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	chek_herdoc(t_minis	*mini, int set)
{
	int	i;
	i = -1;
	while (mini->split[++i] != NULL)
	{
		if(ft_strncmp(mini->split[i], ">", 4) == 0)
		{
			change_file(mini,set,'>');
			//redirect_for_new_file(mini,np);
		}
	}

}
void	builtins(t_minis	*mini)
{
	if (ft_strlen(mini->line) < 1)
		return ;
	mini->split = ft_split(mini->line, ' ');
	chek_herdoc(mini, 0);
	if (mini->split == NULL)
		return ;
	if (ft_strncmp(mini->split[0], "env", 4) == 0)
		ft_env(mini);
	if (ft_strncmp(mini->split[0], "exit;", 10) == 0)
		ft_exit(mini);
	if (ft_strncmp(mini->split[0], "cd", 10) == 0)
		ft_cd(mini);
	if (ft_strncmp(mini->split[0], "pwd", 10) == 0)
		ft_pwd(mini);
	if (ft_strncmp(mini->split[0], "unset", 10) == 0)
		ft_unset(mini);
	if (ft_strncmp(mini->split[0], "export", 10) == 0)
		ft_export(mini);
	if (ft_strncmp(mini->split[0], "echo", 10) == 0)
		ft_echo(mini);
	chek_herdoc(mini, 1);
	free_split(mini->split);
}
