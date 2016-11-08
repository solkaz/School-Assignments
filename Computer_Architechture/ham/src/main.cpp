#include "print.hpp"
#include "utils.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>

// Length of the words is fixed to 16 for this assignment
constexpr int WORD_LENGTH = 16;

WordPair MakeK_WordsPair(WordPair, ParityBits);
Word MakeK_Word(Word, ParityBits);
Word MakeStorageWord(Word, Word);

int main() {

    WordPair IO_words; WordPair K_words;
    Word storage_word;
    auto parity_bits = GetParityBits(WORD_LENGTH);
    int record_num = 1;

    bool first = true;

    // Read the first word in
    std::cin >> IO_words.first;

    // Continue looping while sentinel hasn't been read
    while (IO_words.first != "-1") {
	// Print a section separator if not the first test case
	if (record_num != 1) {
	    std::cout << "\n\n\n\n\n\n\n" << std::endl;   
	}

	// Read the second word in
	std::cin >> IO_words.second;

	// Print the record # and the original input words
	PrintRecord(record_num);
	PrintInputs(IO_words);

	// Make the K words for each inputted word
	K_words = MakeK_WordsPair(IO_words, parity_bits);
	// Compute the word that was stored in memory
	storage_word = MakeStorageWord(IO_words.first, K_words.first);
	// Print the storage word and the K words
	PrintStorageWord(storage_word);
	PrintK_Words(K_words);
	// Print the status message of the operation
	PrintStatusMessage(K_words, storage_word);
	// Increment the record number counter
	++record_num;
	// Formatting for paper printing; add another blank line every even
	// record #
	if (record_num % 2 == 0) {
	    std::cout << std::endl;
	}
	// Read in the next word
	std::cin >> IO_words.first;
    }

    std::cout << "End of output" << std::endl;
    // Exit the program successfully
    return 0;
}

//************************* FUNCTION MakeK_WordsPair ***************************
WordPair MakeK_WordsPair(WordPair IO_words, ParityBits parity_bits) {
    /* Receives: The inputted Words and the generated parity bits for 
     *           the given word size
     * Task: Generate the K words for the input words
     * Returns: the pair of K words
     */

    // Words are little-endian so they are reversed in order to make
    // iteration easier
    auto reverse_IO_words = ReverseWordPair(IO_words);

    // Return the pair of newly-created K words
    return std::make_pair(MakeK_Word(reverse_IO_words.first, parity_bits),
			  MakeK_Word(reverse_IO_words.second, parity_bits));
}
//************************* END OF FUNCTION MakeK_WordsPair ********************

//************************* FUNCTION MakeK_Word ********************************
Word MakeK_Word(Word IO_word, ParityBits parity_bits) {
    /* Receives: A 16-bit word and the set of parity bits
     * Task: Generate the K word for the inputted IO word
     * Returns: the K word
     */

    Word k_word;

    // We'll need to iterate up to the sum of the sizes of the
    // inputted word and the K word (21)
    const int bit_iter_end = WORD_LENGTH + parity_bits.size();
    // # of parity values is the size of the K word;
    for (const auto &parity_bit : parity_bits) {
	// Value of the parity bit that is part of this K word
	// Will default to the first value checked but is then XORed
	// on other values
	int check_bit_value;
	// Index position in the inputted word
	int data_bit_iter = 0;
	bool first = true;
	// Iterate over the inputted word
	for (int bit_index = 1; bit_index <= bit_iter_end; ++bit_index) {
	    // Check that the current bit index is a parity bit index
	    // i.e. is a power of two; skip this index if it is
	    if (IsPowerOfTwo(bit_index)) {
		continue;
	    }

	    // Check that the current bit index is within this parity bit's
	    // set	    
	    if (IsInParitySet(parity_bit, bit_index)) {
		// Get the bit as an int
		int bit = IO_word[data_bit_iter] - '0';
		// If this is the first bit to to be checked, then make it the
		// check bit's value
		if (first) {
		    check_bit_value = bit;
		    first = false;
		} else {
		    // Else XOR the check bit's value with the current data bit
		    check_bit_value ^= bit;
		}
	    }
	    // Increment the data bits iterator regardless of if bit_index
	    // was in the parity set
	    ++data_bit_iter;
	}
	// Make the new bit to the k word and append it
	char check_bit_char = check_bit_value + '0';
	k_word.push_back(check_bit_char);
    }

    // Reverse the k word make it in proper order and return it
    std::reverse(k_word.begin(), k_word.end());
    return k_word;
}
//************************* END OF FUNCTION MakeK_Word *************************

//************************* FUNCTION MakeStorageWord ***************************
Word MakeStorageWord(Word input_word, Word k_word) {
    /* Receives: The word to be stored and its K word
     * Task: Generate the word that will be stored in memory
     * Returns: the word
     */

    // Final storage word
    int storage_word_size = input_word.size() + k_word.size();
    Word storage_word(storage_word_size, ' ');

    // Iterators for the input/k words
    auto input_word_iter = input_word.crbegin();
    auto k_word_iter = k_word.crbegin();

    // Add a parity bit if the index is a power of 2; else add a data bit
    for (int i = 0; i <= storage_word_size; ++i) {
	// Check that the index is a power of 2
	if (IsPowerOfTwo(i + 1)) {
	    // Add a parity bit and increment the iterator
	    storage_word[i] = *(k_word_iter++);
	} else {
	    // Add a data bit and increment its iterator
	    storage_word[i] = *(input_word_iter++);
	}
    }
    // The storage word is in reverse order; reverse it and then return it
    std::reverse(storage_word.begin(), storage_word.end());
    return storage_word;
}
//************************* END OF FUNCTION MakeStorageWord ********************
