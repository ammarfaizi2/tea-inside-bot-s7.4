
#include <string>
#include <stdlib.h>
#include <classes/Bot.hpp>

using namespace TeaBot;

extern "C" {

void init_daemon(char *payload, size_t length)
{
    Bot *st = new Bot(std::string(payload));
    st->execute();
    delete st;
    free(payload);
}

}
