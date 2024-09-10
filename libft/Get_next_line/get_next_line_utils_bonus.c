/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpect <jperpect@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:16:58 by jperpect          #+#    #+#             */
/*   Updated: 2024/08/16 12:18:31 by jperpect         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_strlens(char *str)
{
	int	a;

	if (str == NULL)
		return (0);
	a = 0;
	while (str[a] != '\0')
	{
		a++;
	}
	return (a);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	cont;
	char	*str;

	cont = 0;
	str = (char *)s;
	{
		while (cont < n)
		{
			str[cont] = '\0';
			cont++;
		}
	}
}

int	ft_caract_cont(char *str)
{
	int	a;
	int	c;

	c = 0;
	a = 0;
	if (str == NULL)
	{
		return (0);
	}
	while (str[a] != '\0')
	{
		if (str[a] == '\n')
			c++;
		if (c > 0)
			break ;
		a++;
	}
	return (c);
}

char	*ft_concatenat_str(char *orig, char *second)
{
	int		len;
	int		i;
	char	*ret;
	int		origs;

	origs = ft_strlens(orig);
	i = -1;
	len = origs + ft_strlens(second) + 1;
	ret = (char *)malloc(len * sizeof(char));
	if (ret == NULL)
		return (NULL);
	ft_bzero(ret, len);
	if (orig != NULL)
	{
		while (orig[++i] != '\0')
			ret[i] = orig[i];
		free(orig);
	}
	i = -1;
	while (second[++i] != '\0')
		ret[origs + i] = second[i];
	ret[origs + i] = '\0';
	return (ret);
}

char	*ft_copy(char *str, int a, int frees)
{
	char	*ret;
	int		i;

	i = -1;
	ret = (char *)malloc(a + 1 * sizeof(char));
	if (ret == NULL)
		return (NULL);
	ft_bzero(ret, a + 1);
	while (++i < a)
		ret[i] = str[i];
	ret[i] = '\0';
	if (frees == 1)
		free(str);
	return (ret);
}

// int main(int ac,char **av)
// {
// 	// char *ok =ft_concatenat_str(av[1],av[2]);
// 	// printf("%s",ok);
// 	// free(ok);
// 	//printf("len %d", ft_caract_cont("ola \n vamos la \n para a merda  \n"));
// }
