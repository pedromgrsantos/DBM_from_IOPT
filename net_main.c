/* Net TP2_2022_IOPT_TOOLS - IOPT */
/* Automatic code generated by IOPT2C XSLT transformation. */


#include <stdlib.h>
#include "net_types.h"


int trace_control = TRACE_CONT_RUN;

extern void httpServer_init();
extern void httpServer_getRequest();
extern void httpServer_sendResponse();
extern void httpServer_disconnectClient();
extern void httpServer_checkBreakPoints();
extern void httpServer_finish();

static TP2_2022_IOPT_TOOLS_NetMarking marking;
static TP2_2022_IOPT_TOOLS_InputSignals inputs, prev_inputs;
static TP2_2022_IOPT_TOOLS_PlaceOutputSignals place_out;
static TP2_2022_IOPT_TOOLS_EventOutputSignals ev_out;

void setup()
{
    createInitial_TP2_2022_IOPT_TOOLS_NetMarking( &marking );
    init_TP2_2022_IOPT_TOOLS_OutputSignals( &place_out, &ev_out );
    TP2_2022_IOPT_TOOLS_InitializeIO();
    TP2_2022_IOPT_TOOLS_GetInputSignals( &prev_inputs, NULL );
#ifdef HTTP_SERVER
    httpServer_init();
#endif
}

void loop()
{
#ifdef HTTP_SERVER
    httpServer_getRequest();
#endif

    if( trace_control != TRACE_PAUSE )
        TP2_2022_IOPT_TOOLS_ExecutionStep( &marking, &inputs, &prev_inputs, &place_out, &ev_out );
    else TP2_2022_IOPT_TOOLS_GetInputSignals( &inputs, NULL );
    if( trace_control > TRACE_PAUSE ) --trace_control;

#ifdef HTTP_SERVER
    httpServer_sendResponse();
#endif

    TP2_2022_IOPT_TOOLS_LoopDelay();

#ifdef HTTP_SERVER
    httpServer_disconnectClient();
    httpServer_checkBreakPoints();
#endif
}

#ifndef ARDUINO
int main()
{
    setup();

    do loop();
    while( TP2_2022_IOPT_TOOLS_FinishExecution( &marking ) == 0 );

#ifdef HTTP_SERVER
    httpServer_finish();
#endif

    return 0;
}
#endif


TP2_2022_IOPT_TOOLS_NetMarking* get_TP2_2022_IOPT_TOOLS_NetMarking()
{
    return &marking;
}

TP2_2022_IOPT_TOOLS_InputSignals* get_TP2_2022_IOPT_TOOLS_InputSignals()
{
    return &inputs;
}

TP2_2022_IOPT_TOOLS_PlaceOutputSignals* get_TP2_2022_IOPT_TOOLS_PlaceOutputSignals()
{
    return &place_out;
}

TP2_2022_IOPT_TOOLS_EventOutputSignals* get_TP2_2022_IOPT_TOOLS_EventOutputSignals()
{
    return &ev_out;
}

