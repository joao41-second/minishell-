/* /* /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:42:28 by rpires-c          #+#    #+#             */
/*   Updated: 2024/12/06 15:15:04 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* void	handle_pipe_fork(char **argv, int argc, t_btree *node, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		pipe_error();
	pid = fork();
	if (pid == -1)
		fork_error();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		process_tree(argv, argc, node->left, envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		process_tree(argv, argc, node->right, envp);
	}
}

void	handle_redirection(t_minis mini, char **envp)
{
	int	infile;
	int	outfile;

	if (node->first_cmd == 1)
	{
		infile = open_file(argv[1], 2);
		dup2(infile, STDIN_FILENO);
		close(infile);
	}
	else if (node->first_cmd == 2)
	{
		outfile = open_file(argv[argc - 1], 1);
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
	}
}

void	process_tree(char **argv, int argc, t_btree *node, char **envp)
{
	if (node->cmd == NULL)
		handle_pipe_fork(argv, argc, node, envp);
	else
	{
		handle_redirection(argv, argc, node);
		execute(node->cmd, envp);
	}
} */