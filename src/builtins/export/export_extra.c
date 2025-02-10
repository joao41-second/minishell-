/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_extra.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:14:29 by jperpct           #+#    #+#             */
/*   Updated: 2025/01/21 11:19:45 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	set_env_in_case_of_the_plus(char *str, char **export,
								t_env *env, char *temp)
{
	int	i;

	i = 0;
	if (str[ft_strlen(export[0]) - 1] == '+')
	{
		temp = ft_substr(export[0], 0, ft_strlen(export[0]) - 1);
		env->name = temp;
		temp = NULL;
		i++;
	}
	else
		env->name = ft_strdup(export[0]);
	return (i);
}

int	valid_export(char	*token)
{
	int	save;
	int	i;

	save = 0;
	i = -1;
	if (ft_isalpha(token[0]) == TRUE && token[0] != '_')
		return (FALSE);
	while (token[++i] != '\0')
	{
		if (token[i] == '=')
		{
			save = 1;
			if (token[i - 1] != '+' && (ft_isalnum(token[i - 1]) == TRUE
					&& token[i - 1] != '_'))
				return (FALSE);
			break ;
		}
	}
	i = -1;
	while (token[++i] != '\0')
	{
		if (save != 1 && ft_isalnum(token[i]) == TRUE && token[i] != '_')
			return (FALSE);
	}
	return (TRUE);
}

int	locate(char *str, char src)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == src)
			return (TRUE);
	}
	return (FALSE);
}

int	simpel_export(char *comand)
{
	char	**split;
	int		i;

	i = -1;
	split = ft_split(comand, '=');
	while (split[++i] != NULL)
	{
		if (valid_export(split[i]) != TRUE)
		{
			free_split(split);
			return (FALSE);
		}
	}
	free_split(split);
	return (TRUE);
}
