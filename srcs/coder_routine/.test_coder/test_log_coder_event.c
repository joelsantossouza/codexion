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
	t_coder	coders[10];

	init_coder_log();
	for (i = 0; i < 10; i++)
	{
		coders[i].id = i + 1;
		struct s_arg	log_arg = {&coders[i], i};
		pthread_create(&coders[i].thread, NULL, test_log, &log_arg);
	}
	for (i = 0; i < 10; i++)
		pthread_join(coders[i].thread, NULL);
	return (0);
}
