/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_utils_extra.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rui <rui@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 20:44:52 by rui               #+#    #+#             */
/*   Updated: 2025/02/03 20:46:22 by rui              ###   ########.fr       */
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
	while ((size_t)i < len)
	{
		dst[i] = src[i];
		i++;
	}
	dst[len] = 0;
	return (dst);
}

char	*ft_strcpy(char *dst, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

void	free_tree(t_btree *node)
{
	if (node == NULL)
		return ;
	free_tree(node->left);
	free_tree(node->right);
	ft_free(node, NULL);
}

bool	is_allspace(char *str)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (!is_whitespace(str[i]))
			return (false);
	}
	ft_free(str, NULL);
	return (true);
}
