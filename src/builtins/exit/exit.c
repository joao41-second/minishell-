/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:56:45 by jperpct           #+#    #+#             */
/*   Updated: 2025/02/10 17:19:09 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_str_is_nb(char *src, t_minis *mini)
{
	int	i;

	(void)mini;
	i = -1;
	while (src[++i] != '\0')
	{
		if (ft_isdigit(src[i]) != 1 && src[i] != '-' && src[i] != '+')
		{
			ft_free(src, NULL);
			src = NULL;
			return (FALSE);
		}
	}
	return (TRUE);
}

void	ft_exit(t_minis *mini)
{
	t_token	*token;
	char	*comand;

	if (mini->tokens != NULL && mini->tokens->next != NULL)
	{
		token = get_token(mini->tokens->next);
		comand = expand_env(token->token, mini);
		if (ft_str_is_nb(comand, mini) != TRUE || ft_strlen(comand) > 20)
		{
			comand = expand_env(token->token, mini);
			ft_print_error("exit", comand, NOT_NUB, "bash");
			printf("exit\n");
			mini->exit_code_error = 2;
			ft_exit_end(mini->exit_code_error);
		}
		else
			mini->exit_code_error = ft_atoi(comand);
	}
	else
		mini->exit_code_error = ft_atoi(ft_getenv(mini, "?"));
	if (too_arg_print("exit", 0, mini) == TRUE)
		return ;
	printf("exit\n");
	ft_exit_end(mini->exit_code_error);
}

void	ft_exit_end(int code)
{
	ft_free_all(NULL);
	exit(code);
}
