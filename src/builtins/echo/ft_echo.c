/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rui <rui@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:43:45 by jperpct           #+#    #+#             */
/*   Updated: 2025/02/10 16:04:46 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdio.h>

void	next_opcion(t_list_ **list)
{
	int	i;

	i = 0;
	while (*list != NULL)
	{
		if (get_token(*list)->token[0] == '-' )
		{
			while (i <= 0 && get_token(*list)->token[++i] != '\0')
				if (get_token(*list)->token[i] != 'n')
					i = -50;
			if (i == -50)
				*list = (*list)->previous;
			else
				*list = (*list)->next;
			return ;
		}
		else
			return ;
		if ((*list)->next == NULL)
			break ;
		*list = (*list)->next;
	}
}

int	chek_opcon(char *str)
{
	int	i;

	i = 0;
	if (str == NULL || str[0] != '-' )
		return (FALSE);
	while (str[++i])
	{
		if (str[i] != 'n')
			return (FALSE);
	}
	return (TRUE);
}

void	while_echo(int ok, char *str, t_minis *mini)
{
	if (get_token(mini->tokens)->token == NULL)
		str = NULL;
	else
		str = expand_env (get_token(mini->tokens)->token, mini);
	if (chek_opcon(str) != TRUE)
		ok = 2;
	if (ok != 1)
	{
		ok = 2;
		printf("%s", str);
	}
	if (mini->tokens->next != NULL && ok != 1)
		printf(" ");
}

void	echo_logic(t_minis *mini, t_token *token, int *new_line, int i)
{
	char	*str;
	int		ok;

	ok = 1;
	str = 0;
	token = get_token(mini->tokens->next);
	if (token->token[0] == '-')
	{
		while (token->token[++i] != '\0' )
			if (token->token[i] != 'n')
				*new_line = FALSE;
	}
	else
		*new_line = FALSE;
	if (mini->tokens->next != NULL )
		mini->tokens = mini->tokens->next;
	while (mini->tokens != NULL)
	{
		while_echo(ok, str, mini);
		mini->tokens = mini->tokens->next;
	}
}

void	ft_echo(t_minis *mini)
{
	int		i;
	int		new_line;
	t_token	*token;

	i = 0;
	new_line = TRUE;
	token = NULL;
	mini->tokens = ft_node_start(mini->tokens);
	if (mini->tokens->next == NULL)
		printf("\n");
	if (mini->tokens != NULL && mini->tokens->next != NULL)
		echo_logic(mini, token, &new_line, i);
	if (new_line == FALSE)
		printf("\n");
}
