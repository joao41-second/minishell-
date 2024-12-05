/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:24:52 by jperpct           #+#    #+#             */
/*   Updated: 2024/12/03 10:24:52 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

void ft_print_error(char *comand, char *error,char *error_char, char* start)
{
	ft_putstr_fd(start, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(comand, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error , 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error_char, 2);
	ft_putstr_fd("\n", 2);
}

int too_arg_print(char *comand ,int args,t_minis *mini)
{
	t_token	*token;
	t_list_	*list;
	int exits;
	
	exits = 0;
	list = mini->tokens;

	while (mini->tokens != NULL) 
	{
		token = get_token(mini->tokens);
		if (ft_strncmp(token->type,"argument",15) == 0)
		{
			if(exits == args)
				exits++;
			else
			{
				ft_print_error(comand, "", TOO_ARG, "bash");
				return (TRUE);
			}
		}
		mini->tokens = mini->tokens->next;
	}
		mini->tokens = list;
	return (FALSE);
}

void ft_error(t_minis *mini)
{


}
