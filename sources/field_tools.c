#include "filler.h"
#include <stdlib.h>
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>

void	read_field(void)
{
	t_field	*ans;
	t_piece	*piece;
	char	*str;
	char	*str2;
	char	c;
	char	fill_symbol;
	size_t	i;
	size_t	j;
	size_t	delta;
	
	FILE *fd;

	fd = fopen("log", "w");
	if (fd < 0)
		file_error();
	if (!(ans = (t_field*)malloc(sizeof(t_field))))
		mall_error();
	piece = (t_piece*)malloc(sizeof(t_piece));
	get_next_line(0, &str);
	fill_symbol = str[10] == '1' ? 'O' : 'X';
	free(str);
	get_next_line(0, &str);
	str2 = &str[7];
	ans->height = ptr_atoi(&str2);
	ans->width = ptr_atoi(&str2);
	free(str);
	ans->cells = (t_cell**)malloc(sizeof(t_cell*) * ans->height);
	i = -1;
	while (++i < ans->height)
		ans->cells[i] = (t_cell*)malloc(sizeof(t_cell) * ans->width);
	//while ((get_next_line(0, &str)))
	get_next_line(0, &str);
	{
		free(str);
		//get_next_line(0, &str);
		//free(str);
		i = -1;
		while (++i < ans->height)
		{
			get_next_line(0, &str);
			delta = 0;
			while (str[delta] != ' ')
				delta++;
			delta++;
			j = -1;
			while (++j < ans->width)
			{
				c = str[delta + j];
				if (c == '.')
					ans->cells[i][j].initial = FREE;
				else if (c == fill_symbol)
					ans->cells[i][j].initial = MY;
				else
					ans->cells[i][j].initial = ENEMY;
			}

			free(str);
		}
		//fprintf(fd, "Map:\n");
		//for (int i = 0; i < ans->height; i++)
		//{
		//	for (int j = 0; j < ans->width; j++)
		//	{
		//		if (ans->cells[i][j].initial == MY)
		//			c = '1';
		//		else if (ans->cells[i][j].initial == ENEMY)
		//			c = '2';
		//		else
		//			c = '.';
		//		fprintf(fd, "%c", c);
		//	}
		//	fprintf(fd, "\n");
		//}
		//fclose(fd);
		get_next_line(0, &str);
		fprintf(fd, " str \"%s\"\n", str);
		str2 = &str[5];
		piece->init_height = ptr_atoi(&str2);
		piece->init_width = ptr_atoi(&str2);
		piece->width = piece->init_width;
		piece->height = piece->init_height;
		free(str);
		fprintf(fd, "w %d h %d\n", piece->width, piece->height);
		piece->cells = (t_piece_cell**)malloc(sizeof(t_piece_cell*) * piece->init_height);
		
		i = -1;
		while (++i < piece->init_height)
		{
			piece->cells[i] = (t_piece_cell*)malloc(sizeof(t_piece_cell) * piece->init_width);
			get_next_line(0, &str);
			j = -1;
			fprintf(fd, " str \"%s\"\n", str);
			while (++j < piece->init_width)
			{
				piece->cells[i][j].init = str[j] == '.' ? 0 : 1;
				fprintf(fd, "str[%d] %c cell %d\n", j, str[j], piece->cells[i][j].init);
			}
			free(str);
		}
		piece->delta_w = 0;
		

		fprintf(fd, "Piece: \n");
		i = -1;
		while (++i < piece->init_height)
		{
			j = -1;
			while (++j < piece->init_width)
				fprintf(fd, "%c", (piece->cells[i][j].init ? '*' : '.'));
			fprintf(fd, "\n");
		}
		
		fclose(fd);

		//i = -1; //obrezka sleva napravo
		//while (++i < piece->init_height)
		//{
		//	j = -1;
		//	while (++j < piece->init_width)
		//		if (piece->cells[i][j].init)
		//			break;
		//	if (j == piece->init_width)
		//		break;
		//	piece->delta_w++;
		//	piece->width--;
		//}
		//i = piece->init_height; //obrezka sprava nalevo
		//while (i)
		//{
		//	i--;
		//	j = -1;
		//	while (++j < piece->init_width)
		//		if (piece->cells[i][j].init)
		//			break;
		//	if (j == piece->init_width)
		//		break;
		//	piece->height--;
		//}
		//i = -1; //obrezka sverhu vniz
		//while (++i < piece->init_width)
		//{
		//	j = -1;
		//	while (++j < piece->init_height)
		//		if (piece->cells[j][i].init)
		//			break;
		//	if (j == piece->init_height)
		//		break;
		//	piece->delta_h++;
		//	piece->height--;
		//}
		//i = piece->init_width; //obrezka snizu vverh
		//while (i)
		//{
		//	i--;
		//	j = -1;
		//	while (++j < piece->init_height)
		//		if (piece->cells[j][i].init)
		//			break;
		//	if (j == piece->init_height)
		//		break;
		//	piece->height--;
		//}
		////sohranit obrezanii piece
		//i = -1;
		//while (++i < piece->height)
		//{
		//	j = -1;
		//	while (++j < piece->width)
		//		piece->cells[i][j].val =
		//		piece->cells[i + piece->delta_h][j + piece->delta_w].init;
		//}
		////call calc func
		//i = -1;
		//while (++i < piece->init_height)
		//	free(piece->cells[i]);
		//free(piece->cells);
	}
}
