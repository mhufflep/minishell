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
int						bd_strcmp(const char *s1, const char *s2);
	
t_bd_lst	*bd_lstnew(void *content);
t_bd_lst	*bd_lstlast(t_bd_lst *lst);
int			bd_lstsize(t_bd_lst *lst);
void		bd_lstadd_front(t_bd_lst **lst, t_bd_lst *new);
void		bd_lstadd_back(t_bd_lst **lst, t_bd_lst *new);
void		bd_lst_insert(t_bd_lst **cur, t_bd_lst *new); //CHECK IF WORKS CORRECTLY
void		bd_lstpush_sort(t_bd_lst **lst, t_bd_lst *new, int (*comp)(t_bd_lst *, t_bd_lst *)); //CHECK IF WORKS CORRECTLY
void		bd_lstdelone(t_bd_lst **head, t_bd_lst *lst, void (*del)(void*));
void		bd_lstclear(t_bd_lst **lst, void (*del)(void*));
void		bd_lstiter(t_bd_lst *lst, void (*f)(void *));
void		*def_cont_copy(void *content);
void		bd_lstprint(t_bd_lst *lst);
t_bd_lst	*bd_lstcopy(t_bd_lst *list, void *(*content_copy)(void *));
t_bd_lst	*bd_lstmap(t_bd_lst *lst, void *(*f)(void *), void (*del)(void *));
int			bd_lstmax_cont_len(t_bd_lst *lst);
t_bd_lst	*bd_lstfind(t_bd_lst *lst, void *data, int (*comp)()); //CHECK IF WORKS CORRECTLY
void		bd_lstsort_merge(t_bd_lst **head, int (*comp)());
void		bd_lstsplit(t_bd_lst *lst, t_bd_lst **first_part, t_bd_lst **second_part);
t_bd_lst	*bd_lst_compared_merge(t_bd_lst *n1, t_bd_lst *n2, int (*comp)());
t_bd_lst	*bd_lst_merge(t_bd_lst **n1, t_bd_lst **n2);
t_bd_lst	*bd_parse_from_arr(char **arr); //add copy cont function
char		**bd_parse_to_arr(t_bd_lst *lst); //add copy cont function


#endif