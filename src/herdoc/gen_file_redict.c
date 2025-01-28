/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_file_redict.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:27:15 by jperpct           #+#    #+#             */
/*   Updated: 2025/01/02 16:49:00 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "errno.h"

static void	set_fd(int nb,t_token *token,t_minis *mini,int on)
{
	int fd=0;
	char *redir;
	
	if(nb == 4 || nb == 3)
		redir = expand_env(token->redirection_source,mini);
	else	
		redir = expand_env(token->redirection_target,mini);
	if (nb == 1 && token->redirection_target != NULL)
		fd = open(redir, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (nb == 2 && token->redirection_target != NULL)
		fd = open( redir,O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (nb == 3)
		fd = herdoc(mini, 0,token->redirection_source);
	if (nb == 4 && token->redirection_source != NULL)
		fd = open(redir, O_RDONLY );
	
	if(fd < 0 )
	{
		if (errno == ENOENT) 
			ft_print_error_simple("",NOT_FILE , "bash");
		else
			ft_print_error_simple("",NOT_PERM , "bash");
		mini->exit_code_error = 1;
	}
	if((nb == 2 || nb == 1) && on == 1)
		dup2(fd,1);
	close(fd);
}

void	redirect_bil(t_list_ *list,t_minis *mini)
{
	t_list_ *frist;	

	frist = list;
	while ( list != NULL && ft_strncmp( get_token(list)->type, "pipe", 100) != 0)
	{
		if(ft_strncmp(get_token(list)->token, ">>", 10) == 0 && mini->exit_code_error == 0)
			set_fd(1, get_token(list), mini,0);
		if(ft_strncmp(get_token(list)->token, ">", 10) == 0  && mini->exit_code_error == 0)	
			set_fd(2, get_token(list), mini,0);
		if(ft_strncmp(get_token(list)->token, "<<", 10) == 0  && mini->exit_code_error == 0)	
			set_fd(3, get_token(list), mini,0);
		if(ft_strncmp(get_token(list)->token, "<", 10) == 0  && mini->exit_code_error == 0)
			set_fd(4, get_token(list), mini,0);
		(list) = (list)->next;
	}
}

void dell_redir( t_list_ **list)
{
	t_list_ *save;

	save = *list;
	while ( *list != NULL)
	{
		if(ft_strncmp(get_token(*list)->type, "comand", 10) != 0 )
		{
			save = *list;
			break;
		}
		(*list) = (*list)->next;
	}

	*list = ft_node_start(save);

	while ( *list != NULL)
	{
		if(ft_strncmp(get_token(*list)->type, "redir", 10) == 0 )
		{
			ft_free_node(list, free_token);
			if(*list != NULL){
				ft_free_node(list, free_token);
			}
			continue;
		}
		(*list) = (*list)->next;
	}
	*list = ft_node_start(save);
}

