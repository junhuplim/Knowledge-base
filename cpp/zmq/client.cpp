//
//   Request-reply client in C++
//   Connects REQ socket to tcp://localhost:5559
//   Sends "Hello" to server, expects "World" back
//

#include <iostream>
#include <chrono>
#include "zmq.hpp"

int main ()
{
    zmq::context_t context(1);

    zmq::socket_t requester_sock(context, ZMQ_REQ);
    requester_sock.connect("tcp://localhost:5559");

    for( int request = 0 ; request < 10 ; request++) {

        zmq::message_t msg("hello", 6);
        requester_sock.send(std::move(msg), zmq::send_flags::none);

        auto recv_res = requester_sock.recv(msg, zmq::recv_flags::none);
        if (recv_res) {
            std::cout << "Received reply " << request << " [" << msg << "]" << std::endl;
        }
    }
}

