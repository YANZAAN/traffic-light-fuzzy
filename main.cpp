#include "fuzzylib/fuzzylib.hpp"

using namespace fuzzylib;

int main(int argc, char **argv)
{
    /* ------ Creating engine ------ */
    Engine* engine = TLEngine::create();

    /* ------ Testing engine ------ */
    TLEngine::test(engine, 10);

    delete engine;
}
