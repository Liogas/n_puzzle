/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AlgoStar.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 10:53:17 by glions            #+#    #+#             */
/*   Updated: 2026/02/09 12:31:28 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGOSTAR_HPP
# define ALGOSTAR_HPP

# include <algorithm>
# include <functional>
# include <unordered_map>
# include <unordered_set>
# include <queue>

# include "Node.hpp"
# include "setupHeurisitics.hpp"

enum class HeuristicType
{
	Manhattan,
	LinearConflict
};

using Heuristic = std::function<int(const Node&, const Node&)>;

class AlgoStar
{
	public:
		// constructor //
		AlgoStar(const Node &start, const Node &goal);
		// methods //
		bool start(HeuristicType h);
	private:
		// props //
		int														_expandedNodes;
		int														_maxStates;
		Node 													_start;
		Node 													_goal;
		Heuristic												_heuristic;
		std::priority_queue<Node, std::vector<Node>, NodeCmp>	_opened;
		std::unordered_set<Node, NodeHash>						_closed;
		std::unordered_map<Node, int, NodeHash>					_distances;
		std::unordered_map<Node, Node, NodeHash>				_fathers;
		std::unordered_map<HeuristicType, Heuristic>			_heuristics;
		// methods //
		void	setHeuristic(HeuristicType h);
		void 	showResult();
};

#endif