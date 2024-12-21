/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:43:45 by jperpct           #+#    #+#             */
/*   Updated: 2024/12/17 17:04:00 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdio.h>

void rm_char_str(char *str,int len)
{
	char *src;
	int i;
	

	i = ft_strlen(str);
	src = ft_calloc(i+1 ,  sizeof(char));
	if(len != 0)
	{
	ft_strlcpy(src, str, len);
	ft_strlcat(src, &str[len], i);
	}
	else
	{
		ft_strlcat(src, &str[1], i-1);
	}
	ft_bzero(str,  i);
	ft_strlcat(str,src , i);
	ft_free(src,NULL);
}

void remove_couts(char *str)
{
	int i;
	int quot1;
	int remuve;
	char temp;
	
	i = -1;
	temp = '\0';
	quot1 = TRUE;
	remuve = 0;

	while (str[++i] != '\0') 
	{
		if(str[i] == temp && temp != '\0')
		{
			temp = '\0';
			quot1 = TRUE;
			rm_char_str(str, i+remuve);
			remuve++;
		}
		if((str[i] == 39 || str[i] == '"') && quot1 == TRUE ) {
			temp = str[i];
			quot1 = FALSE;
			rm_char_str(str, i+remuve);
			remuve++;
		}
	}	
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
			remove_couts(get_token(mini->tokens)->token);
			printf("%s", get_token(mini->tokens)->token);
			if(mini->tokens->next != NULL)
				printf(" ");
			mini->tokens = mini->tokens->next;
		}
	}
	if (new_line == FALSE)
		printf("\n");
}
