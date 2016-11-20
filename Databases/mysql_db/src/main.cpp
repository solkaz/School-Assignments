#include "connector.hpp"


int main() {

    Connector db_connector;

    // Get connection data from the user
    db_connector.GetConnectionData();

    // Attempt to connect to the DB; exit if it's unable to
    try {
	db_connector.ConnectToDB();
    } catch (const & std::runtime_error &err) {
	std::cerr << err.what() << std::endl;
	return 2;
    }

    bool cont_exec = true;
    std::string input_line;
    
    while (cont_exec) {
	// Don't read blank lines in
	do {
	    // Read the entire line as a string
	    std::cin.get_line(input_line);
	} while (input_line == "");

	// Split the line into separate words
	auto input_args = SplitInput(input_line);

	// Check if q was entered; exit the program if so
	// else process the input
	if (!input_args[0] == "q") {
	    ProcessInput(input_args);
	} else {
	    cont_exec = false;
	}
    }
    
    return 0;
}

