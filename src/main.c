/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:12:18 by jperpect          #+#    #+#             */
/*   Updated: 2024/10/15 19:29:50 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void func_test ()
{
	char *testo = ft_malloc(3456 * sizeof(int), NULL);
}

int main(int ac, char **av, char **env)
{
	t_list_ * ok;
	t_list_ * envs;
	ok = ft_node_new(malloc(sizeof(1))); 
	ft_malloc(3,ok);
	ft_free_all(ok);
	ft_free(NULL,ok);
	envs = env_split(env);
	t_env *get = ((t_env*)envs->content);
	ft_printf("%s\n", get->name);

	start_shell();
}
