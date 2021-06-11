#ifndef BIDIRECTIONAL_LIST_H
# define BIDIRECTIONAL_LIST_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
typedef struct s_bd_lst
{
	struct s_bd_lst		*next;
	struct s_bd_lst		*prev;
	void				*data;
}						t_blst;

size_t					bd_strlen(const char *s);
int						bd_memcmp(const void *s1, const void *s2, size_t n);
char					*bd_strdup(const char *src);
int						bd_strcmp(const char *s1, const char *s2);
void					node_print(void *data);

void		bd_lstinsert(t_blst **cur, t_blst *new);
t_blst	*bd_lstfind(t_blst *lst, void *data, int size, int (*comp)());

void		bd_lstdelone(t_blst *lst, void (*del)(void*));
void		bd_lstclear(t_blst **lst, void (*del)(void *));
void		bd_lstremove(t_blst **head, t_blst *cur, void (*del)(void *));
void		bd_lstrelink(t_blst *n1, t_blst *n2, t_blst *new);

t_blst	*bd_lstnew(void *data);
t_blst	*bd_lstlast(t_blst *lst);
int			bd_lstsize(t_blst *lst);
void		bd_lstadd_front(t_blst **lst, t_blst *new);
void		bd_lstadd_back(t_blst **lst, t_blst *new);
void		bd_lstpush_sort(t_blst **lst, t_blst *new, int (*comp)(t_blst *, t_blst *));

void		bd_lstiter(t_blst *lst, void (*f)(void *));
void		*def_cont_copy(void *data);
void		bd_lstprint(t_blst *lst, void (*print)(void *));
t_blst	*bd_lstcopy(t_blst *list, void *(*data_copy)(void *));
t_blst	*bd_lstmap(t_blst *lst, void *(*f)(void *), void (*del)(void *));
int			bd_lstmax_cont_len(t_blst *lst);
t_blst	*bd_lstfind(t_blst *lst, void *data, int size, int (*comp)()); //CHECK IF WORKS CORRECTLY
void		bd_lstsort_merge(t_blst **head, int (*comp)());
void		bd_lstsplit(t_blst *lst, t_blst **first_part, t_blst **second_part);
t_blst	*bd_lst_compared_merge(t_blst *n1, t_blst *n2, int (*comp)());
t_blst	*bd_lst_merge(t_blst **n1, t_blst **n2);

t_blst	*bd_parse_from_arr(char **arr, void *(*copy)(void *));
char		**bd_parse_to_arr(t_blst *lst, void *(*copy)(void *));


#endif