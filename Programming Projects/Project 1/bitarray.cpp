#include "bitarray.hpp"
#include <cstring>
#include <cmath>
#define size_of_element 8
/* 1 uint8_t = 8 bits, int ((N-1)/8 + 1)
the BitArray array is similar to a 2d array, with one axis being the byte position, and the other axis being the bit position */
BitArray::BitArray()
{
    // size is greater than 0, therefore valid
    valid_bitarray = true;

    // default size is 8
    size_bitarray = 8;

    intmax_t element_count = ((size_bitarray - 1) / size_of_element) + 1; // bit to byte

    // allocate dynamic memory
    array_bitarray = new uint8_t[element_count];

    memset(array_bitarray, 0, sizeof(*array_bitarray) * element_count); // from the cstring library, fills array with 0;
}

BitArray::BitArray(intmax_t size)
{
    if (size <= 0)
    {
        // N <=0 is invalid, if invalid don't bother with bitarray
        valid_bitarray = false;
    }
    else
    {
        valid_bitarray = true;
        size_bitarray = size;

        // bit to byte
        intmax_t element_count = ((size_bitarray - 1) / size_of_element) + 1;

        // allocate dynamic memory
        array_bitarray = new uint8_t[element_count];

        // from the cstring library, fills array with 0;
        memset(array_bitarray, 0, sizeof(*array_bitarray) * element_count);
    }
}

BitArray::BitArray(const std::string &value)
{

    // set valid initially
    valid_bitarray = true;
    size_bitarray = value.length();

    // bit to byte
    intmax_t element_count = ((size_bitarray - 1) / size_of_element) + 1;

    // allocate dynamic memory
    array_bitarray = new uint8_t[element_count];

    // from the cstring library, fills array with 0
    memset(array_bitarray, 0, sizeof(*array_bitarray) * element_count);

    // position of the array, the array is an array of bytes (8 bits)
    int byte_position = 0;
    for (int bit_position = 0; bit_position < size_bitarray; bit_position++)
    {
        // calculate the position relative to the bit position
        byte_position = bit_position / size_of_element;

        // convert from string char to int
        int zero_or_one = (value[bit_position] - '0');
        if (zero_or_one != 0 && zero_or_one != 1)
        {
            valid_bitarray = false;
            // skips it, leaving it at zero
            continue;
        }
        // Set the bit at the correct byte and bit position using shift and bitwise or
        array_bitarray[byte_position] |= (zero_or_one << (bit_position % size_of_element));
    }
}

BitArray::~BitArray()
{
    // deletes dynamically stored memory
    delete[] array_bitarray;
}

// method to get the size
intmax_t BitArray::size() const
{
    return size_bitarray;
}

// method to confirm is valid or invalid
bool BitArray::good() const
{
    return valid_bitarray;
}

// set value to 1 at index
void BitArray::set(intmax_t index)
{

    // converts length from bits to bytes
    intmax_t element_count = ((size() - 1) / size_of_element) + 1;
    if (index > size() - 1 || index < 0)
    {
        valid_bitarray = false;
    }
    int bit_position = index;
    int byte_position = bit_position / size_of_element; // bit to byte
    // Set the bit at the correct byte and bit position using shift and bitwise or
    array_bitarray[byte_position] |= (1 << (bit_position % size_of_element));
}

// set value to 0 at index
void BitArray::reset(intmax_t index)
{
    // converts length from bits to bytes
    intmax_t element_count = ((size() - 1) / size_of_element) + 1;
    if (index > size() - 1 || index < 0)
    {
        valid_bitarray = false;
    }
    int bit_position = index;
    // bit to byte
    int byte_position = bit_position / size_of_element;
    // invert and to insert a 0 at the correct position
    array_bitarray[byte_position] &= ~(1 << (bit_position % size_of_element));
}

// toggle the bit
void BitArray::toggle(intmax_t index)
{
    // converts length from bits to bytes
    intmax_t element_count = ((size() - 1) / size_of_element) + 1;
    if (index > size() - 1 || index < 0)
    {
        valid_bitarray = false;
    }
    int bit_position = index;
    // bit to byte
    int byte_position = bit_position / size_of_element;
    // Using xor to toggle
    array_bitarray[byte_position] ^= (1 << (bit_position % size_of_element));
}

// checking if 1 is present at index
bool BitArray::test(int index)
{
    // assume that its valid
    if (index > size() - 1 || index < 0)
    {
        valid_bitarray = false;
        return false;
    }
    int bit_position = index;
    // bit to byte
    int byte_position = bit_position / size_of_element;
    /* Using and to single out the bit position at said byte, and using comparison to confirm a number existed or is 0,
     ie checking position 1, with bitset set to 111, 111 & 010 = 010, number is returned as an int,
    reduced to a 1 or 0 using most significant bit */
    return (array_bitarray[byte_position] & (1 << (bit_position % size_of_element))) / pow(2, bit_position % size_of_element);
}

std::string BitArray::asString() const
{
    // assume this is valid
    std::string my_string;
    for (int i = 0; i < size(); i++)
    {
        // using same function as test to check if 0 or 1
        if ((array_bitarray[i / size_of_element] & (1 << (i % size_of_element))) / pow(2, i % size_of_element))
        {
            my_string += '1';
        }
        else
        {
            my_string += '0';
        }
    }
    return my_string;
}
