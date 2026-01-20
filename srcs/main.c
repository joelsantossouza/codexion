#include "codexion.h"
#include <pthread.h>
#include <stdio.h>
#include "private_coder_routine.h"
#include "private_monitor_routine.h"

//typedef char	t_byte;
//
//typedef struct s_coder
//{
//	int				id;
//	t_byte			is_ready_to_compile;
//	pthread_mutex_t	local_mutex;
//	pthread_mutex_t	*global_mutex;
//}	t_coder;
//
//int	timed_wait(t_byte *flag, int max_time)
//{
//	while (*flag == FALSE)
//	{
//		max_time -= time_passed;
//		if (max_time <= 0)
//			return (-1);
//	}
//	return (0);
//}
//
//void	spend_time(unsigned int time, int *total_life_time)
//{
//	if (*total_life_time <= 0)
//		return ;
//	if (time < *total_life_time)
//	{
//		*total_life_time -= time;
//		return (sleep(time));
//	}
//	sleep(*total_life_time);
//	*total_life_time = 0;
//}
//
//void	*start_working(t_coder *coder)
//{
//	int	life_time;
//	int	burnout_time;
//	int	compiling;
//	int	debuging;
//	int	refactoring;
//
//	get_coder_rules(&burnout_time, &compiling, &debuging, &refactoring);
//	life_time = burnout_time;
//	while (life_time > 0)
//	{
//		if (timed_wait(&ready_to_compile, life_time) == -1)
//			return (0);
//		life_time = burnout_time;
//		spend_time(compiling, life_time);
//		spend_time(debuging, life_time);
//		spend_time(refactoring, life_time);
//	}
//	return (0);
//}
//
//// CREATE THE FUNCTION millis()
//
//void	*monitor(t_coder *coders[])
//{
//	int	number_of_coders;
//	int	dongle_cooldown;
//	int	number_of_compiles_required;
//	int	available_dongles;
//	int	i;
//
//	get_monitor_rules(&number_of_coders, &dongle_cooldown, &number_of_compiles_required);
//	available_dongles = number_of_coders;
//	while (1)
//	{
//		i = -1;
//		while (++i < number_of_coders)
//		{
//			if (all_coders_compiled_required_times())
//				return (0);
//			share_dongles(&availables_dongles, coders[i]);
//		}
//	}
//	return (0);
//}

int	main(int argc, char **argv)
{
	t_codexion	codexion;
	t_coder		coders[200];
	int			parse_stats;
	uint32_t	i = -1;
	pthread_t	monitor_thread;
	pthread_mutex_t	global_mutex = PTHREAD_MUTEX_INITIALIZER;

	parse_stats = codexion_parser(&codexion, argc - 1, argv + 1);
	if (parse_stats != 0)
	{
		fprintf(stderr, "%s", get_error_str(parse_stats));
		return (1);
	}
	coder_config(&codexion.time_to_burnout, &codexion.time_to_compile, &codexion.time_to_debug, &codexion.time_to_refactor);
	monitor_config(&codexion.number_of_coders, &codexion.dongle_cooldown, &codexion.number_of_compiles_required, &codexion.scheduler);
	uint64_t	program_start = millis();
	timestamp(&program_start);
	while (++i < codexion.number_of_coders)
	{
		coders[i].id = i + 1;
		pthread_mutex_init(&coders[i].local_mutex, NULL);
		coders[i].global_mutex = &global_mutex;
		coders[i].state = 0;
		coders[i].compilations_done = 0;
		coders[i].compilations_history.first = 0;
		coders[i].compilations_history.last = 0;
		coders[i].execution_remaining = codexion.time_to_burnout;
		pthread_create(&coders[i].thread, NULL, (t_routine)start_working, &coders[i]);
	}
	pthread_create(&monitor_thread, NULL, (t_routine)start_monitoring, coders);
	while (++i < codexion.number_of_coders)
		pthread_join(coders[i].thread, NULL);
	pthread_join(monitor_thread, NULL);
	return (0);
}
