/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:44:50 by jperpct           #+#    #+#             */
/*   Updated: 2024/10/15 16:53:36 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h" 

static void new_line(int sig, siginfo_t *info, void *ucontext)
{
	if(sig == SIGINT)
	{
		ft_free_all();
		exit(1);
	}

}

void	server()
{
	struct sigaction	sa;
	static int			a;

	a = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = new_line;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	//sigaction(SIGINT, &sa, NULL);
}

