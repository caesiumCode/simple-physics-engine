#include "Application.hpp"

int main(int argc, char const** argv)
{
    Application application;
    
    application.initialise();
    application.run();

    return EXIT_SUCCESS;
}
