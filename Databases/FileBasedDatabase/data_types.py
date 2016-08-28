import attr

@attr.s
class City():
    city_code = attr.ib(validator=attr.validators.instance_of(str))
    full_name = attr.ib(validator=attr.validators.instance_of(str))

    def __str__(self):
        return ' '.join([city_code, full_name])

@attr.s
class Airline():
    abbreviation = attr.ib(validator=attr.validators.instance_of(str))
    full_name = attr.ib(validator=attr.validators.instance_of(str))

    def __str__(self):
        return ' '.join([abbreviation, full_name])
    
@attr.s
class Flight():
    airline_code = attr.ib(validator=attr.validators.instance_of(str))
    departure_airport_code = attr.ib(validator=attr.validators.instance_of(str))
    arrival_airport_code = attr.ib(validator=attr.validators.instance_of(str))
    price = attr.ib(validator=attr.validators.instance_of(int))

    def __str__(self):
        return ' '.join([airline_code, departure_airport_code, arrival_airport_code, price])
