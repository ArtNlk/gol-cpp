# gol-cpp
Game of life implementation

## Usage
Executable takes following parameters:
  1. Board row count
  2. Board column count
  3. Thread count. If <1 it is set automatically
  4. Steps count: how many steps to simulate
  5. Cellular automaton [rule string](https://www.conwaylife.com/wiki/Rulestring)
  6. RNG seed
  7. Delay between frames ms
  9. Initial population density 0.0 - 1.0
## Example
`Main.exe 50 50 10 10000 B3/S23 2 20 0.5`
Launches 50x50 game of life on 10 threads with ~50% of cells alive at the start, running for 10000 steps
where dead cells with 3 neighbors become alive, and only cells with 2 or 3 neighbors survive.
RNG is initialized with seed `2`, and program waits for 20 ms after each frame, resulting in about 50 FPS
### Additional info
Due to cout console output, a delay of at least 1 is recommended for stable visuals
