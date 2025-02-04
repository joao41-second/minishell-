/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:02:47 by jperpct           #+#    #+#             */
/*   Updated: 2025/02/04 14:21:59 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child_process(t_btree *node, t_minis *mini, int fd[2])
{
	int	save;
	int	status;

	status = 0;
	if (node->right == NULL)
	{
		close(fd[0]);
		close(fd[1]);
		save = process_tree(node->left, mini);
		ft_exit_end(WSTOPSIG(status));
	}
	else
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		save = process_tree(node->left, mini);
		ft_exit_end(save);
	}
}

void	parent_process(t_btree *node, t_minis *mini, int *fd, pid_t pid)
{
	int	status;
	int	tipe;

	tipe = 0;
	status = 0;
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	if (node->right == NULL)
		tipe = 1;
	process_tree(node->right, mini);
	waitpid(pid, &status, 0);
	if (tipe == 1)
		mini->exit_code_error = WSTOPSIG(status);
}

void	pipe_fork(t_btree *node, t_minis *mini)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		pipe_error();
	pid = fork();
	if (pid == -1)
	{
		close(fd[0]);
		close(fd[1]);
		fork_error();
	}
	if (pid == 0)
		child_process(node, mini, fd);
	else
		parent_process(node, mini, fd, pid);
}

int	process_tree(t_btree *node, t_minis *mini)
{
	if (node && ft_strcmp(node->cmd, "|") == 0)
		pipe_fork(node, mini);
	else if (node)
	{
		redirect_(node->redir, mini);
		execute(node->cmd, mini);
	}
	return (mini->exit_code_error);
}
