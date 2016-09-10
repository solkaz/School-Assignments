import attr
import utils

class DataWrapper():
    data_as_dict = {
        "CITIES": [],
        "AIRLINES": [],
        "FLIGHTS": []
    }

    # Allow for use of [] with DataWrapper
    def __getitem__(self, key):
        return self.data_as_dict[key]

    # Replace data_as_dict with a new set of data
    def update_data_as_dict(self, new_data):
        self.data_as_dict = new_data

    # Return the keys of data_as_dict
    def keys(self):
        return self.data_as_dict.keys()

    # Add an item to data_as_dict
    def add_item(self, data_type, new_object):
        self.data_as_dict[data_type].append(new_object)

    # Given the code and type of object, get the object's full name 
    def get_full_name(self, code, field_name, data_key):
        data_objects = self.data_as_dict[data_key]
        
        for obj in data_objects:
            if getattr(obj, field_name) == code:
                return getattr(obj, 'full_name')

    def is_predefined(self, code, field_name, data_key):
        # Check that the given code/abbreviation is predefined
        type_collection = self.data_as_dict[data_key]
        codes = [ getattr(obj, field_name) for obj in type_collection ]
        return code in codes

    def flight_info_check(self, args):
        # Check that the airline abbreviation and both city codes are defined
        # as they're necessary for listing a flight
        return (
            self.is_predefined(args[0], 'abbreviation', 'AIRLINES') and
            self.is_predefined(args[1], 'city_code', 'CITIES') and
            self.is_predefined(args[2], 'city_code', 'CITIES')
        )

    def is_not_duplicate(self, data_key, new_object):

        # For City and Airline objects, we can check if the code/abbreviation is
        # predefined; if it is, then it is a duplicate
        # Note that multiple objects of either type can have the same full name,
        # but there can't be a shared code/abbreviation between them
        if data_key == "CITIES":
            return not self.is_predefined(
                new_object.city_code,
                'city_code',
                data_key,
            )
        elif data_key == "AIRLINES":
            return not self.is_predefined(
                new_object.abbreviation,
                'abbreviation',
                data_key,
            )
        else:
            # For a Flight, it is a duplicate if there is already an object
            # with the exact same data.
            return not new_object in self.data_as_dict[data_key]

    # Clear a list from data_as_dict, specified by the data key
    def clear(self, data_key):
        self.data_as_dict[data_key].clear()

    # Clear ALL lists from data_as_dict
    def reset(self):
        for data_key in self.keys():
            self.clear(data_key)

    # Search for a flight WITH a connection
    def connecting_flight_search(self, cities):
        # Get all flights
        all_flights = self.data_as_dict['FLIGHTS']

        # List of flights that match input; will be returned at end
        matching_flights = []

        # Get all flights that have the inputted departure city
        departing_flights = list(filter(
            lambda flight_obj: flight_obj.departure_airport_code == cities[0],
            all_flights
        ))
        # Get all flights that have the inputted arrival city
        arriving_flights = list(filter(
            lambda flight_obj: (
                flight_obj.arrival_airport_code == cities[1] and
                # Make sure that direct flights to dest. city are not included
                flight_obj.departure_airport_code != cities[0]
            ),
            all_flights
        ))

        '''
        Create a list of the intermediary cities by finding the intersection
        between the sets of the first flight's destination city and the second
        flight's departure city. 
        '''
        flight_one_arrival = [
            flight.arrival_airport_code for flight in departing_flights
        ]

        flight_two_departure = [
            flight.departure_airport_code for flight in arriving_flights
        ]
        
        intermediary_cities = list(
            set(flight_one_arrival).intersection(flight_two_departure)
        )
        # Iterate through all intermediary cities
        for city in intermediary_cities:
            # Construct list of flights from departure city to an intermediary city
            leg_one_flights = [
                flight for flight in departing_flights if flight.arrival_airport_code == city
            ]
            
            # Next get list of flights from intermediary to destination city
            leg_two_flights = list(filter(
                lambda flight_obj: flight_obj.departure_airport_code == city,
                arriving_flights
            ))

            # Create a tuple pair consisting of the first/second leg flights
            # that share a common intermediary city
            matching_flight_plan = (leg_one_flights, leg_two_flights)
            matching_flights.append(matching_flight_plan)
        # Return the list of matched flights
        return matching_flights

    def simple_flight_search(self, cities):
        all_flights = self.data_as_dict['FLIGHTS']
        # Filter out flights that don't have the specified departure city coden 
        departing_flights = list(filter(
            lambda flight_obj: flight_obj.departure_airport_code == cities[0],
            all_flights
        ))

        # From flights_from_departure, get all flights that are arriving in
        # the inputted arrival city
        matching_flights = list(filter(
            lambda flight_obj: flight_obj.arrival_airport_code == cities[1],
            departing_flights
        ))

        return matching_flights
    
    def prep_for_list(self, data_type):
        if data_type != 'FLIGHTS':
            # For City and Airline objects, we return a list of their str
            # representations
            return [ str(obj) for obj in self.data_as_dict[data_type] ]
                        
        else:
            all_flights = self.data_as_dict[data_type]
            formatted_flights = []
            # Flight needs to the full names of the airlines, which it can't
            # The attributes of the flights are passed back as a conjoined string
            # (separated by spaces), which are then split to create a list of the data
            flight_data = [
                (str(flight)).split() for flight in all_flights
            ]
            for _ in flight_data:
                # We need the full names for the airline and the cities
                full_flight_data = [
                    self.get_full_name(_[0], 'abbreviation', 'AIRLINES'),
                    self.get_full_name(_[1], 'city_code', 'CITIES'),
                    self.get_full_name(_[2], 'city_code', 'CITIES'),
                    _[-1]
                ]
                formatted_flights.append(utils.format_flight_info(full_flight_data))

            # Return the list of formatted strings for each flight's info
            return formatted_flights
        
    def prep_for_saving(self):
        # Create a copy of DATA_AS_DICT, except the keys in DATA_AS_DICT map to lists of
        # dictionary representations of each object, which can be used to easily
        # create the objects again upon being loaded

        data_to_save = {}        
        # Apply attrs.asdict to each section in DATA_AS_DICT to get a dict of each object
        for data_type in self.keys():
            data_to_save[data_type] = [
                attr.asdict(data_object) for data_object in self.data_as_dict[data_type]
            ]

        return data_to_save
