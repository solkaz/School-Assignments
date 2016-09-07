import json

from attr import asdict
from data_abstract import DataFile, DATA_AS_DICT
from data_types import Airline, City, Flight
from utils import *

def validate_data(object_type, args):
    new_obj = None
    try:
        new_obj = object_type(**args)
    except TypeError:
        print("Invalid data supplied to " + object_type.__name__)
        print("Arguments supplied: " + args)

    return new_obj

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
    if duplicate_check(key, new_object):
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
