/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:18:05 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/04/10 11:26:16 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
  t_table table;

  if (argc < 5 || argc > 6)
    error_exit("Wrong input:\nExpected usage:\n" EXP_INPUT EXEMP_INPUT);
  verif_input(argc, argv);
  init_structs(&table, argc, argv);
  simulation(&table);
  clean_all(&table);
  return (0);
}
