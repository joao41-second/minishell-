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
		ft_free_all(NULL);
	new = ft_node_new(mal);
	ft_node_add_front(&list, new);
	return (new->content);
}

void ft_free_all(void *list_set)
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
			ft_printf("\n%x\n",list->content);
		temp = list->next;
		if(list->content != NULL)
			free(list->content);
		free(list);
		list = temp;
	}
}

void ft_free(void *var,void *list_set)
{
	static t_free *list;

	t_free *temp;
	if(list == NULL && list_set != NULL)
	{
		list = list_set;
		return;
	}
	temp = list;
	while (temp != NULL)
	{
		if(temp->content == var)
		{
			ft_printf("\nestive aqui%x\n",temp->content);
			free(temp->content);
			temp->content = NULL;
		}
		temp = temp->next;
	}
	
	ft_printf("\n%p oi\n",var);
	//ft_printf("\n%p\n",var);
	
}
