#include "utils.hpp"

#include <algorithm>
#include <bitset>

//************************* FUNCTION GetParityBits *****************************
std::vector<int> GetParityBits(int word_length) {
    /* Receives: length of the word
     * Task: generate the 2^n parity values
     * Returns: the list of the values
     */
    // Return a vector of the indices that are powers of two
    std::vector<int> parity_bits;
    for (int bit_num = 1; bit_num <= word_length; bit_num *= 2) {
	// Add the index to the back of the vector
	parity_bits.push_back(bit_num);
    }
    return parity_bits;
}
//************************* END OF FUNCTION GetParityBits **********************

//************************* FUNCTION ReverseWord *******************************
Word ReverseWord(Word word) {
    /* Receives: A word
     * Task: reverse it
     * Returns: the reverse word
     */
    // Reverse the inputted word and return it
    std::reverse(word.begin(), word.end());
    return word;
}
//************************* END OF FUNCTION ReverseWord ************************

//************************* FUNCTION ReverseWordPair ***************************
WordPair ReverseWordPair(WordPair word_pair) {
    /*
     * Receives: a pair of Words
     * Task: Reverse each word
     * Returns: the pair of the reversed words
     */
    
    return std::make_pair(ReverseWord(word_pair.first),
			  ReverseWord(word_pair.second));
}
//************************* END OF FUNCTION ReverseWordPair ********************

//************************* FUNCTION IsPowerOfTwo ******************************
bool IsPowerOfTwo(int x) {
    /* Receives: an int
     * Task: check if it is a power of two
     * Returns: the result of the task
     */
    // Check if x is a power of 2
    return (x & (x - 1)) == 0;
}
//************************* END OF FUNCTION IsPowerOfTwo ***********************

//************************* FUNCTION MakeK_WordsPair ************************###
bool IsInParitySet(int parity_num, int data_index) {
    /* Receives: the current parity number (2^n) an
     * Task: Check if the 
     * Returns: result of the task
     */
    // An int is within a parity num's set if the bitwise AND is != 0
    return (parity_num & data_index) != 0;
}
//************************* END OF FUNCTION MakeK_WordsPair ********************

//************************* FUNCTION MakeBinaryString **************************
Word MakeBinaryString(int value) {
    /* Receives: integer value
     * Task: convert it to a std::string that is the binary repr of the input
     * Returns: the 5-bit string
     */
    return std::bitset<5>(value).to_string();
}
//************************* END OF FUNCTION MakeBinaryString *******************

//************************* FUNCTION FinalSyndromeValue ************************
int FinalSyndromeValue(WordPair K_words) {
    /* Receives: The pair of k words
     * Task: Return the bitwise XOR of their values
     * Returns: The XOR of the k words (as an int)
     */
    return (std::stoi(K_words.first, 0, 2) ^
	    std::stoi(K_words.second, 0, 2));
}
//************************* END OF FUNCTION FinalSyndromeValue *****************
