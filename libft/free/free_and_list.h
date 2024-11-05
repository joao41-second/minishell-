/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_list.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:19:37 by jperpct           #+#    #+#             */
/*   Updated: 2024/11/05 11:19:58 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define FREE_AND_LIST_H
#ifdef FREE_AND_LIST_H

# include "list.h"
# include <aio.h>
# include <stdlib.h>
# include <unistd.h>

void	*ft_malloc(size_t size, void *list_set);

void	ft_free_all(void *list_set);

void	ft_free(void *var, void *list_set);

void	start_alloc(void);

t_list_	*ft_node_new_free(void *n);

#endif
