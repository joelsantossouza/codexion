#include "../includes/public_codexion_parser.h"
#include "../../errors/includes/errors.h"
#include <stdio.h>

#define MAX_SIZE	100
#define LEN(array) (sizeof(array) / sizeof(*array))

int		argv_len(char *argv[])
{
	int	len;

	len = 0;
	while (*argv++)
		len++;
	return (len);
}

void	argv_print(char *argv[])
{
	if (!*argv)
	{
		printf("Empty...\n");
		return ;
	}
	printf("%s", *argv++);
	while (*argv)
		printf(", %s", *argv++);
	printf("\n");
}

void	test_cases(int size, char *argv[size][MAX_SIZE])
{
	t_codexion	codexion;
	int			exit_status;
	int			i;

	i = -1;
	while (++i < size)
	{
		printf("Test-%02d: ", i); argv_print(argv[i]);
		exit_status = codexion_parser(&codexion, argv_len(argv[i]), argv[i]);
		if (exit_status != SUCCESS)
		{
			printf("\e[0;31m");
			printf("%s\n", get_error_str(exit_status));
			//printf("%s\n", PROGRAM_USAGE);
		}
		else
		{
			printf("\e[0;32m");
			printf("number_of_coders: %d\n", codexion.number_of_coders);
			printf("time_to_burnout: %d\n", codexion.time_to_burnout);
			printf("time_to_compile: %d\n", codexion.time_to_compile);
			printf("time_to_debug: %d\n", codexion.time_to_debug);
			printf("time_to_refactor: %d\n", codexion.time_to_refactor);
			printf("number_of_compiles_required: %d\n", codexion.number_of_compiles_required);
			printf("dongle_cooldown: %d\n", codexion.dongle_cooldown);
		}
		printf("----------------------------\n");
		printf("\e[0m");
	}
}

int	main(void)
{
	char *argc_error[][MAX_SIZE] = {
		{NULL},
		{"1", NULL},
		{"1", "2", NULL},
		{"1", "2", "3", NULL},
		{"1", "2", "3", "4", NULL},
		{"1", "2", "3", "4", "5", NULL},
		{"1", "2", "3", "4", "5", "6", NULL},
		{"1", "2", "3", "4", "5", "6", "7", NULL},
		{"1", "2", "3", "4", "5", "6", "7", "8", "9", NULL},
		{"1", "2", "3", "4", "5", "6", "7", "8", NULL},
	};

	printf("ARGC_ERROR\n");
	test_cases(LEN(argc_error), argc_error);

	char *scheduler_error[][MAX_SIZE] = {
		{"100", "100", "100", "100", "100", "100", "100", "figaro", NULL},
		{"100", "100", "100", "100", "100", "100", "100", "edff", NULL},
		{"100", "100", "100", "100", "100", "100", "100", "fifoi", NULL},
		{"100", "100", "100", "100", "100", "100", "100", "fifo", NULL},
		{"100", "100", "100", "100", "100", "100", "100", "edf", NULL},
	};

	printf("SCHEDULER_ERROR\n");
	test_cases(LEN(scheduler_error), scheduler_error);

	char *nonnumeric_error[][MAX_SIZE] = {
		{"a100", "100", "100", "100", "100", "100", "100", "fifo", NULL},
		{"100", "1x00", "100", "100", "100", "100", "100", "fifo", NULL},
		{"100", "100", "1p00", "100", "100", "100", "100", "fifo", NULL},
		{"100", "100", "100", "--100", "cd100", "100", "100", "fifo", NULL},
		{"100", "100", "100", "100", "100", "100", " 100 ", "fifo", NULL},
		{"100", "100", "100", "100", "100", "100", " 100", "fifo", NULL},
		{"100", "100", "100", "100", "100", "100", "1 00", "fifo", NULL},
		{"100", "100", "100", "100", "100", "100", "10\n0", "fifo", NULL},
	};

	printf("NONNUMERIC_ERROR\n");
	test_cases(LEN(nonnumeric_error), nonnumeric_error);

	char *negative_error[][MAX_SIZE] = {
		{"-100", "100", "100", "100", "100", "100", "100", "fifo", NULL},
		{"100", "-100", "100", "100", "100", "100", "100", "fifo", NULL},
		{"100", "100", "-0", "100", "100", "100", "100", "fifo", NULL},
		{"100", "100", "100", "-00", "100", "100", "100", "fifo", NULL},
		{"100", "100", "100", "100", "-+00", "100", "100", "fifo", NULL},
		{"100", "100", "100", "100", "100", "-0000000", "100", "fifo", NULL},
		{"100", "100", "100", "100", "100", "100", "-000000000001", "fifo", NULL},
	};

	printf("NEGATIVE_ERROR\n");
	test_cases(LEN(negative_error), negative_error);

	char *overflow_error[][MAX_SIZE] = {
		{"2147483647", "100", "100", "100", "100", "100", "100", "fifo", NULL},
		{"100", "2147483648", "100", "100", "100", "100", "100", "fifo", NULL},
		{"100", "100", "100", "100", "100", "100", "-2147483649", "fifo", NULL},
		{"100", "100", "100", "100", "-2147483647214748364721474836472147483647", "100", "100", "fifo", NULL},
		{"100", "100", "100", "100", "+2147483647214748364721474836472147483647214748364721474836472147483647214748364721474836472147483647", "100", "100", "fifo", NULL},
		{"18446744073709551617", "100", "100", "100", "100", "100", "100", "fifo", NULL},
	};

	printf("OVERFLOW_ERROR\n");
	test_cases(LEN(overflow_error), overflow_error);
}
