import attr
import re
import utils

@attr.s
class City():
    city_code = attr.ib(validator=attr.validators.instance_of(str))
    full_name = attr.ib(validator=attr.validators.instance_of(str))
    
    @staticmethod
    def validate(args):
        return not(
            utils.has_digits(args['city_code']) and
            utils.has_digits(args['full_name'])
        )
    
    def __str__(self):
        return ' '.join([self.city_code, self.full_name])

@attr.s
class Airline():
    abbreviation = attr.ib(validator=attr.validators.instance_of(str))
    full_name = attr.ib(validator=attr.validators.instance_of(str))

    @staticmethod
    def validate(args):
        return not(
            utils.has_digits(args['abbreviation']) and
            utils.has_digits(args['full_name'])
        )
    
    def __str__(self):
        return ' '.join([self.abbreviation, self.full_name])

@attr.s
class Flight():
    airline_code = attr.ib(validator=attr.validators.instance_of(str))
    departure_airport_code = attr.ib(validator=attr.validators.instance_of(str))
    arrival_airport_code = attr.ib(validator=attr.validators.instance_of(str))
    price = attr.ib(validator=attr.validators.instance_of(int))

    @staticmethod
    def validate(args):
        return not(
            utils.has_digits(args['airline_code']) or
            utils.has_digits(args['departure_airport_code']) or
            utils.has_digits(args['arrival_airport_code']) or
        ) and utils.is_valid_int(args['price'])

    def __str__(self):

        # Get the airline's full-name from the airline code
        airline_full_name = utils.get_full_name(
            'abbreviation',
            self.airline_code,
            'AIRLINES'
        )
        departure_city_full_name = utils.get_full_name(
            'city_code',
            self.departure_airport_code,
            'CITIES'
        )
        arrival_city_full_name = utils.get_full_name(
            'city_code',
            self.arrival_airport_code,
            'CITIES'
        )

        # Format the string with the full information and return it
        return ' '.join(
            self.airline_code,
            self.departure_airport_code,
            self.arrival_airport_code, 
            str(self.price)
        )

def getClassFromKey(key):
    if data_type == 'CITIES':
        return City
    elif data_type == 'AIRLINES':
        return Airline
    elif data_type == 'FLIGHTS':
        return Flight

class DataTypeFactory():
        
    @staticmethod
    def create_from_entry(data_key, args):
        data_type = getClassFromKey(data_key)

        # Validate the data
        if data_type.validate(args):
            new_object = data_type(args)
        else:
            print('Invalid data supplied to Add operation. Please check data\n'+
                  'and try again')
            return None
        pass

    @staticmethod
    def create_from_file_data(loaded_data):
        # 
        created_objects = {
            'CITIES': [],
            'AIRLINES': [],
            'FLIGHTS': [],
        }
        
        for data_key in loaded_data:
            # Get the class constructor from the key
            data_type = getClassFromKey(data_key)

            # Iterate through each entry in the loaded data
            for entry in data_key:
                
                if data_type.validate(entry):
                    new_object = data_type(entry)
                    created_objects[data_key].append(new_object)

        return created_objects
