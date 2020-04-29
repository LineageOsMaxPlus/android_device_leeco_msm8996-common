#define LOG_TAG "ConsumerIrService-UDPClient"

#include <android-base/logging.h>

#include <netinet/in.h>
#include "UDPClient.h"

UDPClient::UDPClient(const std::string& addr, int port)
    : f_port(port)
    , f_addr(addr)
{

    char decimal_port[16];
    struct addrinfo hints;
    int ret_val;

    snprintf(decimal_port, sizeof(decimal_port), "%d", f_port);

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_protocol = IPPROTO_UDP;

    ret_val = getaddrinfo(addr.c_str(), decimal_port, &hints, &f_addrinfo);

    LOG(DEBUG) << "Trying to create socket: " + addr + ":" + decimal_port;

    if(ret_val != 0 || f_addrinfo == NULL)
    {

        LOG(ERROR) << "invalid address or port: \"" + addr + ":" + decimal_port + "\"";
    } else {

        LOG(DEBUG) << "valid address or port: \"" + addr + ":" + decimal_port + "\"";
    }

    f_socket = socket(f_addrinfo->ai_family, SOCK_DGRAM | SOCK_CLOEXEC, IPPROTO_UDP);

    if(f_socket == -1)
    {
        freeaddrinfo(f_addrinfo);
        LOG(ERROR) << "Could not create socket for: " + addr + ":" + decimal_port;
    } else {

        LOG(ERROR) << "create socket for: " + addr + ":" + decimal_port + " success.";
    }

}

UDPClient::~UDPClient()
{
    freeaddrinfo(f_addrinfo);
    close(f_socket);
}

int UDPClient::get_socket() const
{
    return f_socket;
}

int UDPClient::get_port() const
{
    return f_port;
}

std::string UDPClient::get_addr() const
{
    return f_addr;
}

int UDPClient::send(const char *msg, size_t size)
{
    return sendto(f_socket, msg, size, 0, f_addrinfo->ai_addr, f_addrinfo->ai_addrlen);
}
