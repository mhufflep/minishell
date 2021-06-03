#ifndef EGG_H
# define EGG_H
	
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>



void		set_color(const char *color);
void		print_static_line(char c);
void		print_colored_symbol(const char *color, char symbol);
// int			is_numeric(char symbol);
void		delay(int milli_seconds); 
void		clean_screen();
char		generate_numeric_char();
void		print_logo();
void		print_iter(int keys[]);

#endif