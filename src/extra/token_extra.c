/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 09:49:11 by jperpct           #+#    #+#             */
/*   Updated: 2025/01/29 11:30:34 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void token_comand_set_start(t_list_ **list)
{
	t_list_ *start;

	start = *list;
	while ((*list) != NULL) 
	{
		if(get_token(*list)->type  != NULL && ft_strncmp(get_token(*list)->type,"comand",20) == 0)
		{
			(*list)->next = start;
			(*list)->previous = NULL;
			start->previous = (*list);
		}
		if((*list)->next == NULL)
			break;
		(*list) = (*list)->next;
	}
	*list = ft_node_start((*list));
}


int chek_biltin_cmd(char *cmd)
{	
	if(  cmd == NULL)
		return (FALSE);
	if(ft_strncmp(cmd, "env", 5) == 0)
		return (TRUE);
	if (ft_strncmp(cmd, "exit", 10) == 0)
		return (TRUE);
	if (ft_strncmp(cmd, "cd", 10) == 0)
		return (TRUE);
	if (ft_strncmp(cmd, "pwd", 10) == 0)
		return (TRUE);
	if (ft_strncmp( cmd,"unset", 10) == 0)
		return (TRUE);
	if (ft_strncmp( cmd,"export", 10) == 0)
		return (TRUE);
	if (ft_strncmp(cmd, "echo", 10) == 0)
		return (TRUE);
	return (FALSE);
}
int chek_comand_exit(t_list_ **list)
{
	t_list_ *start;

	start = *list;
	while ((*list) != NULL) 
	{
		if(get_token(*list)->type  != NULL && ft_strncmp(get_token(*list)->type,"command",20) == 0)
		{
			*list = ft_node_start((*list));
			return (TRUE);
		}
		if((*list)->next == NULL)
			break;
		(*list) = (*list)->next;
	}
	*list = ft_node_start((*list));	
	return (FALSE);
}

void set_new_comand(t_list_ **list)
{
	t_list_ *start;

	start = *list;
	if( *list == NULL || chek_comand_exit(list) == TRUE)
		return;
	while ((*list) != NULL) 
	{
		if(chek_biltin_cmd(get_token(*list)->token) == TRUE)
		{
			ft_free(get_token(*list)->type,NULL);
			get_token(*list)->type = ft_strdup("command");
			break;
		}
		if((*list)->next == NULL)
			break;
		(*list) = (*list)->next;
	}
	//*list = ft_node_start((*list));
}
