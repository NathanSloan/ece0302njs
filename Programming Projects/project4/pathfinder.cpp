#include <cstdlib>
#include <iostream>
#include "lib/image.h"
#include "list.hpp"
#include "queue.hpp"

int main(int argc, char *argv[])
{
  // get input/output file names from command line arguments
  if (argc != 3)
  {
    std::cout << "Usage: pathfinder "
              << "<first_input_filename> <second_output_filename>\n"
              << std::endl;
    return EXIT_FAILURE;
  }

  std::string input_file = argv[1];
  std::string output_file = argv[2];

  // Read input image from file
  Image<Pixel> image = readFromFile(input_file);
  std::cout << "IMAGE READ" << std::endl;

  // find start point
  int height = image.height();
  int width = image.width();

  /*
  Coordinates are saved in an int between 0 - (width * height - 1)
  coord = xPos + yPos * width
  xPos = coord % width
  yPos = coord / width
  */
  int start;
  bool startFound = false;
  for (int h = 0; h < height; h++)
  {
    for (int w = 0; w < width; w++)
    {
      if (image(h, w) == RED)
      {
        if (!startFound)
        {
          startFound = true;
          start = w + h * width;
        }
        else
        {
          std::cout << "Multiple start points found" << std::endl;
          return EXIT_FAILURE;
        }
      }
      else if (image(h, w) != BLACK && image(h, w) != WHITE)
      {
        std::cout << "Unidentified color found" << std::endl;
        return EXIT_FAILURE;
      }
    }
  }

  if (!startFound)
  {
    std::cout << "No start point found" << std::endl;
    return EXIT_FAILURE;
  }

  // TODO: breadth-first search

  // holds queue of potential paths
  Queue<int, List<int>> search;

  // holds coordinates already visited
  bool visited[height * width];

  // mark start point as visited and add to queue
  int yPos = start / width;
  int xPos = start % width;
  visited[start] = true;
  search.enqueue(start);

  // holds directional behavior
  int paths[4] = {0, 0, 0, 0};

  // offset constants used to determine next moves
  int yOffsets[4] = {-1, 1, 0, 0};
  int xOffsets[4] = {0, 0, -1, 1};
  while (!search.isEmpty())
  {
    // save new position coordinates
    int position = search.peekFront();
    yPos = position / width;
    xPos = position % width;
    search.dequeue();

    // calculate next possible moves
    for (int i = 0; i < 4; i++)
    {
      int yPosNew = yPos + yOffsets[i];
      int xPosNew = xPos + xOffsets[i];

      if (xPosNew < 0 || xPosNew >= width || yPosNew < 0 || yPosNew >= height || image(yPosNew, xPosNew) == BLACK)
      {
        paths[i] = -1;
      }
      else
      {
        paths[i] = xPosNew + yPosNew * width;
      }
    }

    // iterate through moves
    for (int path : paths)
    {
      // remove invalid moves
      if (path == -1)
        continue;
      else
      {
        // add unvisited moves to path and mark as visited
        if (!visited[path])
          search.enqueue(path);
        visited[path] = true;
      }
    }

    // detect if solution found
    if (xPos == 0 || xPos == width - 1 || yPos == height - 1 || yPos == 0)
    {
      std::cout << "Solution Found" << std::endl;
      image(yPos, xPos) = GREEN;
      std::cout << yPos << " and " << xPos << std::endl;

      // Write solution image to file
      try
      {
        writeToFile(image, output_file);
      }
      catch (std::runtime_error &my_error)
      {
        std::cerr << "Error: failed to writeToFile()" << my_error.what() << std::endl;
        return EXIT_FAILURE;
      }
      return EXIT_SUCCESS;
    }
  }

  // TODO: Write solution image to file
  try
  {
    writeToFile(image, output_file);
  }
  catch (std::runtime_error &my_error)
  {
    std::cerr << "Error: failed to writeToFile()" << my_error.what() << std::endl;
    return EXIT_FAILURE;
  }
  std::cout << "No Solution Found" << std::endl;
  return EXIT_SUCCESS;
}
