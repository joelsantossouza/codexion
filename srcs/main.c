#include "codexion.h"
#include "parsing_errors.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	int			parse_stats;
	t_codexion	codexion;

	parse_stats = codexion_parser(&codexion, argc - 1, argv + 1);
	if (parse_stats != 0)
	{
		fprintf(stderr, "%s", parsing_error(parse_stats));
		fprintf(stderr, "%s", USAGE);
	}
	return (0);
}
