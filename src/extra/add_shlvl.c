/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_shlvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 11:17:42 by jperpct           #+#    #+#             */
/*   Updated: 2025/01/16 11:29:40 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	chage_shlvl(t_list_ *lists)
{
	t_list_ *list;
	t_env *level;
	int chage;

	list = (t_list_ *)get_list(lists, "SHLVL", get_env_node);
	level = (t_env*)list->content;
	chage = ft_atol( level->content);
	chage++;
	level->content = ft_itoa(chage);

}

void	and_shelvl(t_minis *mini)
{
	chage_shlvl(mini->env);
	chage_shlvl(mini->env_org);
}

