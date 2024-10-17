#define FREE_H
#ifdef FREE_H		

#include <stdlib.h>
#include <aio.h>
#include "list.h"
#include <unistd.h>


void *ft_malloc(size_t size,void* list_set);

void ft_free_all(void *list_set);

void ft_free(void *var,void *list_set);

t_list_	*ft_node_new_free(void * n);



#endif
