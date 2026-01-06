/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 15:41:04 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/06 16:12:07 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# define TRUE	1
# define FALSE	0

typedef struct s_codexion
{
	int			number_of_coders;
	int			time_to_burnout;
	int			time_to_compile;
	int			time_to_debug;
	int			time_to_refactor;
	int			number_of_compiles_required;
	int			dongle_cooldown;
	const char	*scheduler;
}	t_codexion;

// PARSER
const char *parsing_error(unsigned int error_code);
int			codexion_parser(t_codexion *codexion, int argc, char **argv);

#endif
