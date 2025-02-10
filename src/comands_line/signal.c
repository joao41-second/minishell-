/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:44:50 by jperpct           #+#    #+#             */
/*   Updated: 2025/02/10 18:15:39 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	new_line(int sig, siginfo_t *info, void *ucontext)
{
	(void)info;
	(void)ucontext;
	get_signal(sig + 128);
	if (sig == SIGINT)
	{
		ft_printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	new_line_fork(int sig, siginfo_t *info, void *ucontext)
{
	(void)info;
	(void)ucontext;
	get_signal(sig + 128);
	ft_exit_end(sig + 128);
}

static void	new_line_fork_2(int sig, siginfo_t *info, void *ucontext)
{
	(void)info;
	(void)ucontext;
	get_signal(sig + 128);
	ft_putstr_fd("\n", 2);
}

void	server_fork(int chek)
{
	struct sigaction	sa;

	if (chek == TRUE)
	{
		sigemptyset(&sa.sa_mask);
		sa.sa_sigaction = new_line_fork;
		sa.sa_flags = SA_RESTART;
		sigaction(SIGQUIT, &sa, NULL);
		sigaction(SIGINT, &sa, NULL);
		signal(SIGTSTP, SIG_IGN);
	}
	if (chek == FALSE)
	{
		sigemptyset(&sa.sa_mask);
		sa.sa_sigaction = new_line_fork_2;
		sa.sa_flags = SA_RESTART;
		sigaction(SIGQUIT, &sa, NULL);
		sigaction(SIGINT, &sa, NULL);
		signal(SIGTSTP, SIG_IGN);
	}
}

void	server(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = new_line;
	sa.sa_flags = SA_RESTART;
	signal(SIGQUIT, SIG_IGN);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}
