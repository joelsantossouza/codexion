/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 18:10:54 by joesanto          #+#    #+#             */
/*   Updated: 2026/02/05 16:31:14 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <stdint.h>
# include "simulation_control.h"
# include "codexion_parser.h"
# include "codexion_config_control.h"
# include "coder.h"
# include "monitor.h"
# include "errors.h"

typedef enum e_enqueue_status	(*t_enter_on_queue_f)(t_dongle_queue *, t_coder *);

typedef struct s_codexion_config
{
	uint32_t			number_of_coders;
	uint64_t			time_to_burnout;
	uint64_t			time_to_compile;
	uint64_t			time_to_debug;
	uint64_t			time_to_refactor;
	uint32_t			number_of_compiles_required;
	uint64_t			dongle_cooldown;
	t_enter_on_queue_f	scheduler;
}	t_codexion_config;

typedef void *	(*t_routine)(void *);

#endif
