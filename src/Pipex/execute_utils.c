/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rui <rui@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 22:33:44 by rui               #+#    #+#             */
/*   Updated: 2025/02/03 22:52:33 by rui              ###   ########.fr       */
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
