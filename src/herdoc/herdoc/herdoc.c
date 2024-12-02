/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:09:31 by jperpct           #+#    #+#             */
/*   Updated: 2024/11/29 15:26:12 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_signal(int sig)
{
	get_signal(sig + 128);
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		ft_free_all(NULL);
		exit(sig + 128);
	}
}

int	not_join(int not, char join)
{
	if (join == '$' || join == ' ')
		not = 0;
	if (not > 0)
	{
		not--;
	}
	return (not);
}

void	start_var_expand_heradoc(char **ret, char *set, char **temp)
{
	set[1] = '\0';
	*ret = ft_strdup("");
	*temp = ft_strdup("");
}

char	*expand_heradoc(t_minis *mini, char *str)
{
	char	*ret;
	char	set[3];
	char	*temp;
	int		not_print;
	int		i;

	i = -1;
	not_print = 0;
	start_var_expand_heradoc(&ret, set, &temp);
	while (str[++i] != '\0')
	{
		set[0] = str[i];
		not_print = not_join(not_print, str[i]);
		if (not_print > 0)
			continue ;
		if (str[i] == '$')
		{
			temp = concatenate_the_str_with_env_var(&str[i], mini, &not_print);
			ret = ft_strjoin_and_free(ret, temp);
			ft_free(temp, NULL);
		}
		else
			ret = ft_strjoin_and_free(ret, set);
	}
	return (ret);
}

void	loop_heradoc(char *line, char *new_line, char *end, t_minis *mini)
{
	while (ft_strncmp(line, end, ft_strlen(end) + 15) != 0)
	{
		free(line);
		line = readline(">");
		if (line == NULL)
		{
			ft_exit(mini);
			return ;
		}
		new_line = expand_heradoc(mini, line);
		printf("new_line %s\n", new_line);
	}
}

void	herdoc_son_proceed(t_minis *mini, char*end)
{
	char	*line;
	char	*new_line;

	signal(SIGUSR1, handle_signal);
	if (end != NULL)
	{
		signal(SIGINT, handle_signal);
		if (get_signal(0) == 130)
			ft_exit(mini);
		line = readline(">");
		new_line = expand_heradoc(mini, line);
		if (line == NULL)
		{
			ft_exit(mini);
			return ;
		}
		mini->exit_code_error = 1;
		loop_heradoc(line, new_line, end, mini);
		free(line);
	}
	else
		ft_putstr_fd("error \n", 2);
	ft_exit(mini);
}
void	print_erro_line_herdoc(t_minis *mini,char *end,int status)
{
	if (WSTOPSIG(status) == 0)
	{
		mini->readline++;
		ft_putstr_fd("bash: warning: here-document at line ", 2);
		ft_putnbr_fd(mini->readline, 2);
		ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
		ft_putstr_fd(end, 2);
		ft_putstr_fd("')\n", 2);
	}
}

void	herdoc(t_minis *mini, int set, char *end)
{
	pid_t			pid;
	int				status;
	struct rusage	usage;

	if (set != 1)
		return ;
	pid = fork();
	if (pid < 0)
		ft_putstr_fd("error \n", 2);
	else if (pid == 0)
		herdoc_son_proceed(mini, end);
	else
	{
		signal(SIGINT, SIG_IGN);
		usleep(1);
		wait3(&status, 0, &usage);
		print_erro_line_herdoc(mini, end, status);
		get_signal(WSTOPSIG(status));
	}
}
