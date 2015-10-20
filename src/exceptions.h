//
// Created by julian on 12.10.15.
//

#ifndef MATRIX_EXCEPTIONS_H
#define MATRIX_EXCEPTIONS_H

#include <iostream>
#include  <string>


namespace jib {
    class invalid_dimension_exception {
    public:
        invalid_dimension_exception();
        invalid_dimension_exception(std::string msg);

    private:
        std::string text;
    };
}

#endif //MATRIX_EXCEPTIONS_H
