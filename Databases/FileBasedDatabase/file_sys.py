import json

from data_types import Airline, City, Flight
from attr import asdict

DATA_FILE_LOCATION = './data.json' # Location of where the data file should be

# Data is loaded from a dictionary of lists for listing and flight options
# instead of having to read the file each time
DATA_AS_DICT = {
    "CITIES": [],
    "AIRLINES": [],
    "FLIGHTS": []
}

# Basic actions constants
ADD = 'a'
LIST = 'l'
FLIGHT = 'f'

# Options for Add and List action constants
CITY = 'c'
AIRLINE = 'a'
# FLIGHT = 'f' # Defined above, but it is an option for Add/List as well

def ask_to_continue(question):
    # Ask the question and collect input from user
    response = input(question + ', continue [y/n]? ')
    has_valid_response = response == 'y' or response == 'n'
    while not has_valid_response:
        response = input('Please answer with "y" or "n"')
        has_valid_response = response == 'y' or response == 'n'

    return response == 'y'
        
def save_to_data_file():
    # Create a copy of DATA_AS_DICT, except the keys in DATA_AS_DICT map to lists of
    # dictionary representations of each object, which can be used to easily
    # create the objects again upon being loaded
    
    data_to_save = {}

    # Apply attrs.asdict to each section in DATA_AS_DICT to get map representations of each object
    for data_type in DATA_AS_DICT.keys():
        data_to_save[data_type] = list(map(asdict, DATA_AS_DICT[data_type]))
        
    # Save data to the data file
    with open(DATA_FILE_LOCATION, 'w', encoding='utf-8') as data_file:
        json.dump(data_to_save, data_file, ensure_ascii=False)


def load_data_file():
    try:
        with open(DATA_FILE_LOCATION) as data_file:
            # Attempt to load data_file; 
            try:
                read_data = data_file.read()
                data_from_file = json.loads(read_data)
            except ValueError: # 
                return ask_to_continue("Invalid JSON file format")
            
            for data_type in data_from_file:
                # Set the data type being read in
                if data_type == 'CITIES':
                    object_type = City
                elif data_type == 'AIRLINES':
                    object_type = Airline
                elif data_type == 'FLIGHTS':
                    object_type = Flight
                else: # Invalid data type
                    return False

                # Reset the list of objects that was
                DATA_AS_DICT[data_type].clear()
                
                # Attempt to create a new instance of data_type
                # 
                for data_object in data_from_file[data_type]:
                    new_object = validate_data(object_type, data_object)

                    # Check that the data was successfully validated
                    if new_object:
                        # Add the object to the dictionary
                        DATA_AS_DICT[data_type].append(new_object)
                    else: # Invalid data; ask to continue program execution
                        return ask_to_continue("Invalid data in data file (loading will cease execution)")
                
    except OSError: # File doesn't exist; ask to continue execution
        return ask_to_continue("No data file found")

    return True

def validate_data(object_type, args):
    new_obj = None
    try:
        new_obj = object_type(**args)
    except TypeError:
        print("Invalid data supplied to " + object_type.__name__)
        print("Arguments supplied: " + args)

    return new_obj        

def mapArgsToFields(fields, args):
    return dict(zip(fields, args))

def add_new(type_to_add, type_info):
    fields = args = object_type = key = None
    
    if type_to_add == CITY:
        fields = [
            'city_code',
            'full_name',
        ]
        args = [
            type_info[0],
            ' '.join(type_info[1:])
        ]
        object_type = City
        key = 'CITIES'
        
    elif type_to_add == AIRLINE:
        fields = [
            'abbreviation',
            'full_name',
        ]
        args = [
            type_info[0],
            ' '.join(type_info[1:])
        ]
        object_type = Airline
        key = 'AIRLINES'
        
    elif type_to_add == FLIGHT:
        fields = [
            'airline_code',
            'departure_airport_code',
            'arrival_airport_code',
            'price'         
        ]
        args = type_info[0:]
        # Python reads input as str's, thus we need to convert price to int
        args[-1] = int(args[-1])
        object_type = Flight
        key = 'FLIGHTS'
        if not flight_validation(args):
            print('Error: flight has information that has not been entered\n' +
                  'check that the information entered is correct and try again')
            return True
        
    else: # Invalid type to add;
        return False

    arguments_dict = mapArgsToFields(fields, args)
    # Ensure that the data entered has the valid types
    new_object = validate_data(object_type, arguments_dict)
    
    # Check that duplicate data isn't being added
    if new_object not in DATA_AS_DICT[key]:
        DATA_AS_DICT[key].append(new_object)
    else:
        print('Error: attempt to add duplicate data')

    return True

def duplicate_check(key, new_object):
    # For City and Airline objects, we check that there doesn't already exist a
    # respective object with the same code/abbreviation. There can be multiple
    # objects with the same full name, however
    type_collection = DATA_AS_DICT[key]
    if key == 'CITIES':
        city_codes = [x.city_code for x in type_collection[key]]
        return not new_object.city_code in city_codes
    elif key == 'AIRLINES':
        abbreviations = [x.abbreviation for x in type_collection[key]]
        return not new_object.abbreviation in abbreviations 
    else:
        # Only check that a flight with the same input doesn't exist already
        return new_object not in type_collection

def flight_validation(args):
    # Flight has fields that are dependent on Airline and City objects existing a priori
    # Thus, we have to check that the city and airlines entered exist
    verify_flight_input(args[0], args[1], args[2])

    

def verify_flight_input(airline_code, departure, arrival):
    airline_codes = [x.abbreviation for x in DATA_AS_DICT['AIRLINES']]
    city_codes = [x.city_code for x in DATA_AS_DICT['CITIES']]

    return (
        airline_code in airline_codes and
        departure in city_codes and
        arrival in city_codes
    )
    
    
def list_items(type_to_list):
    
    if not load_data_file():
        return False
    
    if type_to_list == CITY:
        key = 'CITIES'
    elif type_to_list == AIRLINE:
        key = 'AIRLINES'
    elif type_to_list == FLIGHT:
        key = 'FLIGHTS'
    else: # Invalid option; exit the program
        return False

    # Check that there are objects to list
    if len(DATA_AS_DICT[key]) == 0:
        print('No ' + key.lower() + ' found')
    else:
        for obj in DATA_AS_DICT[key]:
            print(str(obj))
    
    return True

def search_for_flight(command):
    pass
    
def process_line(operation_char, operation_specifiers):

    if operation_char == ADD: # Add operation
        # Determine what will be added to the data
        if add_new(operation_specifiers[0], operation_specifiers[1:]):
            # Save the file after the addition
            save_to_data_file()
            return True
        else:
            # Action was not successful
            return False
    elif operation_char == LIST: # List operation
        return list_items(operation_specifiers[0])
    elif operation_char == FLIGHT: # Flight operation
        search_for_flight(operation_specifiers[0], operation_specifiers[1:])
        return True
    else: # Exit the program on 'q' or on an illegal command
        return False


if __name__ == '__main__':

    # Attempt to load the data file, if there are errors, the user can choose to continue or end execution
    continue_execution = load_data_file()

    while continue_execution:
        line_inputted = input().strip().split()
        continue_execution = process_line(line_inputted[0], line_inputted[1:])

    print("exiting")
            
