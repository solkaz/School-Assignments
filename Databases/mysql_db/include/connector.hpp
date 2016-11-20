#ifndef CONNECTOR_HPP_
#define CONNECTOR_HPP_

#include <array>
#include <string>

using ConnectionData = std::array<std::string, 4>;

class Connector {
    MYSQL *connector_;
    ConnectionData db_connection_data_;
public:
    Connector();
    void GetConnectionData();
    void ConnectToDB();
};

#endif // CONNECTOR_HPP_
