/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_list.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:19:37 by jperpct           #+#    #+#             */
/*   Updated: 2024/11/29 14:23:55 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define FREE_AND_LIST_H
#ifdef FREE_AND_LIST_H

# include "list.h"
# include <aio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

/**
 * @brief this function is used for allocate memory 
 * @param size nuber bits for alocade 
 * @param list_set set is null;
 */
void	*ft_malloc(size_t size, void *list_set);

/**
 * @brief this function is used to free memory of the program 
 * @param list_set set is null
 */
void	ft_free_all(void *list_set);

/**
 * @brief this function is used for free in specifly variabel
 * @param var for free memory
 * @param list_set set ins null
 */
void	ft_free(void *var, void *list_set);

/**
 * @brief the start the library the malloc not use not 
 * possible use neither the all function
 */
void	start_alloc(void);

/**
 * @brief alloc the memory reght for Created new node t_list_
 *
 * @param n variabel used in list
 * @return node t_list_ alocad with memory alocade
 */
t_list_	*ft_node_new_free(void *n);

// utilis.c
t_list_	*ft_maolloc_next(t_list_ *list_set, t_list_ *list, size_t size);

t_list_	*ft_node_new_free(void *n);

void	ft_remove(t_list_ **node);

t_list_	*free_next(t_list_ *list);
#endif
