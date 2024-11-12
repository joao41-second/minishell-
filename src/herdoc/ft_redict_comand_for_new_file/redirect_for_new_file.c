/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_for_new_file.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:30:26 by jperpct           #+#    #+#             */
/*   Updated: 2024/11/12 12:54:52 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int redirect_for_new_file(t_minis *mini)
{
	int i;
	int fds;
	i = -1;

	while (mini->split[++i] != NULL)
	{
		if(ft_strncmp(mini->split[i], ">", 4) == 0)
		{
			i++;
			break;
		}
	}
	//unlink(mini->split[i]);
	fds = open(mini->split[i],O_CREAT | O_WRONLY | O_TRUNC, 0777);

	return (fds);
}
