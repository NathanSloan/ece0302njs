g++ -std=c++17 -o pathfinder pathfinder.cpp lib/image.cpp
if ($?) {
  ./pathfinder tests/maze03.png output/maze03output.png
}

# .\run.ps1
