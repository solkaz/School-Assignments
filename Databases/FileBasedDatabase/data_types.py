import attr

@attr.s
class City():
    city_code = attr.ib(validator=attr.validators.instance_of(str))
    full_name = attr.ib(validator=attr.validators.instance_of(str))

    def __str__(self):
        return ' '.join([self.city_code, self.full_name])

@attr.s
class Airline():
    abbreviation = attr.ib(validator=attr.validators.instance_of(str))
    full_name = attr.ib(validator=attr.validators.instance_of(str))

    def __str__(self):
        return ' '.join([self.abbreviation, self.full_name])
    
@attr.s
class Flight():
    airline_code = attr.ib(validator=attr.validators.instance_of(str))
    departure_airport_code = attr.ib(validator=attr.validators.instance_of(str))
    arrival_airport_code = attr.ib(validator=attr.validators.instance_of(str))
    price = attr.ib(validator=attr.validators.instance_of(int))

    def __str__(self):
        
        return ' '.join([self.airline_code, self.departure_airport_code, self.arrival_airport_code, self.price])
