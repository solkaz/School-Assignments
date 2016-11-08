#include "main.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

std::vector<int> GetParityBits(int word_length) {
    int num_parity_bits = static_cast<int>(std::log2(word_length));

    std::vector<int> parity_bits;
    for (int bit_num = 1; bit_num <= num_parity_bits; bit_num *= 2) {
	parity_bits.push_back(bit_num);
    }
    return parity_bits;
}

Word ReverseWord(Word word) {
    std::reverse(word.begin(), word.end());
    return word;
}

WordPair ReverseWordPair(WordPair word_pair) {
    return std::make_pair(ReverseWord(word_pair.first),
			  ReverseWord(word_pair.second));
}

WordPair MakeK_Words_Pair(WordPair IO_words, std::vector<int> parity_bits) {
    auto reverse_IO_words = ReverseWordPair(IO_words);

    for (int parity_bit = 0; parity_bit < parity_bits.size(); ++parity_bit) {
	int check_bit_value;
	for (int bit_pos = 0; bit_pos < WORD_LENGTH; ++bit_pos) {
	    if ()
	    
	    // Check that the current bit index is not a power of 2
	    if (IsPowerOfTwo(bit_pos)) {
		continue;
	    }
	    
	}
    }
}

Word MakeK_Word(Word IO_word) {
    
}

void PrintRecord(int record_num) {
    std::cout << "Record #" << record_num; 
}

int main() {

    WordPair IO_words;
    WordPair K_words;
    auto parity_bits = GetParityBits(WORD_LENGTH);
    for (const auto &i : parity_bits) {
	std::cout << i << ' ';
    } std::cout << std::endl;
    
    int record_num = 0;

    std::cin >> IO_words.first;

    while (IO_words.first != "-1") {
	
	std::cin >> IO_words.second;
	std::cout << IO_words.first << std::endl
		  << IO_words.second << std::endl;

	K_words = MakeK_Words_Pair(IO_words, parity_bits);

	// Increment the record number counter
	++record_num;
	// Read in the next word
	std::cin >> IO_words.first;
    }
    
    return 0;
}
