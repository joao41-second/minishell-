/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:56:45 by jperpct           #+#    #+#             */
/*   Updated: 2024/11/13 11:14:30 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdio.h>
#include <stdlib.h>

int ft_str_is_nb(char *str)
{
	int	i;
	while (str[++i] != '\0')
	{
		if(ft_isdigit(str[i]) != 1 || str[i] !='-' || str[i] != '+')
			return (FALSE);
	}
	return (TRUE);
}

void	ft_exit(t_minis *mini)
{	
	t_token	*token;
	t_list_	*list;
	int exits;
	
	exits = 0;
	printf("exit\n");
	list = mini->tokens;
	//tmep
	mini->tokens= mini->tokens->next;
	while (mini->tokens != NULL) 
	{
		token = get_token(mini->tokens);
		if (ft_strncmp(token->type,"argument",15) == 0)
		{
			if(exits == 0)
				exits++;
			else
			{
				ft_print_error("exit", token->token, TOO_ARG, "bash");
				return;
			}
		}
		mini->tokens = mini->tokens->next;
	}
		mini->tokens = list;
	if(mini->tokens != NULL && mini->tokens->next != NULL)
	{
		token = get_token(mini->tokens->next);
		
		if(ft_str_is_nb(token->token) != TRUE)
		{
			ft_print_error("exit", token->token, NOT_NUB, "bash");
			mini->exit_code_error = 2;
		}
		else
			mini->exit_code_error = ft_atoi(token->token);
	}
	ft_free_all(NULL);
	exit(mini->exit_code_error);
}
