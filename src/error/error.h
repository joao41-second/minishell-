/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:25:24 by jperpct           #+#    #+#             */
/*   Updated: 2024/12/03 10:25:24 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define NOT_FILE "No such file or directory"
# define TOO_ARG "too many arguments"
# define NOT_NUB "numeric argument required"
# define INV_OPT "invalid option"
# define NOT_HOME "HOME not set"
# define SNTAX_ERROR "not a valid identifier"
# define REC_FILE "filename argument required"
# define DIR "is a directory"
# define NOT_COMAND "command not found"

//# define SNTAX_ERROR "not a valid identifier"

void	ft_print_error(char *comand, char *error, char *error_char,
			char *start);

int		too_arg_print(char *comand, int args, t_minis *mini);

int		not_opcion(t_minis *mini, char *comand);

#endif // !
