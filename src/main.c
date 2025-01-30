/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rui <rui@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:12:18 by jperpect          #+#    #+#             */
/*   Updated: 2025/01/30 17:47:14 by rui              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minis	start_minis(char **env)
{
	t_minis	mini;

	mini.line = NULL;
	mini.env = env_split(env);
	mini.env_org = env_split(env);
	mini.readline = 0;
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
	and_shelvl(&mini);
	start_shell(mini);
	return (get_signal(0));
}
