#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <stdlib.h>
#include "./get_next_line/get_next_line.h"

const int    width = 210;
const int    height = 50;

typedef struct t_list {
	int end;
	int nbr_zeros;
	int sub;
	int new_space;
	int take_space;
}	s_list;

void    print_array(char **array, s_list *list)
{
    int x = 0;
	int y = 0;
	int i = 0;
	char *print;

	print = calloc(height * width + height + 1, sizeof(char));
    while (y < height)
    {
		x = 0;
		while (x < width)
		{
			print[i] = array[y][x];
			i++;
			x++;
		}
		print[i] = '\n';
		i++;
    	y++;
    }
	write(1, print, ft_strlen(print));
	free(print);
}

int	stream_of_numbers(char ***array, s_list *list)
{
	int i = 0;
	int	print_zeros = 0;
	int rndm;
	list->nbr_zeros;
	while (i < height && print_zeros < list->nbr_zeros)
	{
		rndm = rand() % 50;
		print_zeros++;
		if (rndm % 2 == 0)
			(*array)[rndm][0] = '1';
		else
			(*array)[rndm][0] = '0';
		i++;
	}
	list->nbr_zeros++;
	return (list->nbr_zeros);
}

int	stream_of_numbers2(char ***array, int nbr_zeros, int y, int x, s_list *list)
{
	int i = 0;
	int	print_zeros = 0;
	int rndm;
	while (i < height && print_zeros < nbr_zeros)
	{
		if (rand() % 2 == 0)
		{
			if (rand() % 2 == 0)
				(*array)[y][0] = '0';
			else
				(*array)[y][0] = '1';
		}
		else
		{
			if (rand() % 2 == 0)
				(*array)[y][0] = '0';
			else
				(*array)[y][0] = '1';
		}
		print_zeros++;
		i++;
	}
	return (nbr_zeros);
}

void	reset_background(char ***array, s_list *list)
{
	int i = 0;
	int j = 0;

	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			(*array)[i][j] = ' ';
			j++;
		}
		i++;
	}
}



void	free_array(char ***array)
{
	if (*array)
	{
		for (int i = 0; i < height; i++)
		{
			free((*array)[i]);
		}
		free(*array);
	}
}

void    fill_array(char ***array, s_list *list)
{
    int fd;
    int ret = 1;
    char *line;
    int i = 0;
    int j = 0;

    fd = open("art.txt", O_RDONLY);
	i = 15;
	while (ret > 0 && i < height)
	{
		j = 0;
    	ret = get_next_line(fd, &line);
    	while (j < width && line[j])
    	{
    		(*array)[i][j] = line[j];
    		j++;
    	}
		i++;
		if (line)
		{
			free(line);
			line = NULL;
		}
	}
	list->new_space--;
	close(fd);
}

char	**move_stream(char ***array, s_list *list)
{
	char **new_array;
    new_array = calloc(height + 1, sizeof(char *));
    for (int i = 0; i < height; i++)
    {
   		new_array[i] = calloc(width + 1, sizeof(char));
    }
	reset_background(&new_array, list);
    fill_array(&new_array, list);
	int x = 0;
	int y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (((*array)[y][x] == '1' || (*array)[y][x] == '0') && x < 160)
			{
				int vert_move = rand() % 3;
				int	move_to_middle = rand() % 2;
				if (y > height / 2 && move_to_middle == 1)
				{
					vert_move = 1;
				}
				else if (y < height / 2 && move_to_middle == 1)
				{
					vert_move = 0;
				}
				if (vert_move == 0 && y + 1 < height)
					new_array[y + 1][x + 1] = (*array)[y][x];
				else if (vert_move == 1 && y - 1 >= 0)
					new_array[y - 1][x + 1] = (*array)[y][x];
				else
					new_array[y][x + 1] = (*array)[y][x];
				x++;
			}
			x++;
		}
		y++;
	}
	free_array(array);
	return (new_array);
}

int    fill_array2(char ***array, s_list *list)
{
	FILE file;

	// file = open("brain.txt", O_RDONLY);
    int fd;
	int fd2;
    int ret = 1;
	int ret2 = 1;
    char *line;
	char *line2;
	int		stop_or_not;
    int i = 0;
    int j = 0;

    fd = open("art.txt", O_RDONLY);
	fd2 = open("braini.txt", O_RDONLY);
	i = 15;
	if (list->take_space <= 167)
	{
		stop_or_not = 0;
		while (ret > 0 && ret2 > 0 && i < height)
		{
			j = 0;
			ret = get_next_line(fd, &line);
			while (j < width && line[j + list->take_space])
			{
				(*array)[i][j] = line[j  + list->take_space];
				j++;
			}
			i++;
			if (line)
			{
				free(line);
				line = NULL;
			}
		}
		list->take_space++;
		list->new_space = 210;
	}
	else
	{
		i = 15; //start y brain
		stop_or_not = 1;
		while (ret2 > 0 && i < height)
		{
			j = 0;
			ret2 = get_next_line(fd2, &line2);
			while (j + list->new_space < width && line2[j])
			{
				(*array)[i][j + list->new_space] = line2[j];
				j++;
			}
			i++;
			if (line2)
			{
				free(line2);
				line2 = NULL;
			}
		// printf("%d\n", j + list->new_space);
		}
		if (list->new_space > 36)
			list->new_space--;

	}
	close(fd);
	close(fd2);
	int brain_end = list->new_space + 17; //list->new_space is always 36 in the end => ret is 53
	return (brain_end);
}

