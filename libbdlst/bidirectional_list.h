#ifndef BIDIRECTIONAL_LIST_H
# define BIDIRECTIONAL_LIST_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
typedef struct s_bd_lst
{
	struct s_bd_lst		*next;
	struct s_bd_lst		*prev;
	void				*content;
}						t_bd_lst;

size_t					bd_strlen(const char *s);
int						bd_memcmp(const void *s1, const void *s2, size_t n);
char					*bd_strdup(const char *src);

void					*def_node_cont_copy(void *content);

void					bd_lstprint(t_bd_lst *lst);
t_bd_lst				*bd_parse_from_arr(char **arr);
t_bd_lst				*bd_lstnew(void *content);
t_bd_lst				*bd_lstlast(t_bd_lst *lst);
void					bd_lstadd_front(t_bd_lst **lst, t_bd_lst *new);
int						bd_lstsize(t_bd_lst *lst);
t_bd_lst				*bd_lstlast(t_bd_lst *lst);
t_bd_lst				*bd_lstcopy(t_bd_lst *lst, void *(*cont_copy)(void *));
void					bd_lstsort(t_bd_lst *lst);
void					bd_lstadd_back(t_bd_lst **lst, t_bd_lst *new);
void					bd_lstdelone(t_bd_lst **head, t_bd_lst *lst, void (*del)(void*));
void					bd_lstpush_sort(t_bd_lst **lst, t_bd_lst *new, int (*comp)(t_bd_lst *, t_bd_lst *));
void					bd_lst_insert(t_bd_lst **cur, t_bd_lst *new);
void					bd_lstclear(t_bd_lst **lst, void (*del)(void*));
int						bd_lstmax_cont_len(t_bd_lst *lst);
void					bd_lstiter(t_bd_lst *lst, void (*f)(void *));
t_bd_lst				*bd_lstmap(t_bd_lst *lst, void *(*f)(void *),
						void (*del)(void *));

#endif