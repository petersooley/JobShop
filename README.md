
### Problem
Given a set of Jobs where each job has a sequence of operations and each operation has a target machine and set duration, we need to find a schedule that assignes operations to machines in an optimal way that reduces the overall time to run all operations.

### Implementation
Unlike my homework assignments, I used as little overhead as possible. There's hardly any pointer shuffling. This lead to a much more simple and understandable algorithm. And since the program doesn't rely as much on structure as it does on values, there isn't as much of a limitation on implementing optimizations.

Like the tent arrangement problem, I used a similar tactic of "do/undo." I assign operations all the way down the tree. Once I hit bottom, I just undo assignments until I get to a new schedule. This way, I only ever have at most one complete schedule in memory at a time.

### Optimizations
The first and most obvious heuristic I found was to prune the tree as soon as our running score was worse than the best score we've found so far. This meant I had to keep a running score instead of just calculating it at the bottom of the tree.

The second optimization involved keeping track of times where machines would sit idle. Worse solutions would naturally have higher overall idle times. I would just prune the tree whenever a working solution had an idle time greater than the idle time of our best solution so far.

These optimizations are just heuristics and there are still other strategies that might have a greater impact.
