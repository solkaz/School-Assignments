import attr
import data_file
import data_types
import data_wrapper
import json
import utils

# Data is loaded from a dictionary of lists for listing and flight options
# instead of having to read the file each time

class DataController():
    data = attr.ib()
    data_file = attr.ib()

    def __init__(self):
        # Create new DataWrapper & DataFile instances when
        # DataController is initialized
        self.data = data_wrapper.DataWrapper()
        self.data_file = data_file.DataFile()

    def save_to_file(self):
        # Format the data to be suitable for saving to the data file
        save_data = self.data.prep_for_saving()
        # Dump the data into the data file
        self.data_file.save(save_data)

    def load_from_file(self):

        if not self.data_file.check_existence():
            print("Data file doesn't exist; aborting loading the data file")
            return

        # If the file hasn't been modified since the last time it was edited
        # then there isn't a reason to reload it
        if self.data_file.check_if_modified():
            # Attempt to load 
            data_from_file = self.data_file.load()
            
            try:
                loaded_data = json.loads(data_from_file)
            except ValueError:
                print('Invalid JSON format; aborting loading the data file')
                return
            
            # Clear the pre-existing list of the data type
            self.data.reset()            

            # 
            data_as_object = data_types.DataTypeFactory.create_from_file_data(loaded_data)

            # Replace the previous data with the loaded data
            self.data.update_data_as_dict(data_as_object)

            # Update the last_modified_time
            self.data_file.update_last_modified_time()
            

    def list_items(self, type_to_list):
        self.load_from_file()
        list_of_items = self.data.prep_for_list(type_to_list)
        if list_of_items:
            for item in list_of_items:
                print(item)
        else:
            print('No ' + type_to_list.lower() + ' were found.')

    def add_item(self, data_type, data_info):

        if data_type == 'FLIGHTS' and not self.data.flight_info_check(data_info[:-1]):
            print('foo')
            return
        
        # DataTypeFactory will handle validation of input data and return the
        # relevant object from the arguments
        # If invalid args were supplied, Nonetype will be returned
        new_object = data_types.DataTypeFactory.create_from_entry(data_type, data_info)

        if new_object:
            # Check that there isn't a duplicate object in the data
            if self.data.is_not_duplicate(data_type, new_object):
                self.data.add_item(data_type, new_object)
            else:
                print("Attempt to add a duplicate record")
        else: # Do nothing if invalid data was supplied
            pass

    def search_for_flight(self, args):
        
        # Both city codes need to have been predefined
        if not (self.data.is_predefined(args[0], "city_code", "CITIES") and
                self.data.is_predefined(args[1], "city_code", "CITIES")):
            # One of the codes is not defined; halt searching for flights
            print("One of the codes entered is not defined")
            return
        else:
            # The connections requested needs to be an int; check for that
            if not utils.is_valid_int(args[-1]):
                print("Number of connections needs to be an int")
                return
            else:
                # Convert the truth value of last arg ("Is a connection allowed?")
                # to bool
                connection_requested = bool(int(args[-1]))
                
                # Construct a tuple pair consisting of the two cities
                cities = tuple(args[:-1])

                # Use a different search method if a connection wsa requested
                if connection_requested:
                    flights_found = self.data.connecting_flight_search(cities)

                    # Check that there were flights found
                    if not flights_found:
                        print('No such flights found')
                    else:
                        flight_plans = []
                        # Prep the flights found for printing
                        for connected_flights in flights_found:
                            # Connected flights should be a tuple consisting of
                            # flights that share an intermediary city. This will
                            # create all possible flight plans
                            flight_product = list(itertools.product(*connected_flights))

                            # Append the products to the list of flights to print
                            flight_plans += flight_product

                        # Format all flight plans
                        formatted_flight_plans = list(map(
                            utils.search_print_connecting,
                            flight_plans
                        ))

                        for _ in formatted_flight_plans:
                            print(_)
                    
                else:
                    flights_found = self.data.simple_flight_search(cities)

                    # Check that there were flights found
                    if not flights_found:
                        print('No such flights found')
                    else:
                        print('foo')
                        # Prep the flights found for printing
                        formatted_flights = list(map(
                            utils.search_print_simple,
                            flights_found
                        ))

                        for _ in formatted_flights:
                            print(_)
