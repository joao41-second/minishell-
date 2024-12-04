/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:24:52 by jperpct           #+#    #+#             */
/*   Updated: 2024/12/03 10:24:52 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

void ft_print_error(char *comand, char *error,char *error_char, char* start)
{
	ft_putstr_fd(start, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(comand, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error , 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error_char, 2);
	ft_putstr_fd("\n", 2);
}

void ft_error(t_minis *mini)
{


}
