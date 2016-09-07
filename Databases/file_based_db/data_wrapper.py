import attr

class DataWrapper():
    data_as_dict = {
        "CITIES": [],
        "AIRLINES": [],
        "FLIGHTS": []
    }

    def __getitem__(self, key):
        return self.data_as_dict[key]

    def update_data_as_dict(self, new_data):
        self.data_as_dict = new_data

    def keys(self):
        return self.data_as_dict.keys()

    def add_item(self, data_type, new_object):
        self.data_as_dict[data_type].append(new_object)

    def get_full_name(self, code, field_name, data_type_key):
        matched_object = next(filter(
            lambda obj: getattr(obj, field_name) == code,
            self.data_as_dict[data_type_key]
        ));
        return getattr(matched_object, 'full_name')

    def is_predefined(self, data_key, code, member_name):
        # Check that either the city code or airline abbreviation s predefined
        type_collection = self.data_as_dict[data_key]
        codes = [ getattr(obj, member_name) for obj in type_collection ]
        return code in codes

    def is_not_duplicate(self, data_key, new_object):

        # For City and Airline objects, we can check if the code/abbreviation is
        # predefined; if it is, then it is a duplicate
        # Note that multiple objects of either type can have the same full name,
        # but there can't be a shared code/abbreviation between them
        if data_key == "CITIES":
            return not self.is_predefined(
                data_key,
                new_object.city_code,
                'city_code'
            )
        elif data_key == "AIRLINES":
            return not self.is_predefined(
                data_key,
                new_object.abbreviation,
                'abbreviation'
            )
        else:
            # For a Flight, it is a duplicate if there is already an object
            # with the exact same data. 
            return new_object in self.data_as_dict[data_key]
        
    def clear(self, data_key):
        self.data_as_dict[data_key].clear()
        
    def reset(self):
        for data_key in self.keys():
            self.clear(data_key)

    def connecting_flight_search(self, cities):
        all_flights = self.data_as_dict['FLIGHTS']

        departing_flights = filter(
            lambda flight_obj: flight_obj.departure_airport_code == cities[0],
            all_flights
        )
        
        arriving_flights = filter(
            lambda flight_obj: (
                flight_obj.arrival_airport_code == cities[1] and
                # Make sure that direct flights to dest. city are not included
                flight_obj.departure_airport_code != cities[0]
            ),
            all_flights
        )

        '''
        The list of common elements 
        Extract the list of common elements between 
        '''
        intermediary_cities = list(
            set(departing_flights).intersection(arriving_flights)
        )
        # Iterate through all intermediary cities
        for city in intermediary_cities:
            # Construct list of flights from departure city to an intermediary city
            leg_one_flights = list(filter(
                lambda flight_obj: flight_obj.arrival_airport_code == city,
                departing_flights
            ))
            # Next get list of flights from intermediary to destination city
            leg_two_flights = list(filter(
                lambda flight_obj: flight_obj.departure_airport_code == city,
                arriving_flights
            ))

            # Group 
    
            
    def simple_flight_search(self, cities):
        all_flights = self.data_as_dict['FLIGHTS']
        # Filter out flights that don't have the specified departure city coden 
        departing_flights = filter(
            lambda flight_obj: flight_obj.departure_airport_code == cities[0],
            all_flights
        )

        # From flights_from_departure, get all flights that are arriving in
        # the inputted arrival city
        matching_flights = filter(
            lambda flight_obj: flight_obj.arrival_airport_code == cities[1],
            departing_flights
        )
    
    def prep_for_list(self, data_type):
        if data_type != 'FLIGHTS':
            # For City and Airline objects, we return a list of their str
            # representations
            return [ str(obj) for obj in self.data_as_dict[data_type] ]
                        
        else:
            # Flight needs to the full names of the airlines, which it can't
            # The attributes of the flights are passed back as a conjoined string
            # (separated by spaces), which are then split to create a list of the data
            flight_data = [
                (str(flight)).split() for flight in self.data_as_dict[data_type]
            ]

            # We need the full names for the airline and the cities
            full_flight_data = [
                self.get_full_name(flight_data[0], 'abbreviation', 'AIRLINES'),
                self.get_full_name(flight_data[1], 'city_code', 'CITIES'),
                self.get_full_name(flight_data[2], 'city_code', 'CITIES'),
                flight_data[-1]
            ]

            # Return the list of formatted strings for each flight's info
            return [
                utils.format_flight_info(flight_info) for flight_info in full_flight_data
            ]
        
    def prep_for_saving(self):
        # Create a copy of DATA_AS_DICT, except the keys in DATA_AS_DICT map to lists of
        # dictionary representations of each object, which can be used to easily
        # create the objects again upon being loaded

        data_to_save = {}        
        # Apply attrs.asdict to each section in DATA_AS_DICT to get a dict of each object
        for data_type in self.keys():
            data_to_save[data_type] = [
                attrs.asdict(data_object) for data_object in self.data_as_dict[data_type]
            ]

        return data_to_save
