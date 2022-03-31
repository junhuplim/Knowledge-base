//
//  Simple request-reply broker in C++
//

#include <chrono>
#include "zmq.hpp"

int main ()
{
    //  Prepare our context and sockets
    zmq::context_t context(1);
    zmq::socket_t frontend_sock (context, ZMQ_ROUTER);
    zmq::socket_t backend_sock (context, ZMQ_DEALER);

    frontend_sock.bind("tcp://*:5559");
    backend_sock.bind("tcp://*:5560");

    //  Initialize poll set
    zmq::pollitem_t items [] = {
    { frontend_sock, 0, ZMQ_POLLIN, 0 },
    { backend_sock, 0, ZMQ_POLLIN, 0 }
    };

    //  Switch messages between sockets
    zmq_proxy(frontend_sock, backend_sock, NULL);

    //  We never get here
    zmq_close(frontend_sock);
    zmq_close(backend_sock);
//    zmq_ctx_destroy(context);

//    while (1) {
//        zmq::message_t message;
//        int more;               //  Multipart detection
//        zmq::poll (&items [0], 2, std::chrono::seconds(1));
//        if (items [0].revents & ZMQ_POLLIN) {
//            while (1) {
//                //  Process all parts of the message
//                auto res = frontend_sock.recv(message, zmq::recv_flags::none);
//                if (res) {
//                    more = frontend_sock.get(zmq::sockopt::rcvmore);
//                    backend_sock.send(message, more? zmq::send_flags::sndmore : zmq::send_flags::none);
//                }
//
//                if (!more)
//                    //  Last message part
//                    break;
//            }
//        }
//        if (items [1].revents & ZMQ_POLLIN) {
//            while (1) {
//                //  Process all parts of the message
//                auto res = backend_sock.recv(message, zmq::recv_flags::none);
//                if (res) {
//                    more = backend_sock.get(zmq::sockopt::rcvmore); // new syntax
//                    frontend_sock.send(message, more? zmq::send_flags::sndmore : zmq::send_flags::none);
//                }
//
//                if (!more)
//                    //  Last message part
//                    break;
//            }
//        }
//    }
    return 0;
}