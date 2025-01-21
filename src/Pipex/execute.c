/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:30:41 by rpires-c          #+#    #+#             */
/*   Updated: 2025/01/16 11:40:35 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_paths_from_env(char **envp)
{
	int	i;
	int	space_only;

	space_only = 1;
	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == 0)
	{
		if (!((*envp[i] >= 9 && *envp[i] <= 13) || *envp[i] == 32))
			space_only = 0;
		i++;
	}
	if (!envp[i] || space_only == 1)
		return (NULL);
	return (ft_split(envp[i] + 5, ':'));
}

char	*build_and_check_path(char *path, char *cmd)
{
	char	*part_path;
	char	*full_path;

	part_path = ft_strjoin(path, "/");
	full_path = ft_strjoin(part_path, cmd);
	ft_free(part_path, NULL);
	if (access(full_path, F_OK) == 0)
		return (full_path);
	ft_free(full_path, NULL);
	return (NULL);
}

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;

	paths = get_paths_from_env(envp);
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		path = build_and_check_path(paths[i], cmd);
		if (path)
		{
			free_split(paths);
			ft_free(paths, NULL);
			return (path);
		}
	}
	i = -1;
	free_split(paths);
	return (NULL);
}

int chek_biltin(char **cmd)
{	

	if(  cmd[0] == NULL)
		return (FALSE);
	if(ft_strncmp(cmd[0], "env", 5) == 0)
		return (TRUE);
	if (ft_strncmp(cmd[0], "exit", 10) == 0)
		return (TRUE);
	if (ft_strncmp(cmd[0], "cd", 10) == 0)
		return (TRUE);
	if (ft_strncmp(cmd[0], "pwd", 10) == 0)
		return (TRUE);
	if (ft_strncmp( cmd[0],"unset", 10) == 0)
		return (TRUE);
	if (ft_strncmp( cmd[0],"export", 10) == 0)
		return (TRUE);
	if (ft_strncmp(cmd[0], "echo", 10) == 0)
		return (TRUE);
	return (FALSE);
}

void	execute(char *argv, t_minis *mini)
{
	char	**cmd;
	int		i;
	char	*path;

	i = -1;
	cmd = ft_split(expand_env(argv,mini), ' ');
	unset_list(&mini->env, "?");

	if(chek_biltin(cmd) == TRUE)
	{
		mini->line = argv;
		mini->tokens = tokenize_and_check_bash_command(mini);
		mini->tokens_copy = tokenize_and_check_bash_command(mini);
		builtins(mini);
		ft_exit_end(mini->exit_code_error);
	}
	path = find_path(cmd[0], env_to_matrix(mini));
	if (!path)
		no_path_error(argv);
	if(path == NULL)
		path = mini->path;
	  if (execve(path, cmd, env_to_matrix(mini)) == -1)
		command_error();
}
