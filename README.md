# Mastermind
The game "Mastermind" is a two-player codebreaking game. The minimax algorithm provides a solution with good worst-case run time, while the genetic algorithm can be faster on average. My minimax algorithm is complete; the genetic algorithm is not!

# minimax_mastermind
Uses the minimax algorithm to solve the game. In each round, guess the configuration which optimizes the worst-case amount of information gained by a guess.

# genetic_mastermind
The (extremely fascinating) "genetic algorithm" seeks to maximze a function over a very large domain. It works by comparing the domain to a space of possible genes,
and the function to genetic "fitness". In each generation, fitness is probed for various genes, and then new a new generation of genes is produced by letting 
old genes reproduce and mutate (which amounts to taking new points in the domain which are somehow geometrically derived from the previous generation's points,
perhaps with some random variation). I began to try to apply this idea to solve the game, but have not yet finished the code!
