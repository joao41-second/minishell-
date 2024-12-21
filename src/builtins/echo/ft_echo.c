/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:43:45 by jperpct           #+#    #+#             */
/*   Updated: 2024/12/21 15:35:54 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdio.h>

void rm_char_str(char *str,int len)
{
	char *src;
	int i;

	len++;
	i = ft_strlen(str);
	src = ft_malloc(ft_strlen(str) ,  NULL);
	ft_strlcpy(src, str, len);
	ft_strlcat(src, &str[len], i);
	ft_bzero(str,  i);
	ft_strlcat(str,src , i);
}



void	ft_echo(t_minis *mini)
{
	int		i;
	int		new_line;
	t_token	*token;
	t_list_	*save;
	char *str;

	i = 0;
	new_line = TRUE;
	mini->tokens = ft_node_start(mini->tokens);
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
		}else {
		new_line = FALSE;
		}
		i = 0;
		if (mini->tokens->next != NULL && new_line == TRUE)
			mini->tokens = mini->tokens->next;
		else if (new_line == FALSE)
			mini->tokens = mini->tokens->next;
		while (mini->tokens != NULL)
		{
			str = expand_env(get_token(mini->tokens)->token,mini);
			printf("%s",str);
			if(mini->tokens->next != NULL)
				printf(" ");
			mini->tokens = mini->tokens->next;
		}
	}
	if (new_line == FALSE)
		printf("\n");
}