char	**move_sideways(char ***array, s_list *list)
{
	char **new_array;
	int  i = 0;
	int ret;
	int vert_move;
	int x,y = 0;

	new_array = calloc(height, sizeof(char **));
	while (i < height)
	{
		new_array[i] = calloc(width, sizeof(char));
		i++;
	}
	reset_background(&new_array, list);
	ret = fill_array2(&new_array, list);
	while (y < height)
	{
		x = 0;
		while (x + 1 < width)
		{
			if (((*array)[y][x] == '1' || (*array)[y][x] == '0'))
			{
				if (ret >= 52 && x < ret + 65)
				{
					vert_move = rand() % 3;
					int	move_to_middle = rand() % 2;
					if (y > height / 2 && move_to_middle == 1)
					{
						vert_move = 1;
					}
					else if (y < height / 2 && move_to_middle == 1)
					{
						vert_move = 0;
					}
					if (vert_move == 0 && y + 1 < height)
						new_array[y + 1][x + 1] = (*array)[y][x];
					else if (vert_move == 1 && y - 1 >= 0)
						new_array[y - 1][x + 1] = (*array)[y][x];
					else
						new_array[y][x + 1] = (*array)[y][x];
				}
				// printf("%d\n", ret);
				if (ret <= 58 && y + 1 < height && y - 1 > 0 && x + 1 < width && x -1 > 0)
				{
					int brain_x = 90;
					int brain_y = 30;
					int dist_x;
					int dist_y;
					int distance;
					if (x > brain_x)
						dist_x = x - brain_x;
					else
						dist_x = brain_x - x;
					if (y > brain_y)
						dist_y = y - brain_y;
					else
						dist_y = brain_y - y;
					distance = sqrt(pow(dist_x, 2) + pow(dist_y, 2));
					int move = rand() % 4;
					if (move == 0 && distance < 10)
						new_array[y + 1][x + 1] = (*array)[y][x];
					else if (move == 1 && distance < 10)
						new_array[y + 1][x - 1] = (*array)[y][x];
					else if (move == 2 && distance < 10)
						new_array[y - 1][x - 1] = (*array)[y][x];
					else if (distance < 10)
						new_array[y - 1][x + 1] = (*array)[y][x];
				}
			}
			x++;
		}
		new_array[y][x] = ' ';
		y++;
	}
	// if (*array)
		// free_array(array);
	return (new_array);
}

char	**explode(char ***array, s_list *list)
{
	char **new_array;
	int  i = 0;
	int ret;
	int x,y = 0;

	new_array = calloc(height, sizeof(char **));
	while (i < height)
	{
		new_array[i] = calloc(width, sizeof(char));
		i++;
	}
	reset_background(&new_array, list);
	while (y < height)
	{
		x = 0;
		while (x + 1 < width)
		{
			if ((*array)[y][x] != ' ')
			{
				int new_x = x;
				int new_y = y;
				int brain_x = 90;
				int brain_y = 30;
				int extra_move = rand() % 4;
				if (x > brain_x)
				{
					new_x++;
					if (extra_move == 0)
						new_x -= 2;
				}
				else
				{
					new_x--;
					if (extra_move == 1)
						new_x += 2;
				}
				if (y > brain_y)
				{
					new_y++;
					if (extra_move == 2)
						new_y -= 2;
				}
				else
				{
					new_y--;
					if (extra_move == 3)
						new_y += 2;
				}
				
				if (new_y + 1 < height && new_y - 1 > 0 && new_x + 1 < width && new_x -1 > 0)
				new_array[new_y][new_x] = (*array)[y][x];
			}
			x++;
		}
		new_array[y][x] = ' ';
		y++;
	}
	// if (*array)
		// free_array(array);
	return (new_array);
}

void	set_struct(s_list *list)
{
	list->end = 0;
	list->nbr_zeros = 0;
	list->sub = 0;
	list->new_space = 0;
	list->take_space = 0;
}

void	eye_comming(char ***array, s_list *list)
{
	int fd; 
	int ret = 1;
	char *line;
	int i = 15;
	int j;

	fd = open("art.txt", O_RDONLY);
	while (ret > 1 && i < height)
	{
		j = 0;
		ret = get_next_line(fd, &line);
		while (j + list->new_space < width && line[j])
		{
			(*array)[i][j + list->new_space] = line[j];
			j++;
		}
		i++;
		if (line)
		{
			free(line);
			line = NULL;
		}
	}
	if (list->new_space > 36)
		list->new_space--;
	close(fd);
}


int    main(void)
{
	s_list list;

	
	set_struct(&list);
	time_t t;
	int nbr;
	srand((unsigned) time(&t));
    char **array;
    array = calloc(height + 1, sizeof(char *));
    for (int i = 0; i < height; i++)
    {
   		array[i] = calloc(width + 1, sizeof(char));
    }
	reset_background(&array, &list);
    fill_array(&array, &list);
	while (1)
	{
		set_struct(&list);
		int count = 0;
		while (1)
		{
			nbr = stream_of_numbers(&array, &list);
			array = move_stream(&array, &list);
			print_array(array, &list);
			usleep(15000);
			if (nbr == 170)
				break ;

		}
		int nbr_zeros = 50;
		int y = 48;
		int x = 0;
		while (1)
		{
			count++;
			nbr = stream_of_numbers2(&array, nbr_zeros ,y, x, &list);
			array = move_sideways(&array, &list);
			print_array(array, &list);
			if (y > 0)
				y--;
			if (y < 25)
				y++;
			if (x < 49)
				x++;
			if (x > 25)
				x--;
			usleep(15000);
			if (count == 380)
				break ;
		}
		count = 1;
		while (1)
		{
			array = explode(&array, &list);
			print_array(array, &list);
			if (count < 8)
				usleep(count * 10000);
			else
				usleep(80000);
			count++;
			if (count == 70)
				break;
		}
	}
}