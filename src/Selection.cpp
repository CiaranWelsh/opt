//
// Created by Ciaran on 12/02/2021.
//

#include "Selection.h"


namespace opt {

    Selection::Selection(int howMany)
        : howMany_(howMany){}

    int Selection::getHowMany() const {
        return howMany_;
    }

    void Selection::setHowMany(int howMany) {
        howMany_ = howMany;
    }
}