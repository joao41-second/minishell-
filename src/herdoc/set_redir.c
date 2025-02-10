/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:31:40 by jperpct           #+#    #+#             */
/*   Updated: 2025/02/03 11:10:24 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "errno.h"

void	relink_list(t_list_ **list, void *content)
{
	t_list_	*new;

	new = ft_node_new(content);
	*list = ft_node_end(*list);
	ft_node_add_front(list, new);
}

void	set_fd(t_list_ *list, t_minis *mini)
{
	if (ft_strncmp(get_token(list)->token, "<<", 5) == 0)
	{
		get_token(list)->redir_fd = herdoc(mini, 0,
			get_token(list)->redirection_source);
	}
}

void	set_redir(t_list_ *list, t_btree **btree, t_minis *mini)
{
	t_list_	*list_redir;
	t_btree	*save;

	save = *btree;
	list_redir = NULL;
	while (list != NULL)
	{
		if (ft_strncmp(get_token(list)->type, "redir", 10) == 0)
		{
			set_fd(list, mini);
			if (list_redir == NULL)
				list_redir = ft_node_new(list->content);
			else
				relink_list(&list_redir, list->content);
		}
		if (ft_strncmp(get_token(list)->type, "pipe", 10) == 0 || !list->next)
		{
			if (list_redir != NULL)
				(*btree)->left->redir = ft_node_start(list_redir);
			list_redir = NULL;
			(*btree) = (*btree)->right;
		}
		list = list->next;
	}
	(*btree) = save;
}

static void	set_fds(int nb, t_token *token, t_minis *mini, int on)
{
	int		fd;
	char	*save;

	ser_fd(nb);
	fd = 0;
	save = token->redirection_target;
	if (nb == 1 && token->redirection_target != NULL)
		fd = open(expand_env(save, mini), O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (nb == 2 && token->redirection_target != NULL)
		fd = open(expand_env(save, mini), O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (nb == 3)
		fd = open(HER, O_RDONLY);
	if (nb == 4 && token->redirection_source != NULL)
		fd = open(expand_env(token->redirection_source, mini), O_RDONLY);
	if (fd < 0)
	{
		if (errno == ENOENT)
			ft_print_error_simple("", NOT_FILE, "bash");
		else
			ft_print_error_simple("", NOT_PERM, "bash");
		ft_exit_end(1);
	}
	set_redir_(fd, nb, on);
	close(fd);
}

void	redirect_(t_list_ *list, t_minis *mini)
{
	t_list_	*frist;

	frist = list;
	while (list != NULL && ft_strncmp(get_token(list)->type, "pipe", 100) != 0)
	{
		if (ft_strncmp(get_token(list)->token, ">>", 10) == 0)
			set_fds(1, get_token(list), mini, 0);
		if (ft_strncmp(get_token(list)->token, ">", 10) == 0)
			set_fds(2, get_token(list), mini, 0);
		if (ft_strncmp(get_token(list)->token, "<<", 10) == 0)
			set_fds(3, get_token(list), mini, 1);
		if (ft_strncmp(get_token(list)->token, "<", 10) == 0)
			set_fds(4, get_token(list), mini, 1);
		(list) = (list)->next;
	}
	list = frist;
	while (list != NULL && ft_strncmp(get_token(list)->type, "pipe", 100) != 0)
	{
		if (ft_strncmp(get_token(list)->token, ">>", 10) == 0)
			set_fds(1, get_token(list), mini, 1);
		if (ft_strncmp(get_token(list)->token, ">", 10) == 0)
			set_fds(2, get_token(list), mini, 1);
		(list) = (list)->next;
	}
	ser_fd(50);
}
