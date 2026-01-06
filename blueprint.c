typedef struct s_rules
{
	int	burnout;
	int	compile;
	int	debug;
	int	refactor;
}	t_rules;

typedef struct s_coder
{
	int				id;
	const t_rules	*time_to;
}	t_coder;

typedef struct s_monitor
{
	int	number_of_coders;
	int	dongle_cooldown;
	int	number_of_compiles_required;
}	t_monitor;

int	main(int argc, char **argv)
{
	const t_rules rules = {
		.burnout = 200,
		.compile = 50,
		.debug = 50,
		.refactor = 50,
	};
	t_coder	coders[2];

	// CREATE A FUNCTION THAT RETURNS THE STATIC RULES MEMORY
	coders[0] = (t_coder){
		.id = 1,
		.time_to = &rules,
	};

	coders[0] = (t_coder){
		.id = 2,
		.time_to = &rules,
	};
}
