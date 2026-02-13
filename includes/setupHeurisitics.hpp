/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setupHeurisitics.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 15:48:23 by glions            #+#    #+#             */
/*   Updated: 2026/02/13 15:14:01 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETUPHEURISTICS_HPP
# define SETUPHEURISTICS_HPP

# include "AlgoStar.hpp"
# include "heuristics.hpp"
# include "PatternDatabase.hpp"

using PDBTable = std::unordered_map<PatternState, int, PatternHash>;

int	distManhattan(
	const Node 								*a,
	const Node 								*b,
	const PatternDatabase					*pdb
);
int	distLinearConflict(
	const Node 								*a,
	const Node 								*b,
	const PatternDatabase					*pdb
);
int	distPDB(
	const Node 								*a,
	const Node 								*b,
	const PatternDatabase					*pdb
);

#endif