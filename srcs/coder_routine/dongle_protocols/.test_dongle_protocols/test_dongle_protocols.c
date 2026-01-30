#include "../includes/dongle_protocols.h"
#include "../../includes/coder_internal.h"
#include "../../utils/time_utils/time_utils.h"
#include "../../schedulers/includes/schedulers.h"

#define SLEEP_TIME_US	3000
#define ODD				0
#define EVEN			1

pthread_mutex_t	log_mutex = PTHREAD_MUTEX_INITIALIZER;
uint64_t		cooldown = 100;

void	*coder_loop(void *arg)
{
	t_coder	*coder = (t_coder*)arg;

	while (1)
	{
		request_two_dongles(coder);
		log_coder_event(coder, EVENT_COMPILING);
		usleep(SLEEP_TIME_US);
		release_two_dongles(coder);
	}
}

void	start_coders(int start, int size, t_coder coders[size], t_dongle dongles[size])
{
	int	i = start;

	while (i < size)
	{
		coders[i].id = i + 1;
		
		coders[i].right_dongle = &dongles[(i + 1) % size];
		coders[i].right_neighboor = &coders[(i + 1) % size];

		coders[i].left_dongle = &dongles[(i - 1 + size) % size];
		coders[i].left_neighboor = &coders[(i - 1 + size) % size];

		coders[i].deadline_ms = millis() + 1000000000;
		set_abstime(&coders[i].deadline_ts, 1000000000);

		pthread_mutex_init(&coders[i].mutex, NULL);
		pthread_cond_init(&coders[i].cond, NULL);
		coders[i].log_mutex = &log_mutex;
		coders[i].wait_my_turn = wait_fifo_turn;

		pthread_create(&coders[i].thread, NULL, coder_loop, &coders[i]);
		i += 2;
	}
}

void	init_dongles(int size, t_dongle dongles[size])
{
	int i = 0;

	while (i < size)
	{
		pthread_mutex_init(&dongles[i].mutex, NULL);
		dongles[i].cooldown = &cooldown;
		dongles[i].cooldown_end_ms = 0;
		dongles[i].queue.head = 0;
		dongles[i].queue.tail = 0;
		pthread_mutex_init(&dongles[i].queue.mutex, NULL);
	}
}

int	main(void)
{
	int			ncoders = 2;
	t_dongle	dongles[ncoders];
	t_coder		coders[ncoders];

	init_dongles(ncoders, dongles);
	start_coders(ODD, ncoders, coders, dongles);
	start_coders(EVEN, ncoders, coders, dongles);
	for (int i = 0; i < ncoders; i++)
		pthread_join(coders[i].thread, NULL);
	return (0);
}
