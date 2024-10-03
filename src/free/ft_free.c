#include "free.h" 

void	*ft_malloc(size_t size, void *list_set)
{
	t_free			*new;
	static t_free	*list;
	void			*mal;

	if (list_set != NULL && list == NULL)
	{
		list = list_set;
		return (NULL);
	}
	mal = malloc(size);
	if(mal == NULL)
		ft_free(NULL);
	new = ft_node_new(mal);
	ft_node_add_front(&list, new);
	return (mal);
}

void ft_free(void *list_set)
{
	static t_free	*list = NULL;
	t_free *temp;

	if(list == NULL && list_set != NULL)
	{
		list = list_set;
		return;
	}
	list = ft_node_start(list);
	while (list != NULL)
	{
		temp = list->next;
		if(list->content != NULL)
			free(list->content);
		free(list);
		list = temp;
	}

}
