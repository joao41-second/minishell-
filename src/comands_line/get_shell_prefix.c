/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shell_prefix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 11:26:12 by rpires-c          #+#    #+#             */
/*   Updated: 2024/11/15 18:42:16 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_hostname(void)
{
	char	hostname[256];
	int		fd;
	int		len;
	char	*result;

	fd = open("/etc/hostname", O_RDONLY);
	if (fd == -1)
		return ("");
	len = read(fd, hostname, sizeof(hostname) - 1);
	close(fd);
	if (len <= 0)
		return ("");
	hostname[len] = '\0';
	result = ft_strdup(hostname);
	return (result);
}

char	*get_host_from_session(void)
{
	char	*host;
	char	*dot;
	char	*hostname;

	hostname = get_hostname();
	if (hostname[0] == '\0')
		return ("");
	dot = ft_strchr(hostname, '.');
	if (dot)
		*dot = '\0';
	host = ft_strdup(hostname);
	ft_free(hostname, NULL);
	return (host);
}

char	*build_prefix(char *user, char *host, t_minis *mini)
{
	char	*prefix;
	char	*ext_code;
	size_t	prefix_len;
	char	*cwd;

	cwd = ft_getenv(mini, "PWD");
	prefix_len = ft_strlen(user) + ft_strlen(host) + ft_strlen(cwd) + 10;
	prefix = (char *)ft_malloc(prefix_len + 1, NULL);
	if (!prefix)
		return (NULL);
	prefix[0] = '\0';
	ext_code = ft_itoa(mini->exit_code_error);
	ft_strlcat(prefix, user, prefix_len + 1);
	ft_strlcat(prefix, "@", prefix_len + 1);
	ft_strlcat(prefix, host, prefix_len + 1);
	ft_strlcat(prefix, ":", prefix_len + 1);
	ft_strlcat(prefix, cwd, prefix_len + 1);
	ft_strlcat(prefix, "$ [", prefix_len + 1);
	ft_strlcat(prefix, ext_code, prefix_len + 1);
	ft_strlcat(prefix, "]: ", prefix_len + 1);
	ft_free(ext_code, NULL);
	return (prefix);
}

char	*get_shell_prefix(t_minis *mini)
{
	char	*user;
	char	*host;
	char	*prefix;

	user = get_user();
	if (!user)
		return (NULL);
	host = get_host_from_session();
	if (!host)
		return (NULL);
	prefix = build_prefix(user, host, mini);
	ft_free (user, NULL);
	ft_free (host, NULL);
	return (prefix);
}
