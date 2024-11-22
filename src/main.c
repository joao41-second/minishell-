/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:12:18 by jperpect          #+#    #+#             */
/*   Updated: 2024/11/15 18:03:07 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minis	start_minis(char **env)
{
	t_minis	mini;

	mini.env = env_split(env);
	mini.env_org = env_split(env);
	mini.comand = 0;
	mini.exit_code_error = 0;
	return (mini);
}

int	main(int ac, char **av, char **env)
{
	t_minis	mini;

	(void)ac;
	(void)av;
	start_alloc();
	mini = start_minis(env);
	start_shell(mini);
	//ft_free_all(NULL);
}
