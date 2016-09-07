import data_abstract
import utils

def handle_input_command(controller, command, args):
    
    # Determine which command was requested and (attempt to) execute it
    if command == utils.ADD:
        # Reload the file if there have been changes
        controller.load_from_file()
        data_type = utils.convert_char_to_data_key(args[0])
        if data_type != "":
            data_info = args[1:]
            controller.add_item(data_type, data_info)
            controller.save_to_file()
        else:
            pass # Do nothing if an invalid type was supplied
    elif command == utils.LIST:
        # Reload the file if there have been changes
        controller.load_from_file()
        # There should be only one argument for list, but if there are multiple,
        # We only read the first one (No errors thrown, however)
        data_type = utils.convert_char_to_data_key(args[0])
        if data_type != "":
            controller.list_items(data_type)
        else:
            pass  # Do nothing if an invalid type was supplied
        
    elif command == utils.FLIGHT:
        # Reload the file if there have been changes
        controller.load_from_file()
        controller.search_for_flight(args[0:])

    elif command == utils.QUIT:
        return False  # Return False to end program execution
    
    elif command == utils.HELP:
        utils.print_help()
        
    else:
        # Invalid command entered; alert user
        print("Invalid command entered. Type 'h' for assistance")
        
    return True

def main():
    print("Loading data file...")
    controller = data_abstract.DataController()

    # Do an initial load of the data file
    controller.load_from_file()

    exit_flag = True

    while exit_flag:
        # Get the input from the user
        user_input = input().strip().split()

        command, args = (user_input[0], user_input[1:])
        exit_flag = handle_input_command(controller, command, args)
        
    print('Ending program execution...')
    
if __name__ == '__main__':
    # Load the main function
    main()

