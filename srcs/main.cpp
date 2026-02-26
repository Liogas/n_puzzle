/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 12:43:31 by glions            #+#    #+#             */
/*   Updated: 2026/02/26 16:00:45 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.hpp"
#include "nPuzzle.hpp"
#include "AStar.hpp"

#include <functional>

using Heuristic = std::function<
    int(const NPuzzleState &, const NPuzzleState &)
>;

void startAStar(
	const NPuzzleState	&start,
	const NPuzzleState	&dest,
	Heuristic			heur
)
{
	std::cout << "Start A*" << std::endl;
	std::vector<NPuzzleState> path = AStar(
		start,
		dest,
		[](const NPuzzleState &s){ return s.genNeighbors(); },
		[](const NPuzzleState &s, const NPuzzleState &g){ (void)s; (void)g; return (1); },
		heur
	);
	std::cout << std::endl;
	for (auto s : path)
		printNPuzzleState(s);
}

void startUniform(
	const NPuzzleState	&start,
	const NPuzzleState	&dest
){
	std::cout << "Start uniform-cost" << std::endl;
	std::vector<NPuzzleState> path = AStar(
		start,
		dest,
		[](const NPuzzleState &s){ return s.genNeighbors(); },
		[](const NPuzzleState &s, const NPuzzleState &g){ (void)s; (void)g; return (1); },
		[](const NPuzzleState &s, const NPuzzleState &g) { (void)s; (void)g; return (0); }
	);
	std::cout << "Size du path : " << path.size() << std::endl;
	std::cout << std::endl;
	for (auto s : path)
		printNPuzzleState(s);
}

void startGreedy(
	const NPuzzleState	&start,
	const NPuzzleState	&dest,
	Heuristic			heur
)
{
	std::cout << "Start greedy search" << std::endl;
	std::vector<NPuzzleState> path = AStar(
		start,
		dest,
		[](const NPuzzleState &s){ return s.genNeighbors(); },
		[](const NPuzzleState &s, const NPuzzleState &g){ (void)s; (void)g; return (0); },
		heur
	);
	std::cout << "Size du path : " << path.size() << std::endl;
	std::cout << std::endl;
	for (auto s : path)
		printNPuzzleState(s);
}

int	main(int ac, char **av)
{
	ParsingInfo	parsingInfo;
    Heuristic   heur;
	if (ac != 3)
	{
		std::cout << "args missing : ./nPuzzle [file] [heuristic]" << std::endl;
		return (1);
	}
	if (!parsing(av[1], parsingInfo))
	{
		std::cerr << "File not conform : " << av[1] << std::endl;
		return (1);
	}
	std::vector<int> finalGrid = genFinalGrid(parsingInfo.grid);
	NPuzzleState start{parsingInfo.grid, parsingInfo.size};
    start.size = std::sqrt(start.board.size());
	NPuzzleState dest{finalGrid, parsingInfo.size};
    dest.size = std::sqrt(dest.board.size());
	if (parity(start.board, start.size) != parity(dest.board, start.size))
	{
		std::cout << "Grid unsolvable" << std::endl;
		return (0);
	}

	printNPuzzleState(start);
	printNPuzzleState(dest);

	std::vector<int> pattern = {1, 2, 3, 4};
	std::unordered_set<int> patternSet(pattern.begin(), pattern.end());
	auto abstract = [patternSet](const NPuzzleState &s)
	{
		NPuzzleState copy = s;
		for (auto &tile : copy.board)
			if (!patternSet.contains(tile) && tile != 0)
				tile = -1;
 		return (copy);
	};

	auto neigh = [](const NPuzzleState &s)
	{
		return (s.genNeighbors());
	};

	std::shared_ptr<
    	PatternDatabase<NPuzzleState, decltype(abstract), decltype(neigh)>
	> pdb;
	
    std::string h(av[2]);
    if (h == "manhattan")
        heur = manhattan;
    else if (h == "linearConflict")
        heur = linearConflict;
	else if (h == "pdb")
	{
		pdb = std::make_shared<
        	PatternDatabase<NPuzzleState, decltype(abstract), decltype(neigh)>
    	>(pattern, dest, abstract, neigh);
		pdb->build();
		heur = [&pdb](const NPuzzleState& s, const NPuzzleState&)
		{
    		return pdb->getDistance(s);
		};
	}
    else
    {
        std::cerr << "Unknown heuristic" << std::endl;
        return (1);
    }

	startAStar(start, dest, heur);
	startGreedy(start, dest, heur);
	startUniform(start, dest);
	
	return (0);
}
