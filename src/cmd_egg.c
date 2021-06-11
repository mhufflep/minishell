#include "minishell.h"

const char   *FG_COLOR_BLACK = "\033[0;30m";
const char   *FG_COLOR_RED =	"\033[0;31m";
const char   *FG_COLOR_GREEN = "\033[0;32m";
const char   *FG_COLOR_YELLOW = "\033[0;33m";
const char   *FG_COLOR_BLUE = "\033[0;34m";
const char   *FG_COLOR_MAGENTA = "\033[0;35m";
const char   *FG_COLOR_CYAN = "\033[0;36m";
const char   *FG_COLOR_WHITE = "\033[0;37m";

// const char	*FG_COLOR_PURPLE = "\e[38;2;120;61;1852\e[0m";
// const char	*FG_COLOR_GREENCYAN = "\e[38;2;116;245;1762\e[0m";
//purple 120, 61, 185
//green 116, 245, 176
//const char   *FG_COLOR_BEFORE = FG_COLOR_GREEN;
//const char   *FG_COLOR_AFTER = FG_COLOR_WHITE;
const int    DELAY_VALUE_MMS = 7500;
const int    DELAY_BTWN_ITER = 1000000;
const int    MAX_COUNTER = 500;
const int    KEYS = 10;
const int    DIVIDER = MAX_COUNTER / KEYS;
const int    ARR_ROWS = 10;
const int    ARR_COLS = 16;
const int    ARR_LETTERS = 2;
const char    EMPTY = ' ';

const char    arr[ARR_LETTERS][ARR_ROWS][ARR_COLS] = {
           {"222222222222    ", "222222222222    ", "            2222", "            2222", "    22222222    ", "    22222222    ", "2222            ", "2222            ", "    222222222222", "    222222222222" },
           {"        1111    ", "        1111    ", "            1111", "            1111", "            1111", "            1111", "            1111", "            1111", "            1111", "            1111" }
};

char	generate_numeric_char()
{
	return ((char)(48 + random() % 2));
}

void	reset(int *counter, int keys[], int *row_key)
{
	int i;
	*counter = 0;
	*row_key = 0;
	
	i = 0;
	while (i < KEYS)
		keys[i++] = 0;
}

void	print_iter(int keys[KEYS])
{
	int i;
	int j;
	int k;
	
	i = 0;
	while (i < ARR_ROWS)
	{
		k = 0;
		while (k < ARR_LETTERS)
		{
			j = 0;
			while (j < ARR_COLS)
			{
				if (keys[i] == 1)
					print_static_line(arr[k][i][j]);
				else
					print_colored_symbol(FG_COLOR_MAGENTA, generate_numeric_char());
				j++;
			}
			k++;
		}
		printf("\n");
		i++;
	}
}

void	print_logo() {
	int counter;
	int row_key;
	int keys[KEYS];
	
	reset(&counter, keys, &row_key);
	while (counter < MAX_COUNTER)
	{
		clean_screen();
		if (counter % DIVIDER == DIVIDER - 1)
		{
			keys[row_key] = 1;
			row_key++;
		}
		print_iter(keys);
		counter++;
		delay(DELAY_VALUE_MMS);
	}
	delay(DELAY_BTWN_ITER);
	printf("\n"); 
}

void	delay(int milli_seconds)
{
	clock_t start_time;
   
	start_time = clock();
	while (clock() < start_time + milli_seconds);
}

void	print_colored_symbol(const char *color, char symbol)
{
	set_color(color);
	printf("%c", symbol);
}

void	print_static_line(char c)
{
	if (ft_isdigit(c))
		print_colored_symbol(FG_COLOR_GREEN, c);
	else
		printf("%c", EMPTY);
}

void	clean_screen()
{
	printf("\e[1;1H\e[2J");
}

void	set_color(const char *color)
{
	printf("%s", color);
}

int	cmd_21school(t_sh *sh, t_cmd *cmd)
{
	(void)sh;
	(void)cmd;
	print_logo();
	return (0);
}
