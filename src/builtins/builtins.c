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

void	builtins(t_minis	*mini)
{
	if (ft_strlen(mini->line) < 1)
		return ;
	mini->split = ft_split(mini->line, ' ');
	if (mini->split[0] == NULL)
		return (free_split(mini->split));
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
	free_split(mini->split);
}
