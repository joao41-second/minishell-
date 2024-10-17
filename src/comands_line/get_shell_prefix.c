/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shell_prefix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 11:26:12 by rpires-c          #+#    #+#             */
/*   Updated: 2024/10/17 14:43:46 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#include <unistd.h>

char	*get_user(void)
{
	char	*user;

	user = getenv("USER");
	if (!user)
	{
		ft_printf("Error: Could not get USER environment variable\n");
		return (NULL);
	}
	return (user);
}

char	*get_host_from_session(char *session_manager)
{
	char	*start;
	char	*end;
	char	*host;
	size_t	session_len;

	session_len = ft_strlen(session_manager);
	start = ft_strnstr(session_manager, "local/", session_len);
	if (!start)
	{
		ft_printf("Error: SESSION_MANAGER formatis missing 'local/'\n");
		return (NULL);
	}
	start += 6;
	end = ft_strchr(start, '.');
	if (!end)
	{
		ft_printf("Error: SESSION_MANAGER format is invalid (missing '.')\n");
		return (NULL);
	}
	host = ft_strndup(start, end - start);
	if (!host)
		return (NULL);
	return (host);
}

char	*build_prefix(char *user, char *host)
{
	char	*prefix;
	size_t	prefix_len;
	char	cwd[1024];

	if (!getcwd(cwd, sizeof(cwd)))
	{
		ft_printf("Error: Could not get current working directory\n");
		return (NULL);
	}
	prefix_len = ft_strlen(user) + ft_strlen(host) + ft_strlen(cwd) + 5;
	prefix = (char *)ft_malloc(prefix_len + 1, NULL);
	if (!prefix)
	{
		ft_printf("Error: Memory allocation failed for prefix\n");
		return (NULL);
	}
	prefix[0] = '\0';
	ft_strlcat(prefix, user, prefix_len + 1);
	ft_strlcat(prefix, "@", prefix_len + 1);
	ft_strlcat(prefix, host, prefix_len + 1);
	ft_strlcat(prefix, ":~", prefix_len + 1);
	ft_strlcat(prefix, cwd, prefix_len + 1);
	ft_strlcat(prefix, "$ ", prefix_len + 1);
	return (prefix);
}

char	*get_shell_prefix(void)
{
	char	*user;
	char	*host;
	char	*prefix;
	char	*session_manager;

	user = get_user();
	if (!user)
		return (NULL);
	session_manager = getenv("SESSION_MANAGER");
	if (!session_manager)
	{
		ft_printf("Error: Could not get SESSION_MANAGER\n");
		return (NULL);
	}
	host = get_host_from_session(session_manager);
	if (!host)
		return (NULL);
	prefix = build_prefix(user, host);
	free(host);
	return (prefix);
}