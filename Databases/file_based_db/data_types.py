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

    @staticmethod
    def get_fields():
        return [
            'city_code',
            'full_name'
        ]
    
    @staticmethod
    def format_args(args):
        return [
            args[0],
            ' '.join(args[1:])
        ]
    
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
    
    @staticmethod
    def get_fields():
        return [
            'abbreviation',
            'full_name'
        ]

    @staticmethod
    def format_args(args):
        return [
            args[0],
            ' '.join(args[1:])
        ]
    
    def __str__(self):
        return ' '.join([self.abbreviation, self.full_name])

@attr.s
class Flight():
    airline_code = attr.ib(validator=attr.validators.instance_of(str))
    departure_airport_code = attr.ib(validator=attr.validators.instance_of(str))
    arrival_airport_code = attr.ib(validator=attr.validators.instance_of(str))
    # Price *should* be an int, but for formatting purposes it is a string
    # it will be checked that it is a valid int, however
    price = attr.ib(validator=attr.validators.instance_of(int)) 

    @staticmethod
    def validate(args):
        return (
            not(
                utils.has_digits(args['airline_code']) or
                utils.has_digits(args['departure_airport_code']) or
                utils.has_digits(args['arrival_airport_code'])
            ) and utils.is_valid_int(args['price'])
        )

    @staticmethod
    def get_fields():
        return [
            'airline_code',
            'departure_airport_code',
            'arrival_airport_code',
            'price'
        ]

    @staticmethod
    def format_args(args):
        return args[:-1] + [int(args[-1])]

    def __str__(self):

        # Format the string with the full information and return it
        return ' '.join([
            self.airline_code,
            self.departure_airport_code,
            self.arrival_airport_code, 
            str(self.price)
        ])

def getClassFromKey(key):
    if key == 'CITIES':
        return City
    elif key == 'AIRLINES':
        return Airline
    elif key == 'FLIGHTS':
        return Flight

class DataTypeFactory():
        
    @staticmethod
    def create_from_entry(data_key, args):
        data_type = getClassFromKey(data_key)
        data_field_names = data_type.get_fields()

        # Each type is expecting a certain number of args; format them as such
        formatted_args = data_type.format_args(args)
        mapped_args = utils.map_args_to_fields(data_field_names, formatted_args)
        # Validate the data
        if data_type.validate(mapped_args):
            new_object = data_type(**mapped_args)
            return new_object
        else:
            print('Invalid data supplied to Add operation. Please check data\n'+
                  'and try again')
            return None

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
            for entry in loaded_data[data_key]:
                
                if data_type.validate(entry):
                    new_object = data_type(**entry)
                    created_objects[data_key].append(new_object)
                else:
                    print('Invalid data supplied to Add operation. Please check data\n'+
                          'and try again')
                    return []

        return created_objects
