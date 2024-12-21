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

void remove_couts(char *str)
{
	int i;
	int quot1;
	int cord1;
	char temp;
	char *dup;
	int use;
	
	i = -1;
	temp = '\0';
	quot1 = TRUE;
	cord1 = 0;
	use = 0;

	while(str[++i] != '\0')
	{
		if(str[i] == 39 && quot1 == TRUE)
		{
			quot1=FALSE;
			temp = 39;
			cord1= i;
			continue;
		}
		if( str[i] == 39 && quot1 == FALSE)
		{
			if(cord1 == 0)
				cord1=1;
			quot1 = TRUE;
			//rm_char_str(str, i+use);
			//rm_char_str(str, cord1+use);
			str[cord1] = (char) 255;
			str[i] = (char) 255;
//			printf("str %s \n",str);
			use++;
			//i-=2;
			continue;
		}
		if(str[i] == '"' && quot1 == TRUE)
		{
			quot1=FALSE;
			temp = '"';
			cord1= i;
			continue;
		}
		if( str[i] == '"' && quot1 == FALSE)
		{
			quot1 = TRUE;	
			str[cord1] = (char) 25;
			str[i] = (char) 25;
			use++;
			continue;
		}
	}
	i = -1;
	/* 
	int tmep = 0;
	
	char * src = ft_malloc(ft_strlen(str) ,  NULL);
	while (str[++i] != '\0')
	{
		if(str[i] != (char) 25)
			src[i-temp] = str[i];
		else
			temp++;
	}
	src[i] = '\0';
//	printf("%s",src);
	temp = ft_strlen(str);
	ft_bzero(str, temp);
	ft_strlcat(str, src, temp);
*/	
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
