/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 20:46:51 by jperpct           #+#    #+#             */
/*   Updated: 2024/10/23 16:06:37 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <linux/limits.h>
#include <stdio.h>

void set_path(t_list_ **list,char *path)
{
	t_env *pwd;
	t_env *oldpwd;
	char paths[PATH_MAX];
	
    pwd = list_to_env ((t_list_ *) get_list(*list,"PWD",get_env_node));
    oldpwd = list_to_env ((t_list_ *) get_list(*list,"OLDPWD",get_env_node));
	if(oldpwd != NULL)
	{
		ft_free(oldpwd->content, NULL);
		oldpwd->content = ft_strdup(path);
	}
	getcwd(paths,PATH_MAX);
	if(pwd != NULL)
	{
		ft_free(pwd->content,NULL);
		pwd->content = ft_strdup(paths);
	}	


}

void ft_cd(t_minis *mini)
{
	char path[PATH_MAX];

	if(mini->split[1] )
	{
		getcwd(path,PATH_MAX);
		if( chdir(mini->split[1]) == -1)
		{
			perror("ola o error");
		}
		else 
		{
			set_path(&mini->env, path );
			set_path(&mini->env_org, path );
			getcwd(mini->path,PATH_MAX);
		}
	}
}
