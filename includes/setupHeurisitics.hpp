/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setupHeurisitics.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 15:48:23 by glions            #+#    #+#             */
/*   Updated: 2026/02/12 14:32:00 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETUPHEURISTICS_HPP
# define SETUPHEURISTICS_HPP

# include "AlgoStar.hpp"
# include "heuristics.hpp"

using PDBTable = std::unordered_map<Node, int, NodeHash>;

struct PDB
{
	std::vector<std::unordered_set<int>>	patterns;
	std::vector<PDBTable>					pdbs;
};

int	distManhattan(
	const Node 								*a,
	const Node 								*b,
	PDB										*pdb
);
int	distLinearConflict(
	const Node 								*a,
	const Node 								*b,
	PDB										*pdb
);
int	distPDB(
	const Node 								*a,
	const Node 								*b,
	PDB										*pdb
);



#endif