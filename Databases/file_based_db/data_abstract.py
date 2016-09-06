import data_types
import utils
import attrs
import os

# Data is loaded from a dictionary of lists for listing and flight options
# instead of having to read the file each time

class DataController():
    data = attr.ib()
    data_file = attr.ib()

    def __init__(self):
        # Create new DataWrapper & DataFile instances when
        # DataController is initialized
        self.data = DataWrapper()
        self.data_file = DataFile()

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

            # Update the last
            

    def list_items(self, type_to_list):
        self.load_from_file()
        list_of_items = self.data.prep_for_list(type_to_list)
        if list_of_items:
            for item in list_of_items:
                print(item)
        else:
            print('No ' + type_to_list.lower() + ' were found.')

    def add_item(self, data_type, data_info):

        # Validate that the data inputted is valid, i.e. names shouldn't
        # have numbers in them, and that price's value is a valid int

        # DataTypeFactory will handle 
        new_object = data_types.DataTypeFactory(data_type, data_info)
        # Check that there isn't a duplicate already
        
        pass
        
        
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

    def get_full_name(self, field_name, data_type_key):
        matched_object = next(filter(
            lambda obj: getattr(obj, field_name),
            self.data_as_dict[data_type_key]
        ));
        return getattr(matched_object, 'full_name')

    def is_predefined(self, data_key, code, member_name):
        # Check that either the city code or airline abbreviation s predefined
        type_collection = self.data_as_dict[data_key]
        codes = [getattr(obj, member_name) for obj in type_collection]
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

    def prep_for_list(self, data_type):
        data_type
        if data_type != 'FLIGHTS':
            # For City and Airline objects, we return a list of their str
            # representations
            return [
                str(obj) for obj in self.data_as_dict[data_type]
            ]
                        
        else:
            # Flight needs to the full names of the airlines, which it can't
            # The attributes of the flights are passed back as a conjoined string
            # (separated by spaces), which are then split to create a list of the data
            flight_data = [
                (str(flight)).split() for flight in self.data_as_dict[data_type]
            ]

            # We need the full names for the airline and the cities, AKA
            # elements 0 - 2 in flight_attr_lists
            full_flight_data = [
                self.get_full_name(data_field) for data_field in flight_attr_lists[0:2]
            ] + flight_attr_lists[-1]  # Tack on the price at the end

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
            
class DataFile():

    # Location of where the data file should be
    DATA_FILE_LOCATION = './data.json'
    last_modified_time = -1

    def check_existence(self):
        try:
            with open(self.DATA_FILE_LOCATION) as data_file:
                pass
            return True
        except OSError:
            pass
        return False

    def check_if_modified(self):
        # Get the time of the last modification to the data file
        last_modified_time = os.stat(self.DATA_FILE_LOCATION).st_mtime
        # Return the comparison between the saved last modified time
        # and the most recent time. Guaranteed to return True if we haven't
        # loaded the data_file yet because the default value is -1
        return self.last_modified_time != last_modified_time

    def update_last_modified_time(self):
        # Update the time of the last modification of the data file
        # that this instance is aware of
        last_modified_time = os.stat(self.DATA_FILE_LOCATION).st_mtime
        self.last_modified_time = last_modified_time
    
    def save(self, save_data):
        # Save data to the data file
        with open(self.DATA_FILE_LOCATION, 'w', encoding='utf-8') as data_file:
            json.dump(data_to_save, data_file, ensure_ascii=False)
            
    def load(self):
        with open(self.DATA_FILE_LOCATION) as data_file:
            # Attempt to load data_file;
            read_data = data_file.read()
        return read_data
