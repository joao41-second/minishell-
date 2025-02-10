/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:45:41 by jperpct           #+#    #+#             */
/*   Updated: 2025/02/10 16:05:11 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	rm_char_str(char *str, int len)
{
	char	*src;
	int		i;

	len++;
	i = ft_strlen(str);
	src = ft_malloc(ft_strlen(str), NULL);
	ft_strlcpy(src, str, len);
	ft_strlcat(src, &str[len], i);
	ft_bzero(str, i);
	ft_strlcat(str, src, i);
}
