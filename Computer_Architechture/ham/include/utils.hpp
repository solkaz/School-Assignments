#ifndef UTILS_HPP_
#define UTILS_HPP_

#include "types.hpp"

std::vector<int> GetParityBits(int);
Word ReverseWord(Word);
WordPair ReverseWordPair(WordPair);
bool IsPowerOfTwo(int);
bool IsInParitySet(int, int);
int FinalSyndromeValue(WordPair);
Word MakeBinaryString(int);

#endif // UTILS_HPP_
