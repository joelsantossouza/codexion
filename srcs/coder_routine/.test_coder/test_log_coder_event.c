#include <stdlib.h>
#include "../includes/coder_internal.h"

struct s_arg
{
	t_coder			*coder;
	enum e_event_id	event_id;
};

void	*test_log(void *arg)
{
	struct s_arg	*log_arg = (struct s_arg*)arg;

	log_coder_event(log_arg->coder, log_arg->event_id);
	return (0);
}

int	main(void)
{
	int	i;
	int	ncoders = 10000;
	t_coder	coders[ncoders];
	struct s_arg	log_arg[ncoders];
	pthread_mutex_t	log_mutex = PTHREAD_MUTEX_INITIALIZER;

	init_coder_log();
	for (i = 0; i < ncoders; i++)
	{
		coders[i].id = i + 1;
		coders[i].log_mutex = &log_mutex;
		log_arg[i] = (struct s_arg) {&coders[i], i % MAX_EVENTS};
		if (pthread_create(&coders[i].thread, NULL, test_log, &log_arg[i]) != 0)
			exit(1);
	}
	for (i = 0; i < ncoders; i++)
		if (pthread_join(coders[i].thread, NULL) != 0)
			exit(1);
	return (0);
}
