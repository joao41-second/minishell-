#define FREE_H
#ifdef FREE_H		

#include <stdlib.h>
#include <aio.h>
#include "../../libft/printf/ft_printf.h"


typedef struct s_list_
{
	void			*content;
	struct s_list_	*next;
	struct s_list_	*previous;
} t_list_;

void *ft_malloc(size_t size,void* list_set);

void ft_free_all(void *list_set);


void ft_free(void *var,void *list_set);

t_list_	*ft_node_new(void * n);

void	ft_node_add_front(t_list_ **lst, t_list_ *new);

t_list_	*ft_node_start(t_list_ *list);







#endif
