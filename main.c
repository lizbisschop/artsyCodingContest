#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <stdlib.h>
#include "./gnl/get_next_line.h"

const int    width = 210;
const int    height = 50;


void    print_array(char **array)
{
    int x = 0;
	int y = 0;
	int i = 0;
	char *print;

	// print = calloc(height * width + height + 1, sizeof(char));
    // while (y < height)
    // {
	// 	x = 0;
	// 	while (x < width)
	// 	{
	// 		print[i] = array[y][x];
	// 		i++;
	// 		x++;
	// 	}
	// 	print[i] = '\n';
	// 	i++;
    // 	y++;
    // }
	// write(1, print, ft_strlen(print));
	// free(print);

	while (y < height)
	{
		printf("%s\n", array[y]);
		y++;
	}
}

void	stream_of_numbers(char ***array)
{
	int i = 0;
	int	print_zeros = 0;
	int rndm;

	static int nbr_zeros;

	while (i < height && print_zeros < nbr_zeros)
	{
		rndm = rand() % 50;
		print_zeros++;
		if (rndm % 2 == 0)
			(*array)[rndm][0] = '1';
		else
			(*array)[rndm][0] = '0';
		i++;
	}
	nbr_zeros++;
}

void	reset_background(char ***array)
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

void    fill_array(char ***array)
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
	close(fd);
}

char	**move_stream(char ***array)
{
	char **new_array;
    new_array = calloc(height + 1, sizeof(char *));
    for (int i = 0; i < height; i++)
    {
   		new_array[i] = calloc(width + 1, sizeof(char));
    }
	reset_background(&new_array);
    fill_array(&new_array);
	int x = 0;
	int y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if ((*array)[y][x] == '1' || (*array)[y][x] == '0')
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





int    main(void)
{
	time_t t;
	srand((unsigned) time(&t));
    char **array;
    array = calloc(height + 1, sizeof(char *));
    for (int i = 0; i < height; i++)
    {
   		array[i] = calloc(width + 1, sizeof(char));
    }
	reset_background(&array);
    fill_array(&array);
	while (1)
	{
		stream_of_numbers(&array);
		array = move_stream(&array);
	    print_array(array);
		usleep(15000);
		// system("clear");
	}
}