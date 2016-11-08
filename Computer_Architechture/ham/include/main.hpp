#ifndef MAIN_HPP_
#define MAIN_HPP_

#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

constexpr int WORD_LENGTH = 16;

using Word = std::string;
using WordPair = std::pair<Word, Word>;

std::vector<int> GetParityBits(int);
Word ReverseWord(Word);
WordPair ReverseWordPair(WordPair);
WordPair MakeK_Words_Pair(WordPair, std::vector<int>);
Word MakeK_Word(Word);
void PrintRecord(int);

bool IsPowerOfTwo(int x) {
    return (x & (x - 1)) == 0;
}

#endif // MAIN_HPP_
