/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:12:36 by jperpct           #+#    #+#             */
/*   Updated: 2024/10/22 20:59:15 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
void builtins(t_minis mini)
{
	if(mini.comand == 1)
	{
		ft_env(mini);
	}
	if(mini.comand == 2)
	{
		ft_exit(mini);
	}
	if(mini.comand == 3)
	{
		ft_cd("./src/");
	} 
}
