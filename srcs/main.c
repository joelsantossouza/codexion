#include "codexion.h"
#include "parsing_errors.h"
#include <stdio.h>

typedef char	t_byte;

typedef struct s_coder
{
	int				id;
	t_byte			is_ready_to_compile;
	pthread_mutex_t	local_mutex;
	pthread_mutex_t	*global_mutex;
}	t_coder;

int	timed_wait(t_byte *flag, int max_time)
{
	while (*flag == FALSE)
	{
		max_time -= time_passed;
		if (max_time <= 0)
			return (-1);
	}
	return (0);
}

void	spend_time(unsigned int time, int *total_life_time)
{
	if (*total_life_time <= 0)
		return ;
	if (time < *total_life_time)
	{
		*total_life_time -= time;
		return (sleep(time));
	}
	sleep(*total_life_time);
	*total_life_time = 0;
}

void	*start_working(t_coder *coder)
{
	int	life_time;
	int	burnout_time;
	int	compiling;
	int	debuging;
	int	refactoring;

	get_coder_rules(&burnout_time, &compiling, &debuging, &refactoring);
	life_time = burnout_time;
	while (life_time > 0)
	{
		if (timed_wait(&ready_to_compile, life_time) == -1)
			return (0);
		life_time = burnout_time;
		spend_time(compiling, life_time);
		spend_time(debuging, life_time);
		spend_time(refactoring, life_time);
	}
	return (0);
}

void	*monitor()
{

}

int	main(int argc, char **argv)
{
	int			parse_stats;
	t_codexion	codexion;

	parse_stats = codexion_parser(&codexion, argc - 1, argv + 1);
	if (parse_stats != 0)
	{
		fprintf(stderr, "%s", get_error_str(parse_stats));
		fprintf(stderr, "%s", PROGRAM_USAGE);
		return (1);
	}
	return (0);
}
