/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:36:26 by jperpct           #+#    #+#             */
/*   Updated: 2024/10/22 14:26:58 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strndup(const char *src, size_t n)
{
	size_t	len;
	char	*dst;
	int		i;

	len = 0;
	i = 0;
	while (len < n && src[len])
		len++;
	dst = (char *)ft_malloc(len + 1, NULL);
	if (!dst)
		return (NULL);
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
	dst[len] = 0;
	return (dst);
}

void	start_shell(t_minis mini)
{
	char	*line;
	char	*prompt;

	server();
	while (1)
	{
		prompt = get_shell_prefix();
		line = readline(prompt);
		ft_free(prompt,NULL);
		if (line == NULL)
			break ;
		ft_printf("%s\n", line);
		builtins(mini);
		check_syntax(line);
		add_history(line);
		free(line);
	}
}
