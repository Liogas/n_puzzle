/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 12:43:31 by glions            #+#    #+#             */
/*   Updated: 2026/02/20 13:10:16 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.hpp"
#include "nPuzzle.hpp"
#include "AStar.hpp"

#include <functional>

using Heuristic = std::function<
    int(const NPuzzleState &, const NPuzzleState &)
>;

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
    std::string h(av[2]);
    if (h == "manhattan")
        heur = manhattan;
    else if (h == "linearConflict")
        heur = linearConflict;
    else
    {
        std::cerr << "Unknown heuristic" << std::endl;
        return (1);
    }
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
	return (0);
}
