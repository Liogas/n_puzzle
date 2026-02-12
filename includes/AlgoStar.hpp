/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AlgoStar.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 10:53:17 by glions            #+#    #+#             */
/*   Updated: 2026/02/12 14:31:42 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGOSTAR_HPP
# define ALGOSTAR_HPP

# include <algorithm>
# include <functional>
# include <unordered_map>
# include <queue>

# include "Node.hpp"
# include "setupHeurisitics.hpp"

struct PDB;

enum class HeuristicType
{
	Manhattan,
	LinearConflict,
	PDB
};

using PDBTable = std::unordered_map<Node, int, NodeHash>;

using Heuristic = std::function<int(
	const Node 								*a,
	const Node 								*b,
	PDB										*pdb
)>;

class AlgoStar
{
	public:
		// constructor //
		AlgoStar(const Node &start, const Node &goal);
		// methods //
		bool 	start(HeuristicType h);
	private:
		// props //
		int														_expandedNodes;
		int														_maxStates;
		Node 													_start;
		Node 													_goal;
		HeuristicType											_heuristicT;
		Heuristic												_heuristic;
		std::priority_queue<Node, std::vector<Node>, NodeCmp>	_opened;
		std::unordered_set<Node, NodeHash>						_closed;
		std::unordered_map<Node, int, NodeHash>					_distances;
		std::unordered_map<Node, Node, NodeHash>				_fathers;
		std::unordered_map<HeuristicType, Heuristic>			_heuristics;
		std::vector<std::unordered_set<int>>					_patterns;
		std::vector<PDBTable>									_pdbs;
		// methods //
		int			calcHeuristic(const Node &n);
		void		setHeuristic(HeuristicType h);
		void 		showResult();
		void		buildPatterns();
		void		buildAllPDBs();
		PDBTable	buildPDB(std::unordered_set<int> &pattern);
		
};

#endif