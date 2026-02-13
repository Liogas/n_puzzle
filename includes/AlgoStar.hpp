/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AlgoStar.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 10:53:17 by glions            #+#    #+#             */
/*   Updated: 2026/02/13 15:10:12 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGOSTAR_HPP
# define ALGOSTAR_HPP

# include <functional>

# include "setupHeurisitics.hpp"
# include "PatternDatabase.hpp"
# include "Node.hpp"

enum class HeuristicType
{
	Manhattan,
	LinearConflict,
	PDB
};

using Heuristic = std::function<int(
	const Node 								*a,
	const Node 								*b,
	const PatternDatabase					*pdb
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
		PatternDatabase											_pdb;
		// methods //
		int			calcHeuristic(const Node &n);
		void		setHeuristic(HeuristicType h);
		void 		showResult();
};

#endif