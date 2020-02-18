/**
 * @file fsm.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-02-11
 * 
 * @copyright Copyright (c) 2020
 * 
 * @note Based on https://barrgroup.com/embedded-systems/how-to/state-machines-event-driven-systems 
 * 
 */

#include "fsm.h"
#include "hardware.h"
#include <stdbool.h>

typedef struct fsm_t fsm_t;

typedef void (*state_function)(fsm_event_t event);

struct fsm_t {
    state_function state;
    fsm_state_t current_floor;
};

// FSM functions
static void fsm_transition(state_function new_state);

// State functions
static void state_init                  (fsm_event_t event);
static void state_unknown_floor         (fsm_event_t event);
static void state_idle                  (fsm_event_t event);
static void state_moving                (fsm_event_t event);
static void state_door_open             (fsm_event_t event);
static void state_emergency_stop        (fsm_event_t event);
static void state_emergency_stop_nowhere(fsm_event_t event);
static void state_emergency_stop_floor  (fsm_event_t event);

static fsm_t fsm;

// 

void fsm_init()
{

}

void fsm_run()
{

}

void fsm_dispatch(fsm_event_t event)
{
    (fsm.state)(event);
}

// FSM functions

static void fsm_transition(state_function new_state)
{
    fsm_dispatch(EVENT_EXIT);

    fsm.state = new_state;

    fsm_dispatch(EVENT_ENTRY);
}

// State Functions

static void state_init(fsm_event_t event)
{
    switch(event)
    {
        case EVENT_FOUND_FLOOR:

        break;

        case EVENT_EXIT:

        break;
    }
}

static void state_unknown_floor(fsm_event_t event)
{
    switch(event)
    {

    }
}

static void state_idle(fsm_event_t event)
{
    switch(event)
    {

    }
}

static void state_moving(fsm_event_t event)
{
    switch(event)
    {

    }
}

static void state_door_open(fsm_event_t event)
{
    switch(event)
    {
        case EVENT_ENTRY:
            hardware_command_door_open(true);
        break;

        case EVENT_OBSTRUCTION_ACTIVE:
            //fsm_transition(&state_door_open);
            // reset_timer, state transition vil ikke funke, blinke leds og shit
        break;

        case EVENT_TIMER_TIMEOUT:
            fsm_transition(&state_idle);
        break;

        case EVENT_EXIT:
            hardware_command_door_open(false);
        break;
    }
}

static void state_emergency_stop(fsm_event_t event)
{
    switch(event)
    {
        case EVENT_ENTRY:
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        break;

        case EVENT_STOP_BUTTON_RELEASED:
        { 
            if(on_floor())
            {
                fsm_transition(&state_emergency_stop_floor);
            }
            else
            {
                fsm_transition(&state_emergency_stop_nowhere);
            }
        }   
        break;

        case EVENT_EXIT:

        break;
    }
}

static void state_emergency_stop_nowhere(fsm_event_t event)
{
    switch(event)
    {
        case EVENT_ENTRY:

        break;

        case EVENT_STOP_BUTTON_RELEASED:
            fsm_transition(&state_idle);
        break;

        case EVENT_EXIT:

        break;
    }
}

static void state_emergency_stop_floor(fsm_event_t event)
{
    switch(event)
    {
        case EVENT_ENTRY:
            hardware_command_door_open(true);
        break;

        case EVENT_EXIT:

        break;
    }
}


