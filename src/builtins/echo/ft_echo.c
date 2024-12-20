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

char *rm_char_str(char *str,int len)
{
	char *src;
	src = ft_malloc(ft_strlen(str) ,  NULL);
	ft_strlcpy(src, str, len-1);
	//ft_strlcat(src, &str[len], ft_strlen(str));
	return (src);
}

char * remove_couts(char *str)
{
	int i;
	int quot1;
	int quot2;
	char temp;
	char *dup;
	
	i = -1;
	temp = '\0';
	quot1 = TRUE;
	quot2 = 0;
	
	while (str[++i] != '\0') 
	{
		if(str[i] == temp && temp != '\0')
		{
			temp = '\0';
			quot1 = TRUE;
			dup =rm_char_str(str, i);
			ft_free(str,NULL);
			str = dup;
			dup = NULL;
		}
		if((str[i] == 36 || str[i] == '"') && quot1 == TRUE )
		{
			temp = str[i];
			quot1 = FALSE;
			dup =rm_char_str(str, i);
			ft_free(str,NULL);
			str = dup;
			dup = NULL;
		}
	}
	return(str);
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
			str = remove_couts(get_token(mini->tokens)->token);
			printf("%s", str);
			if(mini->tokens->next != NULL)
				printf(" ");
			mini->tokens = mini->tokens->next;
		}
	}
	if (new_line == FALSE)
		printf("\n");
}
