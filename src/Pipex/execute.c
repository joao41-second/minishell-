/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:30:41 by rpires-c          #+#    #+#             */
/*   Updated: 2025/02/11 16:57:15 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "pipex.h"

int	chek_biltin_tree(char **cmd)
{
	if (cmd[0] == NULL)
		return (FALSE);
	if (ft_strncmp(cmd[0], "env\x1F", 5) == 0)
		return (TRUE);
	if (ft_strncmp(cmd[0], "exit\x1F", 10) == 0)
		return (TRUE);
	if (ft_strncmp(cmd[0], "cd\x1F", 10) == 0)
		return (TRUE);
	if (ft_strncmp(cmd[0], "pwd\x1F", 10) == 0)
		return (TRUE);
	if (ft_strncmp(cmd[0], "unset\x1F", 10) == 0)
		return (TRUE);
	if (ft_strncmp(cmd[0], "export\x1F", 10) == 0)
		return (TRUE);
	if (ft_strncmp(cmd[0], "echo\x1F", 10) == 0)
		return (TRUE);
	return (FALSE);
}

char	*search_env_paths(char *cmd, char **paths)
{
	char	*path;
	int		i;

	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		path = build_and_check_path(paths[i], cmd);
		if (path)
		{
			free_split(paths);
			return (path);
		}
	}
	free_split(paths);
	return (NULL);
}

char	*find_path(char *cmd, char **envp, t_minis *mini)
{
	char	**paths;
	char	*path;

	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
	{
		if (access(cmd, F_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	paths = get_paths_from_env(envp);
	path = search_env_paths(cmd, paths);
	if (path)
		return (path);
	path = build_and_check_path(mini->path, cmd);
	if (path && access(path, F_OK) == 0)
		return (path);
	ft_free(path, NULL);
	return (NULL);
}

char	*handle_builtin_or_find_path(char *argv, char **cmd, t_minis *mini)
{
	struct stat	file_stat;
	char		*path;

	unset_list(&mini->env, "?");
	if (chek_biltin_tree(cmd) == TRUE)
	{
		mini->line = argv;
		mini->tokens = tokenize_and_check_bash_command(mini);
		mini->tokens_copy = tokenize_and_check_bash_command(mini);
		builtins(mini);
		ft_exit_end(mini->exit_code_error);
	}
	path = find_path(cmd[0], env_to_matrix(mini), mini);
	if (path)
		return (path);
	if (access(cmd[0], F_OK) == 0)
	{
		if (stat(cmd[0], &file_stat) == -1)
		{
			ft_print_error(cmd[0], "", NOT_FILE, "");
			ft_exit_end(127);
		}
		return (cmd[0]);
	}
	return (NULL);
}

void	execute(char *argv, t_minis *mini)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(expand_env(argv, mini), '\x1F');
	if (ft_strncmp(cmd[0], ">>", 10) == 0
		|| ft_strncmp(cmd[0], "<", 10) == 0
		|| ft_strncmp(cmd[0], ">", 10) == 0
		|| ft_strncmp(cmd[0], "<<", 10) == 0)
		ft_exit_end(0);
	path = handle_builtin_or_find_path(argv, cmd, mini);
	if (!path)
		no_path_error(expand_env(argv, mini));
	check_execute_permissions(path, expand_env(argv, mini));
	if (execve(path, cmd, env_to_matrix(mini)) == -1)
		command_error();
}
