/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_validation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oklymeno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 16:32:31 by oklymeno          #+#    #+#             */
/*   Updated: 2017/06/09 19:15:49 by oklymeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm_header.h"

unsigned int	move_bits(unsigned int num)
{
	unsigned int fs;
	unsigned int s;
	unsigned int t;
	unsigned int fo;

	fs = num >> 24;
	s = (num << 8) >> 24;
	t = (num << 16) >> 24;
	fo = (num << 24) >> 24;
	num = (fo << 24) + (t << 16) + (s << 8) + fs;
	return (num);
}

static t_player	*get_player(t_header *header, int fd, int numb)
{
	t_player		*player;
	unsigned char	*com;
	static int		vis_numb = 1;

	player = malloc(sizeof(t_player) + 1);
	player->header = header;
	com = malloc(header->prog_size);
	read(fd, com, header->prog_size);
	player->commands = com;
	player->numb = numb;
	player->vis_numb = vis_numb++;
	player->next = NULL;
	return (player);
}

static void		check_file(char *file)
{
	char	**res;
	int		i;

	i = 0;
	res = ft_strsplit(file, '.');
	while (res[i])
		i++;
	if (ft_strcmp(res[i - 1], "cor"))
	{
		while (--i >= 0)
			free(res[i]);
		free(res);
		print_error_file(file);
	}
	while (--i >= 0)
		free(res[i]);
	free(res);
}

t_player		*read_file_vm(char *file, int numb)
{
	int			fd;
	char		*res;
	t_header	*header;

	check_file(file);
	res = malloc(sizeof(char *) * sizeof(t_header));
	fd = open(file, O_RDONLY);
	read(fd, res, sizeof(t_header));
	header = (t_header *)res;
	header->magic = move_bits(header->magic);
	header->prog_size = move_bits(header->prog_size);
	if (header->prog_size > CHAMP_MAX_SIZE)
		print_size_error(header->prog_name);
	if (header->magic != COREWAR_EXEC_MAGIC)
		print_cant_read_source_file(file);
	return (get_player(header, fd, numb));
}
