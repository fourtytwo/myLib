//
// Created by julian on 12.10.15.
//

#include "exceptions.h"

namespace jib {

    invalid_dimension_exception::invalid_dimension_exception() { }


    invalid_dimension_exception::invalid_dimension_exception(std::string msg ):
            text{msg}
    { }

}