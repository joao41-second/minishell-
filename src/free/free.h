#define FREE_H
#ifdef FREE_H		

#include <stdlib.h>
#include <aio.h>
typedef struct s_list_
{
	void			*content;
	struct s_list_	*next;
	struct s_list_	*previous;
} t_free;


void *ft_malloc(size_t size,void* list_set);


t_free	*ft_node_new(void * n);

void	ft_node_add_front(t_free **lst, t_free *new);

t_free	*ft_node_start(t_free *list);







#endif
