/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rui <rui@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:25:24 by jperpct           #+#    #+#             */
/*   Updated: 2025/01/30 18:48:25 by rui              ###   ########.fr       */
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
# define DIR "Is a directory"
# define NOT_COMAND "command not found"
# define NOT_PERM "Permission denied"
# define NOT_ACCESS "cannot access file"
# define BROKEN_SOFT_LINK "broken symbolic link"
# define IS_SOCKET "is a socket"
# define IS_BLOCK "is a block device"
# define IS_CHAR "is a character device"
# define IS_PIPE "is a FIFO/pipe"
# define NOT_REG_FILE "not a regular file"

# include "../minishell.h"
# include "../comands_line/readline.h"
//# define SNTAX_ERROR "not a valid identifier"

void	ft_print_error(char *comand, char *error, char *error_char,
			char *start);

void	ft_print_error_simple(char *comand, char *error, char *start);

int		too_arg_print(char *comand, int args, t_minis *mini);

int		not_opcion(t_minis *mini, char *comand);

#endif // !
