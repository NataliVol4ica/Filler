#include "filler.h"
#include <stdlib.h>
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>

void	read_field(void)
{
	t_field	*map;
	t_piece	*piece;
	char	*str;
	char	*str2;
	char	c;
	char	my_symbol;
	size_t	i;
	size_t	j;
	size_t	i1, j1;
	size_t	delta;
	size_t	temp;
	size_t	counter;
	size_t	quit;
	size_t	optx, opty, opt;
	_Bool	first_reading;
	
	FILE *fd;

	fd = fopen("log", "w");
	if (fd < 0)
		file_error();
	if (!(map = (t_field*)malloc(sizeof(t_field))))
		mall_error();
	piece = (t_piece*)malloc(sizeof(t_piece));
	get_next_line(0, &str);
	my_symbol = str[10] == '1' ? 'O' : 'X';
	free(str);
	get_next_line(0, &str);
	str2 = &str[7];
	map->height = ptr_atoi(&str2);
	map->width = ptr_atoi(&str2);
	free(str);
	map->cells = (t_cell**)malloc(sizeof(t_cell*) * map->height);
	i = -1;
	while (++i < map->height)
		map->cells[i] = (t_cell*)malloc(sizeof(t_cell) * map->width);
	first_reading = 1;
	while ((get_next_line(0, &str)))
	{
		if (!first_reading)
		{
			free(str);
			get_next_line(0, &str);
		}
		first_reading = 0;
		free(str);
		//get_next_line(0, &str);
		//free(str);
		i = -1;
		while (++i < map->height)
		{
			get_next_line(0, &str);
			delta = 0;
			while (str[delta] != ' ')
				delta++;
			delta++;
			j = -1;
			while (++j < map->width)
			{
				c = str[delta + j];
				if (c == '.')
					map->cells[i][j].initial = FREE;
				else if (c == my_symbol)
					map->cells[i][j].initial = MY;
				else
					map->cells[i][j].initial = ENEMY;
			}

			free(str);
		}
		fprintf(fd, "Map:\n");
		for (int i = 0; i < map->height; i++)
		{
			for (int j = 0; j < map->width; j++)
			{
				if (map->cells[i][j].initial == MY)
					c = '1';
				else if (map->cells[i][j].initial == ENEMY)
					c = '2';
				else
					c = '.';
				fprintf(fd, "%c", c);
			}
			fprintf(fd, "\n");
		}
		get_next_line(0, &str);
		str2 = &str[5];
		piece->init_height = ptr_atoi(&str2);
		piece->init_width = ptr_atoi(&str2);
		piece->width = piece->init_width;
		piece->height = piece->init_height;
		free(str);
		piece->cells = (t_piece_cell**)malloc(sizeof(t_piece_cell*) * piece->init_height);
		
		i = -1;
		while (++i < piece->init_height)
		{
			piece->cells[i] = (t_piece_cell*)malloc(sizeof(t_piece_cell) * piece->init_width);
			get_next_line(0, &str);
			j = -1;
			while (++j < piece->init_width)
				piece->cells[i][j].init = str[j] == '.' ? 0 : 1;
			free(str);
		}
		piece->delta_w = 0;
		piece->delta_h = 0;
		

		fprintf(fd, "Piece: \n");
		i = -1;
		while (++i < piece->init_height)
		{
			j = -1;
			while (++j < piece->init_width)
				fprintf(fd, "%c", (piece->cells[i][j].init ? '*' : '.'));
			fprintf(fd, "\n");
		}
		
		i = -1; //obrezka sverhu vniz 
		while (++i < piece->init_height)
		{
			j = -1;
			while (++j < piece->init_width)
				if (piece->cells[i][j].init)
					break;
			if (j != piece->init_width)
				break;
			piece->delta_h++;
			piece->height--;
		}
		i = piece->init_height; //obrezka snizu vverh
		while (i)
		{
			i--;
			j = -1;
			while (++j < piece->init_width)
				if (piece->cells[i][j].init)
					break;
			if (j != piece->init_width)
				break;
			piece->height--;
		}
		i = -1; //obrezka sleva napravo
		while (++i < piece->init_width)
		{
			j = -1;
			while (++j < piece->init_height)
				if (piece->cells[j][i].init)
					break;
			if (j != piece->init_height)
				break;
			piece->delta_w++;
			piece->width--;
		}
		i = piece->init_width; //obrezka snizu vverh
		while (i)
		{
			i--;
			j = -1;
			while (++j < piece->init_height)
				if (piece->cells[j][i].init)
					break;
			if (j != piece->init_height)
				break;
			piece->width--;
		}
		//sohranit obrezanii piece
		i = -1;
		while (++i < piece->height)
		{
			j = -1;
			while (++j < piece->width)
				piece->cells[i][j].val =
				piece->cells[i + piece->delta_h][j + piece->delta_w].init;
		}
		fprintf(fd, "Cut piece: %d %d\n", piece->height, piece->width);
		i = -1;
		while (++i < piece->height)
		{
			j = -1;
			while (++j < piece->width)
				fprintf(fd, "%c", (piece->cells[i][j].val ? '*' : '.'));
			fprintf(fd, "\n");
		}
		//finished reading and input parsing
		
		//cleaning extra maps
		temp = map->width * map->height;
		i = -1;
		while (++i < map->height && (j = -1))
			while (++j < map->width)
			{
				map->cells[i][j].valid = 0;
				if (map->cells[i][j].initial == ENEMY)
					map->cells[i][j].closest = 0;
				else
					map->cells[i][j].closest = temp;
			}
		//filling valid map
		i = -1;
		while (++i < map->height - piece->height + 1 && (j = -1))
			while (++j < map->width - piece->width + 1)
			{
				counter = 0;
				i1 = -1;
				while (++i1 < piece->height && (j1 = -1))
					while (++j1 <piece->width)
						if (piece->cells[i1][j1].val)
							counter += map->cells[i + i1][j + j1].initial;
				if (counter == 1)
					map->cells[i][j].valid = 1;
				else
					map->cells[i][j].valid = 0;
			}
		fprintf(fd, "Valid map:\n");
		for (int i = 0; i < map->height; i++)
		{
			for (int j = 0; j < map->width; j++)
				fprintf(fd, "%c", (map->cells[i][j].valid ? 'T' : '.'));
			fprintf(fd, "\n");
		}
		//filling distance map
		counter = 0;
		opt = 0;
		quit = 0;
		while (!quit && !opt)
		{
			quit = 1;
			i = -1;
			while (!opt && ++i < map->height && (j = -1))
				while (!opt && ++j < map->width)
				{
					if (map->cells[i][j].closest == counter)
					{
						quit = 0;
						if (i > 0 && map->cells[i - 1][j].closest > counter + 1)
							map->cells[i - 1][j].closest = counter + 1;
						if (j > 0 && map->cells[i][j - 1].closest > counter + 1)
							map->cells[i][j - 1].closest = counter + 1;
						if (i < map->height - 1 && map->cells[i + 1][j].closest > counter + 1)
							map->cells[i + 1][j].closest = counter + 1;
						if (j < map->width - 1 && map->cells[i][j + 1].closest > counter + 1)
							map->cells[i][j + 1].closest = counter + 1;
						if (map->cells[i][j].valid)
						{
							opt = 1;
							optx = i;
							opty = j;
						}
					}
				}
			counter++;
		}
		fprintf(fd, "Distance map:\n");
		for (int i = 0; i < map->height; i++)
		{
			for (int j = 0; j < map->width; j++)
				fprintf(fd, "%d", map->cells[i][j].closest % 10);
			fprintf(fd, "\n");
		}
		if (opt)
		{
			fprintf(fd, "Map of a valid piece:\n");
			for (int i1 = 0; i1 < map->height; i1++)
			{
				for (int j1 = 0; j1 < map->width; j1++)
					if (i1 - optx >= 0 && i1 - optx < piece->height &&
						j1 - opty >= 0 && j1 - opty < piece->width)
					{
						if (piece->cells[i1 - optx][j1 - opty].val)
							fprintf(fd, "#");
						else
							fprintf(fd, ".");
					}
					else if (map->cells[i1][j1].initial)
						fprintf(fd, "%d", map->cells[i1][j1].initial);
					else
						fprintf(fd, ".");
				fprintf(fd, "\n");
			}
		}
		if (opt)
			fprintf(fd, " Ans %d %d\n", optx - piece->delta_h, opty - piece->delta_w);
		if (opt)
			ft_printf("%d %d\n", optx - piece->delta_h, opty - piece->delta_w);
		else
			break ;
		//cleaning
		i = -1;
		while (++i < piece->init_height)
			free(piece->cells[i]);
		free(piece->cells);
	}
	fclose(fd);
}
