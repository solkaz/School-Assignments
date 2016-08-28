import json

from .data_types import Airline, City, Flight

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

def save_to_data_file():
    # Create a copy of DATA_AS_DICT, except the keys in DATA_AS_DICT map to lists of
    # dictionary representations of each object, which can be used to easily
    # create the objects again upon being loaded
    data_to_save = {}
    for data_type in DATA_AS_DICT.keys():
        data_to_save[data_type] = map(attrs.asdict, DATA_AS_DICT[data_type])
    with open(DATA_FILE_LOCATION, 'w') as data_file:
        json.dump(data_to_save, data_file, ensure_ascii=False)

        
def load_data_file():
    try:
        with open(DATA_FILE_LOCATION) as data_file:
            # Load data from data_file

            data_from_file = json.loads(data_file.read())
            
            for data_type in data_from_file:
                # Set the data type being read in
                if data_type is 'CITIES':
                    object_type = City
                    pass
                elif data_type is 'AIRLINES':
                    object_type = Airline
                    pass
                elif data_type is 'FLIGHTS':
                    object_type = Flight
                    pass
                else: # Invalid data type
                    break

                # Attempt to create a new instance of data_type
                # 
                for data_object in data_type:
                    new_object = validate_data(object_type, data_object)

                    # Check that the data was successfully validated
                    if new_object:
                        # Add the object to the dictionary
                        DATA_AS_DICT[data_type].append(new_object)
                    else: # Invalid data; continue execution, but do not attempt to add that data
                        pass
                
    except OSError: # File doesn't exist; do nothing
        print("No data file found")

def validate_data(object_type, args):
    new_obj = None
    try:
        # Flight expects an int for the price member, but Python reads input as strs,
        # thus we have to convert price to an int quickly
        if object_type is Flight:
            args['price'] = int(args['price'])
            
        new_obj = object_type(**args)
    except TypeError:
        print("Invalid data supplied to " + object_type.__name__)
        print("Arguments supplied: " + args)

    return new_obj        

def mapArgsToFields(fields, args):
    return dict(zip(fields, args))

def add_new(command):
    type_to_add = command[0]

    fields = args = object_type = key = None
    
    if type_to_add is CITY:
        fields = [
            'city_code',
            'full_name',
        ]
        args = [
            command[3],
            ' '.join(command[4:])
        ]
        object_type = City
        key = 'CITIES'
        
    elif type_to_add is AIRLINE:
        fields = [
            'abbreviation',
            'full_name',
        ]
        args = [
            command[3],
            ' '.join(command[4:])
        ]
        object_type = Airline
        key = 'AIRLINES'
        
    elif type_to_add is FLIGHT:
        fields = [
            'airline_code',
            'departure_airport_code',
            'arrival_airport_code',
            'price'         
        ]
        args = command[2:]
        # Price needs to be an int; Python reads input as str. Thus we need to convert it
        args[-1] = int(args[-1])
        object_type = Flight
        key = 'FLIGHTS'
        
    else: # Invalid type to add; 
        return False

    arguments_dict = mapArgsToFields(fields, args)
    # Ensure that the 
    new_object = validate_data(object_type, arguments_dict)
    
    # Check that duplicate data isn't being added
    if new_object not in DATA_AS_DICT[key]:
        DATA_AS_DICT[key].append(new_object)
    else:
        print('Error: attempt to add duplicate data')
    
def list_items(command):
    type_to_list = command[0]
    
    if type_to_list is CITY:
        key = 'CITIES'
    elif type_to_list is AIRLINE:
        key = 'AIRLINES'
    elif type_to_list is FLIGHT:
        key = 'FLIGHTS'
    else: # Invalid option; exit the program
        return True

    for obj in DATA_AS_DICT[key]:
        print(str(obj))
    
    return False

def search_for_flight(command):
    pass
    
def process_line(command):

    op_char = command[0]
    
    if op_char is ADD: # Add operation
        # Determine what will be added to the data
        if add_new(command[1:]):
            # Save the file after the addition
            save_to_data_file()
        else:
            # Action was not sucecssful
            return False
    elif op_char is LIST: # List operation
        list_items(command[1:])
        
    elif op_char is FLIGHT: # Flight operation
        search_for_flight(command[1:])
        return False
    else: # Exit the program on 'q' or on an illegal command
        return True
    
if __name__ == '__main__':

    # load the data file first
    load_data_file()
    continue_execution = True
    while continue_execution:
        continue_execution = process_line(input().strip().split()):
            
            
