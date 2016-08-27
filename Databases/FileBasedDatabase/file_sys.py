import attr
import json

data_file = './data.json' # Location of where the data file should be

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
# FLIGHT = 'f' # Already entered above so it'll be reused

@attr.s
class City():
    city_code = attr.ib()
    full_name = attr.ib()

    def __str__(self):
        print(city_code, full_name)

@attr.s
class Airline():
    abbreviation = attr.ib()
    full_name = attr.ib()

    def __str__(self):
        print(abbreviation, full_name)
    
@attr.s
class Flight():
    airline_code = attr.ib()
    departure_airport_code = attr.ib()
    arrival_airport_code = attr.ib()
    price = attr.ib()

    def __str__(self):
        print(airline_code, departure_airport_code, arrival_airport_code, price)

def main():
    with open(data_file) as data:
        pass

def add_new(command):
    data_to_add = command[0]
    if 

def process_line(command):

    op_char = command[0]
    
    if op_char is ADD: # Add operation
        # Determine what will be added to the data
        add_new(command[1:])
        
        if data_to_add is CITY:
            new_city_info = {
                'city_code': command[3],
                'full_name': command[4:].join(' ')
            }
            new_city_obj(**new_city_info)
            pass
        elif data_to_add is AIRLINE:
            new_airline_info = {
                'abbreviation': command[3],
                'full_name': command[4:].join(' ')
            }
            new_airline_obj = Airline(**new_airline_info)
            pass
        elif data_to_add is FLIGHT:
            new_flight_info = {
                'airline_code' : command[2],
                'departure_airport_code' : command[3],
                'arrival_airport_code' : command[4],
                'price' : command[5]
            }
            new_flight_obj = Flight(**new_flight_info)
            
            pass
        else:
            return False

        # Save the file after the addition
        return False
    elif op_char is LIST: # List operation
        
        data_to_add = command[1]
        if data_to_add is CITY:
            # List all cities
            for city in DATA_AS_DICT['CITIES']:
                pass
            pass
        elif data_to_add is AIRLINE:
            # List all airlines
            for city in DATA_AS_DICT['AIRLINES']:
                pass
            pass
        elif data_to_add is FLIGHT:
            # List all flights
            for city in DATA_AS_DICT['FLIGHTS']:
                pass
            pass
        else: # Invalid option; exit the program
            return True
        return False
    elif op_char is FLIGHT: # Flight operation
        
        return False
    else: # Exit the program on 'q' or on an illegal command
        return True
    
if __name__ == '__main__':
    continue_execution = True
    while continue_execution:
        continue_execution = process_commands(input().strip().split()):
            
            
