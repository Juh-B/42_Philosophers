/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:53:23 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/06/23 16:53:25 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc < 5 || argc > 6)
		error_exit("Wrong input:\nExpected: "EXP_INPUT EXEMP_INPUT, &table);
	verif_input(argc, argv, &table);
	init_structs(&table, argc, argv);
	simulation(&table);
	clean_all(&table);
	return (0);
}
