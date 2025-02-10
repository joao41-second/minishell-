/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minis.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:27:38 by jperpct           #+#    #+#             */
/*   Updated: 2025/02/04 11:29:03 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MINIS_H
#ifdef MINIS_H

typedef struct s_mines
{
	t_list_	*env;
	t_list_	*env_org;
	int		readline;
	t_list_	*tokens;
	t_list_	*tokens_copy;
	char	path[PATH_MAX];
	char	*line;
	char	**split;
	int		comand;
	int		exit_code_error;
	int		pid;
	int		pips[2];
}			t_minis;

#endif
