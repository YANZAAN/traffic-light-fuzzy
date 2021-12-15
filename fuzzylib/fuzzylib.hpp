#ifndef FL_LIB_H
#define FL_LIB_H

#include <fl/Headers.h>

using namespace fl;

namespace fuzzylib
{
    class TLEngine {
        public:
         static Engine* create();
         static std::tuple<scalar, scalar> run(Engine*, std::tuple<scalar, scalar>);
         static void test(Engine*, short);

        private:
         TLEngine() {}
    };
} // namespace fuzzylib

#endif