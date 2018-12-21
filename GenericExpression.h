//
// Created by omer on 12/15/18.
//

#ifndef PROJECT_GENERICEXPRESSION_H
#define PROJECT_GENERICEXPRESSION_H

#include "Expression.h"

class GenericExpression {
    GenericExpression(Expression* e);
    Expression* getOriginalExpression();
};

#endif //PROJECT_GENERICEXPRESSION_H
