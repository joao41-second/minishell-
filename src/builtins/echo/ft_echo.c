/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:43:45 by jperpct           #+#    #+#             */
/*   Updated: 2024/11/04 15:54:27 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdio.h>

void	ft_echo(t_minis *mini)
{
	int	i;
	char *str;
	i = 0;
	//while (mini->split[++i] != NULL)
	//{
	//	printf("%s ",  mini->split[i]);
	//}
	str = expand_env(mini->line, mini);
	if(str == NULL)
		printf("error");
	else
		printf("%s",str);
	ft_free(str,NULL);
	printf("\n");
}
