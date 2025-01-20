#ifndef BITARRAY_HPP
#define BITARRAY_HPP
#include <stdint.h>
#include <stdlib.h>
#include <string>

class Bitarray
{
public:
  // default constructor
  Bitarray();

  // constructor with size input
  Bitarray(intmax_t size);

  // consntructor with string input
  Bitarray(const std::string &value);

  // default destructor to delete any dynamic memory
  ~Bitarray();

  Bitarray(const Bitarray &) = delete;
  Bitarray &operator=(const Bitarray &) = delete;

  // method to get the size
  intmax_t size() const;

  // method to confirm is valid or invalid
  bool good() const;

  // set value to 1 at index
  void set(intmax_t index);

  // set value to 0 at index
  void reset(intmax_t index);

  // toggle the bit
  void toggle(intmax_t index);

  // checking if 1 is present at index
  bool test(int index);

  // TODO COMMENT
  std::string asString() const;

private:
  uint8_t *array_bitarray; // the bitarray array
  intmax_t size_bitarray;  // size of bitarray
  bool valid_bitarray;     // check if valid
};

#endif
