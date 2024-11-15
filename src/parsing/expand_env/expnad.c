/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expnad.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:59:23 by jperpct           #+#    #+#             */
/*   Updated: 2024/11/15 16:15:47 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char *expand_env(char *str, t_minis *mini)
{
	int i;
	int char_flag;
	int char_flag_dub;
	int cord_flag;
	int cord_flag_dub:

	(void)mini;
	i = -1;
	char_flag = 0;
	char_flag_dub = 0;
	cord_flag = -1;
	cord_flag_dub = -1;
	while (str[++i] != '\0')
	{
		if(str[i] == 39)
		{
			char_flag++;
			cord_flag = i;
		}
		if(str[i] == '"')
		{
			cord_flag_dub = i;
			char_flag_dub++;
		}
		if(char_flag > 1)
		{
			char_flag = 0;
			cord_flag = -1;
		}
		if(char_flag_dub > 1)
		{
			cord_flag_dub = -1;
			char_flag_dub = 0;
		}
	}
	return ("");
}
