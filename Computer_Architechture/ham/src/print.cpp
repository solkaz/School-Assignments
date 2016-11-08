#include "print.hpp"
#include "utils.hpp"

#include <iostream>

// Various print functions

//************************* FUNCTION PrintRecord ************************
void PrintRecord(int record_num) {
    /* Receives: record number 
     * Task: Print the record #
     * Returns: void
     */
    std::cout << "Record #" << record_num << '\t';
}
//************************* END OF FUNCTION PrintRecord *****************

//************************* FUNCTION PrintInputs ************************
void PrintInputs(WordPair &IO_words) {
    /* Receives: The inputted words
     * Task: Print them out
     * Returns: void
     */
    std::cout << "Original input words:\n"
	      << "\t\t---------------------\n"
	      << "\t\t" << IO_words.first << std::endl
	      << "\t\t" << IO_words.second << std::endl << std::endl;
}
//************************* END OF FUNCTION PrintInputs *****************

//************************* FUNCTION PrintStorageWord ************************
void PrintStorageWord(Word &storage_word) {
    /* Receives: The storage word 
     * Task: Print it out
     * Returns: void
     */
    std::cout << "\t\tThe input word was stored as:\n"
	      << "\t\t-----------------------------\n"
	      << "\t\t" << storage_word << std::endl << std::endl;
}
//************************* END OF FUNCTION PrintStorageWord *****************

//************************* FUNCTION PrintComparison ************************
void PrintComparison(Word &final_syndrome) {
    /* Receives: The comparison word
     * Task: Print it out
     * Returns: void
     */
    std::cout << "\t\tSyndrome word comparison:\n"
	      << "\t\t-------------------------\n"
	      << "\t\t" << final_syndrome << std::endl << std::endl;
}
//************************* END OF FUNCTION PrintComparison *****************

//************************* FUNCTION PrintSeparator ************************
void PrintSeparator() {
    /* Receives: The K words 
     * Task: Print the K words
     * Returns: void
     */
    // Print a separator out
    std::cout << std::string(30, '*') << std::endl << std::endl;
}
//************************* END OF FUNCTION PrintSeparator *****************

//************************* FUNCTION PrintK_Words ************************
void PrintK_Words(WordPair K_words) {
    /* Receives: The K words 
     * Task: Print the K words
     * Returns: void
     */
    std::cout << "\t\tThe two syndrome code words are:\n"
	      << "\t\t--------------------------------\n"
	      << "\t\tK-bit code written into memory: " << K_words.first << '\n'
	      << "\t\tK-bit code read from memory: " << K_words.second << "\n\n";
}
//************************* END OF FUNCTION PrintK_Words *****************

//************************* FUNCTION PrintStatusMessage ************************
void PrintStatusMessage(WordPair K_words, Word storage_word) {
    /* Receives: The K words and the storage word
     * Task: Print the status message out
     * Returns: void
     */

    // Calculate the final syndrome word's value as an int
    auto final_syn_int = FinalSyndromeValue(K_words);
    auto final_syn_str = MakeBinaryString(final_syn_int);

    PrintComparison(final_syn_str);

    if (final_syn_int == 0) {
	// No error in the code
	std::cout << "\t\tA comparison of the syndrome words indicates that\n"
		  << "\t\tthe word read from memory is correct." << std::endl;
    } else if (IsPowerOfTwo(final_syn_int)) {
	// Error in the check bit
	std::cout << "\t\tThe syndrome word indicates that a check bit is in error.\n"
		  << "\t\tNo correction to the data is necessary." << std::endl;    
    } else if (final_syn_int > 21) {
	// Value of the syndrome word is too large
	std::cout << "\t\tThe value of the syndrome word indicates that the error\n"
		  << "\t\tcannot be corrected. Output data is unreliable." << std::endl;
    } else {
	// Prin the position of the bit in error
	int bit = storage_word[21 - final_syn_int] - '0';
	int inverted = (bit ? 0 : 1);
	
	std::cout << "\t\tThe syndrome word indicates that the bit in position "
		  << final_syn_int << " of the word" << std::endl
		  << "\t\tread from memory is in error. It was as a " << bit
		  << " and must be inverted to a " << inverted << std::endl;
    }
    std::cout << std::endl;
    PrintSeparator();
}
//************************* END OF FUNCTION PrintStatusMessage *****************
