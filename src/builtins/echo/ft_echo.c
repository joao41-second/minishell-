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

void	ft_echo(t_minis *mini)
{
	int		i;
	char	*str;
	int		new_line;
	t_token	*token;
	t_list_	*save;

	i = 0;
	new_line = TRUE;
	save = mini->tokens;
	if (mini->tokens != NULL && mini->tokens->next != NULL)
	{
		token = get_token(mini->tokens->next);
		if (token->token[0] == '-')
		{
			while (token->token[++i] != '\0' )
			{
				if (token->token[i] != 'n')
					new_line = FALSE;
			}
		}
		i = 0;
		if (mini->tokens->next->next != NULL && new_line == TRUE)
			mini->tokens = mini->tokens->next->next;
		else if (new_line == FALSE)
			mini->tokens = mini->tokens->next;
		while (mini->tokens != NULL)
		{
			printf("%s ", get_token(mini->tokens)->token);
			mini->tokens = mini->tokens->next;
		}
	}
	if (new_line == FALSE)
		printf("\n");
}
