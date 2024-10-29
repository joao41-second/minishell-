/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 20:46:51 by jperpct           #+#    #+#             */
/*   Updated: 2024/10/23 16:06:37 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void ft_cd(t_minis *mini)
{
	t_list_ *ok;
	
	ok = mini->env;
    ok = (t_list_ *) get_list(mini->env,"PWD",get_env_node);
	if(ok == NULL)
		return ;

	if(mini->split[1] )
	{
		 
		if( chdir(mini->split[1]) == -1)
		{
			perror("ola o error");
		}
	}
}
