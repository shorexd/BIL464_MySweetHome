#ifndef ABSTRACTACTIONHANDLER_H
#define ABSTRACTACTIONHANDLER_H

#include <string>

class AbstractActionHandler {
public:
    AbstractActionHandler();
    virtual ~AbstractActionHandler();

    AbstractActionHandler* setNext(AbstractActionHandler* handler);

    virtual bool handle(const std::string& context);

private:
    AbstractActionHandler* next_handler;
};

#endif // ABSTRACTACTIONHANDLER_H