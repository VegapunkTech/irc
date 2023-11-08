#include"server.hpp"


int main()
{
    Server *srv= new Server(6667);

    (void)srv->run();


}
