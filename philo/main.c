#include "philo.h"

int main(int argc, char **argv)
{
  t_table table;

  if (argc < 5 || argc > 6)
    error_exit("Wrong input:\nExpected: "EXP_INPUT EXEMP_INPUT);
  verif_input(argc, argv);
  init_structs(&table, argc, argv);
  simulation(&table);
  clean_all(&table);
  return (0);
}
