#include <stdio.h>
#include "../includes/coder_internal.h"

struct s_arg
{
	t_coder			*coder;
	enum e_event_id	event_id;
};

void	*test_log(void *arg)
{
	struct s_arg	*log_arg = (struct s_arg*)arg;

	printf("coder_id: %u\n", log_arg->coder->id);
	log_coder_event(log_arg->coder, log_arg->event_id);
	return (0);
}

int	main(void)
{
	int	i;
	int	ncoders = 10;
	t_coder	coders[ncoders];
	pthread_mutex_t	log_mutex = PTHREAD_MUTEX_INITIALIZER;

	init_coder_log();
	for (i = 0; i < ncoders; i++)
	{
		coders[i].id = i + 1;
		coders[i].log_mutex = &log_mutex;
		struct s_arg	log_arg = {&coders[i], i % MAX_EVENTS};
		pthread_create(&coders[i].thread, NULL, test_log, &log_arg);
	}
	for (i = 0; i < ncoders; i++)
		pthread_join(coders[i].thread, NULL);
	return (0);
}
