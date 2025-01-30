/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_for_new_file.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rui <rui@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:30:26 by jperpct           #+#    #+#             */
/*   Updated: 2025/01/30 18:01:29 by rui              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../herdoc.h"

int	redirect_for_new_file(t_minis *mini, t_token *name)
{
	int	fds;

	(void)*mini;
	fds = open(name->redirection_target, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	return (fds);
}

int	redirect_for_add_file(t_minis *mini, t_token *name)
{
	int	fds;

	(void)*mini;
	fds = open(name->redirection_target, O_CREAT | O_WRONLY | O_APPEND, 0644);
	return (fds);
}
