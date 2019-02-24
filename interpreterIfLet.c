#include <stdio.h>
#include <string.h>
#include "value.h"
#include "interpreter.h"
#include "talloc.h"
#include "assert.h"
#include "linkedlist.h"
#include "parser.h"


Value *lookUpSymbol(Value *symbol, Frame *frame) {

}


void evaluationError() {

}


Value *evalIf(Value *args, Frame *frame) {

}


void interpret(Value *tree) {
    Value *evalResult;
    Frame *global = talloc(sizeof(Frame));
    global->bindings = makeNull();
    global->parent = NULL;
    Frame *previous = talloc(sizeof(Frame));
    previous->bindings = makeNull();
    previous->parent = NULL;
    while (tree->type) {
        if (car(tree)->type != CONS_TYPE) {  //case where there's one thing in car of the tree
            global->bindings = cons(car(tree), global->bindings);
            evalResult = eval(car(tree), global);  //call eval on car and the global
            global->bindings = cons(evalResult, global->bindings);
        } else {
            Frame *frame = talloc(sizeof(Frame));  //case where there's more than one thing in car of tree
            frame->bindings = makeNull();      //initialize a new frame
            if (previous->parent == NULL) {    //if first previous hasn't been initialized, point to global
                frame->parent = global;
            } else {
                frame->parent = previous;
            }
            previous = frame;     //updating previous to point to current frame
            evalResult = eval(car(tree), frame);
            frame->bindings = cons(evalResult, frame->bindings);
        }
    tree = cdr(tree);
    }
}


Value *eval(Value *tree, Frame *frame) {
    switch (tree->type)  {
        case INT_TYPE: {
            ...
            break;
        }
        case ......: {
        ...
        break;
    }
        case SYMBOL_TYPE: {
            return lookUpSymbol(tree, frame);
            break;
        }
        case CONS_TYPE: {
            Value *first = car(tree);
            Value *args = cdr(tree);

            // Sanity and error checking on first...

            if (!strcmp(first->s,"if")) {
                result = evalIf(args,frame);
            }

                // .. other special forms here...

            else {
                // not a recognized special form
                evaluationError();
            }
            break;
        }

            ....
    }
    ....
}
