
#define LIST_H
#ifdef LIST_H

//#include "free.h"

typedef struct s_list_
{
	void			*content;
	struct s_list_	*next;
	struct s_list_	*previous;
} t_list_;

t_list_	*ft_node_new(void * n);

void	ft_node_add_front(t_list_ **lst, t_list_ *new);

t_list_	*ft_node_start(t_list_ *list);

void print_list(t_list_ *list,void(*print)(void*));


int	ft_list_size(t_list_ *list);
t_list_	*ft_node_end(t_list_ *list);

#endif
