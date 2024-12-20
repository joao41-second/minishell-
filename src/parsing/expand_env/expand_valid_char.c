/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_valid_char.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 09:48:25 by jperpct           #+#    #+#             */
/*   Updated: 2024/12/03 09:50:08 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_if_expand(char *verifc, t_quotes *quotes, int i)
{
	(void)i;
	if ((verifc[0] == '$' && quotes->dub == 1))
		return (TRUE);
	if ((verifc[0] == '$' && quotes->dub == 0 && quotes->simp == 0))
		return (TRUE);
	return (FALSE);
}

int	if_verifc(char *verifc, int *not_print, char **temp )
{
	if (verifc[0] == '\0')
	{
		not_print = 0;
		ft_free(*temp, NULL);
		*temp = NULL;
		return (TRUE);
	}
	return (FALSE);
}

char	*concatenate_not_env( char *verifc, t_quotes *quotes, char *temp )
{
	if (verifc[0] == '"' || verifc[0] == 39)
	{
		if (quotes->simp == 1 && quotes->dub == 1)
		{
			temp = ft_strjoin_and_free(temp, verifc);
			if (verifc[0] == '"')
				quotes->dub--;
			if (verifc[0] == 39)
				quotes->simp--;
		}
	}
		temp = ft_strjoin_and_free(temp, verifc);
	return (temp);
}

char	*concatenate_env(char *temp, char *save, int *not_print)
{
	if (save == NULL)
	{
		*not_print = INT_MAX;
		ft_free(temp, NULL);
		temp = NULL;
		return (NULL);
	}
	temp = ft_strjoin_and_free(temp, save);
	return (temp);
}

char	*creat_new(int i, char *str, t_quotes *quotes, t_minis *mini)
{
	static char	*temp = NULL;
	static int	not_print;
	char		*save;
	char		verifc[2];

	verifc[0] = str[i];
	verifc[1] = '\0';
	if (if_verifc(verifc, &not_print, &temp) == TRUE)
		return (NULL);
	if (not_print > 0)
		not_print--;
	if (not_print == 0)
	{
		if (temp == NULL)
			temp = ft_strdup("");
		if (ft_if_expand(verifc, quotes, i) == TRUE)
		{
			save = concatenate_the_str_with_env_var(&str[i], mini, &not_print);
			temp = concatenate_env(temp, save, &not_print);
			ft_free(save, NULL);
			return (temp);
		}
		temp = concatenate_not_env(verifc, quotes, temp);
	}
	return (temp);
}
