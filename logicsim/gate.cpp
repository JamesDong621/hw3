#include <vector>
#include <random>
#include <iostream>

#include "gate.h"
#include "wire.h"

Gate::Gate(int num_inputs, Wire* output) 
	: m_output(output), m_inputs(num_inputs), m_delay(0), m_current_state('X')
{
    
}

Gate::~Gate(){}

void Gate::wireInput(unsigned int id, Wire* in)
{
    if(id < m_inputs.size())
    {
        m_inputs[id] = in;
    }
}

And2Gate::And2Gate(Wire* a, Wire* b, Wire* o) : Gate(2,o)
{
    wireInput(0,a);
    wireInput(1,b);
}

Event* And2Gate::update(uint64_t current_time)
{
    
  char state = '1';
  Event* e = nullptr;
	for(auto w : m_inputs)
	{
		char in = w->getState();
		if(in == '0')
		{
			state = '0';
			break;
		}
		else if(in == 'X')
		{
			state = 'X';
		}
	}
    if(state != m_current_state)
	{
    m_current_state = state;
    uint64_t next = current_time + m_delay;
		e = new Event {next,m_output,state};
         
	}
    return e;
}

Or2Gate::Or2Gate(Wire* a, Wire* b, Wire* o) : Gate(2,o)
{
    wireInput(0,a);
    wireInput(1,b);
}

Event* Or2Gate::update(uint64_t current_time)
{
    
  char state = '0';
  Event* e = nullptr;
	for(auto w : m_inputs)
	{
		char in = w->getState();
		if(in == '1')
		{
			state = '1';
			break;
		}
		else if(in == 'X')
		{
			state = 'X';
		}
	}
  if(state != m_current_state)
	{
    m_current_state = state;
		uint64_t next = current_time + m_delay;
		e = new Event {next,m_output,state};
         
	}
  return e;
}


NotGate::NotGate(Wire* input, Wire* output) : Gate(1, output) {
    wireInput(0, input); // Assign the single input wire to the gate.
}

Event* NotGate::update(uint64_t current_time) {
    char state = '0'; // Get the current state of the input wire.
    char newState; // Determine the new state based on the NOT operation.
	for(auto w : m_inputs)
	{
		char in = w->getState();
		if(in == '1')
		{
			state = '1';
			break;
		}
		else if(in == '0')
		{
			state = '0';
			break;
		}
		else if(in == 'X')
		{
			state = 'X';
			break;
		}
	}
    // Perform the NOT operation unless the input state is undefined ('X').
    switch (state) {
        case '0':
            newState = '1'; // NOT 0 = 1
            break;
        case '1':
            newState = '0'; // NOT 1 = 0
            break;
        default:
            newState = 'X'; // Undefined input leads to undefined output.
            break;
    }

    // Only generate a new event if the state of the output wire needs to change.
    if (newState != m_current_state) {
        m_current_state = newState; // Update the current state of the gate.
        uint64_t nextTime = current_time + m_delay; // Calculate the time for the event based on the gate delay.
        return new Event{nextTime, m_output, newState}; // Create and return the new event.
    }

    return nullptr; // If no state change is needed, return nullptr.
}
