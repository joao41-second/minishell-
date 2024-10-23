/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:12:18 by jperpect          #+#    #+#             */
/*   Updated: 2024/10/23 15:37:45 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minis start_minis(char **env)
{
	t_minis mini;

	mini.env = env_split(env);
	mini.comand = 4;
	mini.exit_code_error= 0;
	return(mini);
}


int main(int ac, char **av, char **env)
{
	t_minis  mini;

	start_alloc();
	mini = start_minis(env);
	start_shell( mini);
	free_list(mini.env,free_env);
	ft_free_all(NULL);
}
