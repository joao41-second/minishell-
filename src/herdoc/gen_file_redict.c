/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_file_redict.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rui <rui@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:27:15 by jperpct           #+#    #+#             */
/*   Updated: 2025/02/03 11:15:53 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "errno.h"
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

static void	erro_prin(t_minis *mini)
{
	if (errno == ENOENT)
		ft_print_error_simple("", NOT_FILE, "bash");
	else
		ft_print_error_simple("", NOT_PERM, "bash");
	mini->comand = 1;
	mini->exit_code_error = 1;
}

static void	set_fd(int nb, t_token *token, t_minis *mini, int on)
{
	int		fd;
	char	*redir;

	fd = 0;
	if ((token->redirection_source == NULL && (nb == 4 || nb == 3))
		|| (token->redirection_target == NULL && (nb == 1 || nb == 2)))
		return ;
	if (nb == 4 || nb == 3)
		redir = expand_env(token->redirection_source, mini);
	else
		redir = expand_env(token->redirection_target, mini);
	if (nb == 1 && token->redirection_target != NULL)
		fd = open(redir, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (nb == 2 && token->redirection_target != NULL)
		fd = open(redir, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (nb == 3)
		fd = herdoc(mini, 0, token->redirection_source);
	if (nb == 4 && token->redirection_source != NULL)
		fd = open(redir, O_RDONLY);
	if (fd < 0)
		erro_prin(mini);
	if ((nb == 1 || nb == 2) && on == 1)
		dup2(fd, 1);
	close(fd);
}

void	redirect_bil(t_list_ *list, t_minis *mini)
{
	list = ft_node_start(list);
	while (list != NULL && ft_strncmp(get_token(list)->type, "pipe", 100) != 0)
	{
		if (ft_strncmp(get_token(list)->token, ">>", 10) == 0
			&& mini->exit_code_error == 0)
			set_fd(1, get_token(list), mini, 1);
		if (ft_strncmp(get_token(list)->token, ">", 10) == 0
			&& mini->exit_code_error == 0)
			set_fd(2, get_token(list), mini, 1);
		if (ft_strncmp(get_token(list)->token, "<<", 10) == 0
			&& mini->exit_code_error == 0)
			set_fd(3, get_token(list), mini, 1);
		if (ft_strncmp(get_token(list)->token, "<", 10) == 0
			&& mini->exit_code_error == 0)
			set_fd(4, get_token(list), mini, 1);
		(list) = (list)->next;
	}
}

void	free_node_dub(t_list_ **list)
{
	ft_free_node(list, free_token);
	if (*list != NULL)
		ft_free_node(list, free_token);
}

void	dell_redir( t_list_ **list)
{
	t_list_	*save;

	save = *list;
	while (*list != NULL)
	{
		if (ft_strncmp(get_token(*list)->type, "comand", 10) != 0)
		{
			save = *list;
			break ;
		}
		(*list) = (*list)->next;
	}
	*list = ft_node_start(save);
	while (*list != NULL)
	{
		if (get_token(*list)->type != NULL
			&& ft_strncmp(get_token(*list)->type, "redir", 10) == 0)
		{
			free_node_dub(list);
			continue ;
		}
		(*list) = (*list)->next;
	}
	*list = ft_node_start(save);
}
