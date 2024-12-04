/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 20:46:51 by jperpct           #+#    #+#             */
/*   Updated: 2024/12/03 09:54:38 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <linux/limits.h>
#include <stdio.h>

void	set_path(t_list_ **list)
{
	t_env	*pwd;
	t_env	*oldpwd;
	char	paths[PATH_MAX];

	pwd = list_to_env((t_list_ *)get_list(*list, "PWD", get_env_node));
	oldpwd = list_to_env((t_list_ *)get_list(*list, "OLDPWD", get_env_node));
	if (oldpwd != NULL && pwd->content != NULL)
	{
		ft_free(oldpwd->content, NULL);
		oldpwd->content = ft_strdup(pwd->content);
	}
	getcwd(paths, PATH_MAX);
	if (pwd != NULL)
	{
		ft_free(pwd->content, NULL);
		pwd->content = ft_strdup(paths);
	}
}

void	ft_cd(t_minis *mini)
{
	char	path[PATH_MAX];
	char	*fd;

	if (mini->split[1])
	{
		if (mini->split[1][0] == '~')
		{
			fd = ft_strjoin(ft_getenv(mini, "HOME"), &mini->split[1][1]);
		}
		else
			fd = ft_strdup(mini->split[1]);
		//getcwd(path, PATH_MAX);
		if (chdir(fd) < 0)
		{
			ft_print_error("cd",fd,2,"bash");
			ft_free(fd, NULL);

			return;
		}
		else
		{
			set_path(&mini->env);
			set_path(&mini->env_org);
			getcwd(mini->path, PATH_MAX);
		}
		ft_free(fd, NULL);
	}
}
