import re

# Basic actions constants
ADD = 'a'
LIST = 'l'
FLIGHT = 'f'
QUIT = 'q'
HELP = 'p'

# Options for Add and List action constants
CITY = 'c'
AIRLINE = 'a'
# FLIGHT = 'f' # Defined above, but it is an option for Add/List as well

def ask_to_continue(question):
    # Ask the question and collect input from user
    response = input(question + ', continue [y/n]? ')
    has_valid_response = response in ['y', 'n']
    while not has_valid_response:
        response = input('Please answer with "y" or "n"')
        has_valid_response = response in ['y', 'n']

    return response == 'y'

_digits = re.compile('\d')
def has_digits(string):
    return bool(_digits.search(string))

def is_valid_int(string):
    # Attempt to convert the str input into an int
    try:
        i = int(string)
        return True
    # 
    except ValueError:
        print('Invalid integer type supplied')
        return False

def print_help():
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
