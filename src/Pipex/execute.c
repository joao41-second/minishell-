/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:30:41 by rpires-c          #+#    #+#             */
/*   Updated: 2025/01/28 18:01:00 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char *build_and_check_path(char *path, char *cmd)
{
    char *part_path;
    char *full_path;

    part_path = ft_strjoin(path, "/");
    full_path = ft_strjoin(part_path, cmd);
    ft_free(part_path, NULL);
    if (access(full_path, F_OK) == 0)
        return (full_path);
    ft_free(full_path, NULL);
    return (NULL);
}

char *find_path(char *cmd, char **envp, t_minis *mini)
{
    char **paths;
    char *path;
    int i;

    if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
    {
        if (access(cmd, F_OK) == 0)
            return (ft_strdup(cmd));
        return (NULL);
    }
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
    free_split(paths);
    path = build_and_check_path(mini->path, cmd);
    if (path && access(path, F_OK) == 0)
        return (path);
    
    ft_free(path, NULL);
    return (NULL);
}

void execute(char *argv, t_minis *mini)
{
    char **cmd;
    char *path;
	struct stat file_stat;

    cmd = ft_split(expand_env(argv, mini), ' ');
    unset_list(&mini->env, "?");
    if (chek_biltin(cmd) == TRUE)
    {
        mini->line = argv;
        mini->tokens = tokenize_and_check_bash_command(mini);
        mini->tokens_copy = tokenize_and_check_bash_command(mini);
        builtins(mini);
        ft_exit_end(mini->exit_code_error);
    }
    if (cmd[0][0] == '/' || (cmd[0][0] == '.' && cmd[0][1] == '/'))
    {
        if (stat(cmd[0], &file_stat) == -1)
        {
            ft_print_error(cmd[0], "", NOT_FILE, "");
            ft_exit_end(127);
        }
        check_execute_permissions(cmd[0],expand_env(argv, mini));
        if (execve(cmd[0], cmd, env_to_matrix(mini)) == -1)
            command_error();
        return;
    }
    path = find_path(cmd[0], env_to_matrix(mini), mini);
    if (!path)
    {
        no_path_error(expand_env(argv, mini));
        return;
    }
    check_execute_permissions(path,expand_env(argv, mini));
    if (execve(path, cmd, env_to_matrix(mini)) == -1)
        command_error();
}
