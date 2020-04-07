/**
 * @author Ammar Faizi <ammarfaizi2@gmail.com>
 * @version 7.4.0
 * @license MIT
 */

#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <classes/Bot.hpp>
#include <classes/ResponseRoutes.hpp>

using namespace TeaBot;

extern "C" {

void init_daemon()
{
    ResponseRoutes::initRoutes();
}

void *execute_payload(char *payload)
{	
    Bot *st = new Bot(std::string(payload));
    st->execute();
    delete st;
    free(payload);
    return NULL;
}

}
