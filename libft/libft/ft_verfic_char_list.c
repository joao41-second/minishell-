/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verfic_char_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpect <jperpect@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:01:16 by jperpect          #+#    #+#             */
/*   Updated: 2024/08/16 15:05:15 by jperpect         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	verfic_char_list(char *list, char set)
{
	int	i;

	i = -1;
	while (list[++i] != '\0')
	{
		if (list[i] == set)
			return (1);
	}
	return (0);
}
