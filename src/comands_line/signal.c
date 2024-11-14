/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:44:50 by jperpct           #+#    #+#             */
/*   Updated: 2024/11/12 20:59:42 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

int	get_signal(int sig)
{
	static int	signals;
	
	if (sig != 0)
	{
		printf("a mudar o");
		signals = sig;
	}
	printf("%d sig\n",sig);	
	return (signals);
}

static void	new_line(int sig, siginfo_t *info, void *ucontext)
{
	(void)info;
	(void)ucontext;
	get_signal(sig+128);
	if (sig == SIGINT)
	{
		ft_printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	server(void)
{
	struct sigaction	sa;
	static int			a;

	a = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = new_line;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}
