#include "free_and_list.h" 
#include <stdio.h>
t_list_	*ft_node_new_free(void *n)
{
	t_list_	*new_node;

	new_node = (t_list_ *)malloc(1 * sizeof(t_list_));
	if (new_node == NULL)
		return (NULL);
	new_node->content = n;
	new_node->next = NULL;
	new_node->previous = NULL;
	return (new_node);
}


void	*ft_malloc(size_t size, void *list_set)
{
	t_list_			*new;
	static t_list_	*list;
	void			*mal;

	if( list_set != NULL &&  size == 134)
	{
		list = list_set;
		return NULL;
	}
	if (list_set != NULL && list == NULL)
	{
		list = list_set;
		return (NULL);
	}
	if(list == NULL)
		write(2,"error\n",10);
	mal = malloc(size);
	if(mal == NULL)
	{
		ft_free_all(NULL);
		write(2,"error_remove_the_limited_memory_bitch\n",40);
		exit(1);
	}
	new = ft_node_new_free(mal);
	if(new == NULL)
	{
		ft_free_all(NULL);
		write(2,"error_remove_the_limited_memory_bitch\n",40);
		exit(1);
	}
	//list = ft_node_end(list);
	ft_node_add_front(&list, new);
	//list = ft_node_start(list);
	return (new->content);
}

void	ft_free_all(void *list_set)
{
	static t_list_	*list = NULL;
	t_list_			*temp;

	if (list == NULL && list_set != NULL)
	{
		list = list_set;
		return ;
	}
	list = ft_node_start(list);
	while (list != NULL)
	{
		temp = list->next;
		if (list->content != NULL)
			free(list->content);
		free(list);
		list = temp;
	}
}

void ft_emove(t_list_ **node)
{
	t_list_ *prv;
	t_list_ *nex;
	t_list_ *temp;

	temp = *node;
	nex = temp->next;
	prv = temp->previous;
	nex->previous = prv;
	prv->next = nex;
	free(*node);
	*node = prv;	
}

void ft_remove(t_list_ **node)
{
	t_list_ *prv;
	t_list_ *temp;

	temp = *node;
	prv = temp->previous;
	prv->next = NULL;
	free(*node);
	*node = prv;	
}


void ft_free(void *var,void *list_set)
{
	static t_list_ *list;
	t_list_	*temp;

	if(list == NULL && list_set != NULL)
	{
		list = list_set;
		return;
	}
	temp = list;
	while (list != NULL)
	{
		if(list->content == var)
		{
			free(list->content);
			list->content = NULL;
			var = NULL;
			if(list->next == NULL )
			{
				ft_remove(&list);	
				ft_malloc(134,list);
			}
			else if( list->next !=NULL && list->previous != NULL)
			{
				 ft_emove(&list);	
			}
			break;
		}
		list = list->next;
	}
	list = temp;
}

void start_alloc()
{
	t_list_ * list;
	
	list = ft_node_new_free(malloc(sizeof(1))); 
	ft_malloc(3,list);
	ft_free_all(list);
	ft_free(NULL,list);
}
