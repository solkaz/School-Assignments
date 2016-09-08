import re

# Basic actions constants
ADD = 'a'
LIST = 'l'
FLIGHT = 'f'
QUIT = 'q'
HELP = 'h'

# Options for Add and List action constants
CITY = 'c'
AIRLINE = 'a'
# FLIGHT = 'f' # Defined above, but it is an option for Add/List as well

# Check if a string has digits with a regex
_digits = re.compile('\d')
def has_digits(string):
    return bool(_digits.search(string))

def is_valid_int(string):
    # Attempt to convert the str input into an int
    try:
        i = int(string)
        return True
    # ValueError is raised if str cannot be converted to a valid int
    except ValueError:
        print('Invalid integer type supplied')
        return False

def print_help():
    # Print a basic help menu
    print('commands\n' +
          '--------\n' +
          'a = add a new (c)ity, (a)irline, or (f)light\n'  +
          'l = list all (c)ities, (a)irlines or (f)lights\n' +
          'f = search for a flight\n'+
          'q = quit program execution\n' +
          'h = display this help text')

def convert_char_to_data_key(data_type_char):
    # Convert the char representation of the data type
    if data_type_char == CITY:
        return "CITIES"
    elif data_type_char == AIRLINE:
        return "AIRLINES"
    elif data_type_char == FLIGHT:
        return "FLIGHTS"
    else:
        print("Invalid data type supplied to list operation")
        return ""
    
def format_flight_info(flight_info):
    # Returns a formatted string with a flight's information, making it
    # suitable for printing
    return "{0}: {1} -> {2} ${3}".format(*flight_info)

def search_print_simple(flight_info):
    # To get the members of the flight object, we convert it to a str (which
    # will contain all data members) and then split it into a list
    flight_members = str(flight_info).split()
    return "{0} -> {1} : {2} ${3}".format(
        flight_members[1],  # Flights are the first two inserted
        flight_members[2],
        flight_members[0],  # Then airline
        flight_members[-1]  # Finally price
    )

def search_print_connecting(flight_pair):
    flight_one, flight_two = flight_pair

    # We need the "simple" formats of each individual flight
    # to compose the final product
    flight_infos = tuple(map(
        search_print_simple,
        flight_pair
    ))
    # Get the total price of the flight plan
    total_price = str(flight_one.price + flight_two.price)

    # Return the formatted flight info to be printed
    return "{0}; {1}, for a total cost of ${2}".format(
        *flight_infos,
        total_price
    )

# Create a dict with the given fields and args
# Useful in creating a data object from the keywords
def map_args_to_fields(fields, args):
    return dict(zip(fields, args))
