/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:23:46 by jperpct           #+#    #+#             */
/*   Updated: 2024/10/23 15:54:19 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <string.h>

void	ft_pwd(t_minis *mini)
{
	t_token *token;
	char opcion[6];
	
	if(mini->tokens->next != NULL)
	{
		token = get_token(mini->tokens->next);
		//if(ft_strlen(token->token) > 3)
		//{
			if(token->token[0]== '-' && token->token[1] != '-')
			{
				ft_strlcpy(opcion, token->token, 3);
				ft_print_error("mini", opcion, INV_OPT, "bash");
			}
			if(token->token[0]== '-' && token->token[1] == '-' && token->token[2] == '\0')
			{
				ft_strlcpy(opcion, token->token, 3);
				ft_print_error("mini", opcion, INV_OPT, "bash");
			}
	//	}

	}
	printf("%s\n", mini->path);
}
