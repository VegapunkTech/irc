#include"../include/server.hpp"


int main(int ac, char **av)
{
    //signal(SIGINT, signalHandler);
    if(ac != 3)
    {
        //std::cout << "Error : The number of arguments must be equal to 2 !" <<std::endl;
        return(0);
    }
    Server *srv= new Server(std::atoi(av[1]), std::string(av[2]));

    (void)srv->run();
}
