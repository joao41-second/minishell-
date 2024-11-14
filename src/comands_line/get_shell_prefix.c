/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shell_prefix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 11:26:12 by rpires-c          #+#    #+#             */
/*   Updated: 2024/11/14 18:23:11 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


char *get_user(void)
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char *username = NULL;

    fp = fopen("/etc/passwd", "r");
    if (fp == NULL) {
        return "";
    }

    while ((read = getline(&line, &len, fp)) != -1)
	{
        char *token = strtok(line, ":");
        if (token != NULL) {
            if (username == NULL) {
                username = strdup(token);
            }
            for (int i = 0; i < 5; i++) {
                token = strtok(NULL, ":");
            }
        }
    }

    fclose(fp);
    if (line) {
        free(line);
    }

    return username;
}

char *get_host_from_session(void)
{
    char *host;
    char *hostname;
    int fd;

    fd = open("/etc/hostname", O_RDONLY);
    if (fd == -1)
        return "";
    hostname = ft_malloc(256, NULL);
    if (hostname == NULL)
	{
		close(fd);
        return "";	
	}
    if (read(fd, hostname, 256) > 0)
	{
        hostname[strcspn(hostname, "\n")] = '\0';
        char *dot = strchr(hostname, '.');
        if (dot)
            *dot = '\0';
        host = strdup(hostname);
    }
	else 
        host = "";
    ft_free(hostname, NULL);
    close(fd);
    return host;
}

char	*build_prefix_aux(char *cwd, size_t cwd_size, char *home)
{
	size_t	home_len;
	int		cwd_starts_with_home;

	if (!getcwd(cwd, cwd_size))
	{
		ft_printf_fd (2, "Error: Could not get current working directory\n");
		return (NULL);
	}
	if (home)
	{
		home_len = ft_strlen(home);
		cwd_starts_with_home = (ft_strncmp(cwd, home, home_len) == 0
				&& cwd[home_len] == '/');
		if (cwd_starts_with_home)
		{
			ft_memmove(cwd + 1, cwd + home_len, ft_strlen(cwd + home_len) + 1);
			cwd[0] = '~';
		}
	}
	return (cwd);
}

char	*build_prefix(char *user, char *host, t_minis *mini)
{
	char	*prefix;
	char	*ext_code;
	size_t	prefix_len;
	char	cwd[1024];
	char	*home;

	home = ft_getenv(mini, "HOME");
	if (!build_prefix_aux(cwd, sizeof(cwd), home))
		return (NULL);
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
	ft_free (host, NULL);
	return (prefix);
}
