#include "connector.hpp"
#include "utils.hpp"

#include <iostream>

Connector::Connector() {
    mysql_init(&mysql);
}

void Connector::GetConnectionData() {
    std::cout << "Hostname: ";
    std::cin >> db_connection_data_[HOST];

    std::cout << "Username: ";
    std::cin >> db_connection_data_[USERNAME];

    std::cout << "Password: ";
    db_connection_data_[PASSWORD] = GetPassword();

    std::cout << "Name: ";
    std::cin >> db_connection_data_[NAME];
}

void Connector::ConnectToDB() {

    std::cout << "Connecting to DB..." << std::endl;
    connector = mysql_real_connect(&mysql,
				   db_connection_info[HOST],
				   db_connection_info[USERNAME],
				   db_connection_info[PASSWORD]
				   db_connection_info[NAME], 0, 0 , 0);
    if (connector == nullptr) {
	throw std::runtime_error(mysql_error(&mysql)) << std::endl;
    }

    std::cout << "Connection succeeded" << std::endl;
}
