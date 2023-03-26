#include "application.h"
int main(int argc, char** argv) {
    try {
        Application app(argc, argv);
        app.Run();
        return 0;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    } catch (...) {
        return -2;
    }
}
