//
//   Request-reply service in C++
//   Connects REP socket to tcp://localhost:5560
//   Expects "Hello" from client, replies with "World"
//

#include <iostream>
#include <chrono>
#include <thread>
#include "zmq.hpp"

int main ()
{
    zmq::context_t context(1);
    zmq::message_t msg;
    zmq::socket_t responder_sock(context, ZMQ_REP);
    responder_sock.connect("tcp://localhost:5560");

    while(1)
    {
        //  Wait for next request from client
        auto res = responder_sock.recv(msg, zmq::recv_flags::none);
        if (res) {
            std::cout << "Received request: " << msg << std::endl;
        }

        //  Simulate work
        std::this_thread::sleep_for(std::chrono::seconds(1));

        //  Send reply to client
        zmq::message_t response_msg("world", 6);
        responder_sock.send(std::move(response_msg), zmq::send_flags::none);
    }
}
