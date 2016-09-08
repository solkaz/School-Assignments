import json
import os

class DataFile():

    # Location of where the data file should be
    DATA_FILE_LOCATION = './data.json'
    last_modified_time = -1

    def check_existence(self):
        # Attempt to open the data file; if it doesn't exist, then it an
        # OSError will be raised
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
            json.dump(save_data, data_file, ensure_ascii=False)
            
    def load(self):
        with open(self.DATA_FILE_LOCATION) as data_file:
            # Attempt to load data_file;
            read_data = data_file.read()
        # Return the contents of the data file
        return read_data
