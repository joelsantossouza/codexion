#include "codexion.h"
#include "parsing_errors.h"
#include <stdio.h>

void	test_this(void);

int	get_coder_rules(int *burnout, int *compile, int *debug, int *refactor)
{
	static int	already_initialized = FALSE;
	static int	time_to_burnout;
	static int	time_to_compile;
	static int	time_to_debug;
	static int	time_to_refactor;

	if (already_initialized == FALSE)
	{
		already_initialized = TRUE;
		time_to_burnout = *burnout;
		time_to_compile = *compile;
		time_to_debug = *debug;
		time_to_refactor = *refactor;
		return (FALSE);
	}
	*burnout = time_to_burnout;
	*compile = time_to_compile;
	*debug = time_to_debug;
	*refactor = time_to_refactor;
	return (TRUE);
}

void	print_values(int burnout, int compile, int debug, int refactor)
{
	printf("Burnout: %d\n", burnout);
	printf("Compile: %d\n", compile);
	printf("Debug: %d\n", debug);
	printf("Refactor: %d\n", refactor);
}

int	main(int argc, char **argv)
{
	int			parse_stats;
	t_codexion	codexion;

	parse_stats = codexion_parser(&codexion, argc - 1, argv + 1);
	if (parse_stats != 0)
	{
		fprintf(stderr, "%s", parsing_error(parse_stats));
		fprintf(stderr, "%s", USAGE);
		return (1);
	}
	get_coder_rules(
		&codexion.time_to_burnout,
		&codexion.time_to_compile,
		&codexion.time_to_debug,
		&codexion.time_to_refactor
	);
	test_this();
	return (0);
}

void	test_this(void)
{
	int burnout;
	int compile;
	int debug;
	int refactor;

	get_coder_rules(&burnout, &compile, &debug, &refactor);
	print_values(burnout, compile, debug, refactor);
}
