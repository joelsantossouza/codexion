#include "codexion.h"
#include "parsing_errors.h"
#include <stdio.h>

void	*start_working()
{
	int	life_time;
	int	burnout_time;
	int	compiling;
	int	debuging;
	int	refactoring;

	get_coder_rules(&burnout_time, &compiling, &debuging, &refactoring);
	life_time = burnout_time;
	while (life_time)
	{
		pthread_cond_timedwait(ready_to_compile, life_time);
		life_time = burnout_time;
		spend_time(compiling, life_time);
		spend_time(debuging, life_time);
		spend_time(refactoring, life_time);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int			parse_stats;
	t_codexion	codexion;

	parse_stats = codexion_parser(&codexion, argc - 1, argv + 1);
	if (parse_stats != 0)
	{
		fprintf(stderr, "%s", get_error_str(parse_stats));
		fprintf(stderr, "%s", USAGE);
		return (1);
	}
	return (0);
}
