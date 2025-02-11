/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 10:20:11 by jperpct           #+#    #+#             */
/*   Updated: 2025/02/11 10:11:23 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
char	*ft_generat_if(char *fd, t_minis *mini)
{
	if (fd == NULL)
		fd = ft_strdup(ft_getenv(mini, "HOME"));
	if (fd == NULL)
	{
		mini->exit_code_error = 1;
		ft_print_error("cd", NOT_HOME, "", "bash");
	}
	return (fd);
}

char	*fd_generat(t_minis *mini)
{
	t_token	*token;
	char	*fd;
	char	*comand;

	fd = NULL;
	if (mini->tokens->next != NULL)
	{
		token = get_token(mini->tokens->next);
		comand = expand_env(token->token, mini);
		if (comand[0] == '~')
		{
			if (ft_getenv(mini, "HOME") == NULL)
			{
				ft_print_error("cd", NOT_HOME, "", "bash");
				mini->exit_code_error = 1;
				return (ft_free(comand, NULL), NULL);
			}
			fd = ft_strjoin(ft_getenv(mini, "HOME"), &comand[1]);
		}
		else
			fd = ft_strdup(comand);
		ft_free(comand, NULL);
	}
	fd = ft_generat_if(fd, mini);
	return (fd);
}

void	ft_cd(t_minis *mini)
{
	char	*fd;

	fd = NULL;
	if (not_opcion(mini, "cd") == TRUE)
		return ;
	if (too_arg_print("cd", 0, mini) == TRUE)
		return ;
	fd = fd_generat(mini);
	if (fd == NULL)
		return ;
	if (chdir(fd) < 0)
	{
		ft_print_error("cd", fd, NOT_FILE, "bash");
		ft_free(fd, NULL);
		mini->exit_code_error = 1;
		return ;
	}
	else
	{
		set_path(&mini->env);
		set_path(&mini->env_org);
		getcwd(mini->path, PATH_MAX);
	}
	ft_free(fd, NULL);
}
