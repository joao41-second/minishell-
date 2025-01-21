/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 09:48:13 by jperpct           #+#    #+#             */
/*   Updated: 2025/01/21 10:58:08 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_and_free(t_minis *mini, int set, t_list_ **token, char chage)
{
	if (chage == 'h')
		herdoc(mini, set, get_token(*token)->redirection_source);
	else
		change_file(mini, set, chage, get_token(*token));
	ft_free_node(token, free_token);
	ft_free_node(token, free_token);
}

int	open_error(t_minis *mini, t_list_ **token)
{
	int	i;

	i = open(get_token(*token)->redirection_target, O_WRONLY);
	if (i == -1)
	{
		perror("bash");
		mini->comand = 1;
		mini->exit_code_error = 1;
		ft_free_node(token, free_token);
		ft_free_node(token, free_token);
		return (FALSE);
	}
	close(i);
	ft_free_node(token, free_token);
	ft_free_node(token, free_token);
	return (TRUE);
}

void	redir_if( t_minis *mini, t_list_ **token, char set)
{
	static int	i = 0;

	if (i == 1 && (ft_strncmp(get_token(*token)->token, ">", 4) == 0
			|| ft_strncmp(get_token(*token)->token, ">>", 4) == 0
			|| ft_strncmp(get_token(*token)->token, "<<", 4) == 0))
	{
		i = 0;
		change_file(mini, 1, 'i', get_token(*token));
	}
	if (ft_strncmp(get_token(*token)->token, ">", 4) == 0)
		change_and_free(mini, set, token, '>');
	if (ft_strncmp(get_token(*token)->token, ">>", 4) == 0)
		change_and_free(mini, set, token, 'n');
	if (ft_strncmp(get_token(*token)->token, "<<", 4) == 0)
		change_and_free(mini, set, token, 'h');
	if (ft_strncmp(get_token(*token)->token, "<", 4) == 0)
		if (open_error(mini, token) == FALSE)
			return ;
	if ((ft_strncmp(get_token(*token)->token, ">", 4) == 0
			|| ft_strncmp(get_token(*token)->token, ">>", 4) == 0
			|| ft_strncmp(get_token(*token)->token, "<<", 4) == 0))
	{
		*token = ft_node_start(*token);
		i++;
	}
}
