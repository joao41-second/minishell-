/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpect <jperpect@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:20:37 by jperpect          #+#    #+#             */
/*   Updated: 2024/09/10 13:12:18 by jperpect         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "./free/free.h"

int main()
{
	ft_printf("ola");
	ft_printf("adeus");
	ft_printf("run");
	t_free * ok;
	ok = ft_node_new("ola"); 
	ft_malloc(3,ok);
	char *str = (char *)ft_malloc(38,NULL);
	str[0]='a';
}
