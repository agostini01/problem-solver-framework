#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <algorithm> // for std::copy

int main()
{
  std::ifstream is("N4W4B3R9.txt");
  std::istream_iterator<unsigned int> start(is), end;
  std::vector<unsigned int> numbers(start, end);
  std::cout << "Read " << numbers.size() << " numbers" << std::endl;

  // print the numbers to stdout
  std::cout << "numbers read in:\n";
  std::copy(numbers.begin(), numbers.end(), 
            std::ostream_iterator<unsigned int>(std::cout, " "));
  std::cout << std::endl;

}
