#include "free.h" 

void *ft_malloc(size_t size,void* list_set)
{
  	//va_list	args;
	t_free *new;
	static t_free *list = NULL;
	void *mal;

	if (list_set != NULL && list == NULL)
	{
		list = list_set;
		return(NULL);
	}	
	mal = malloc(size);
	
	new = ft_node_new(mal);
	ft_node_add_front(&list, new);
	
	
	return(mal);
}

