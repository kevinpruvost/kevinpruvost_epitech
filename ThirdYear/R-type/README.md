# R-Type

## Description

The R-Type project is a "shoot them up" game, playable on networks, based on the original game design of the [R-Type] game, released in 1987, it also has to be usable on both Windows and Linux OS.

For the game engine part, we chose to make a dynamic ECS architecture. As it was dynamic, we could add new classes and objects by loading dynamic libraries at runtime (*.dll or *.so).

We use [Conan], as it is a cross-platform package manager for C++ projects.

We also implemented [Google Test] & [Google Benchmark] for testing and optimizing purposes.

## Diagram

<image src="https://github.com/kevinpruvost/kevinpruvost_epitech/blob/master/ThirdYear/R-type/doc/R-Type%20UML%20Class%20Diagram%20.png">

[Google Test]: https://github.com/google/googletest
[Google Benchmark]: https://github.com/google/benchmark
[R-Type]: https://fr.wikipedia.org/wiki/R-Type
[Conan]: https://conan.io/
