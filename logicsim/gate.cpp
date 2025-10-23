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

NotGate::NotGate(Wire* in, Wire* out) : Gate(1, out){
  wireInput(0, in);
}

Event* NotGate::update(uint64_t tiempo){
  char state;
  char in = m_inputs[0]->getState();
  if(in == '0'){
    state = '1';
  }
  else if(in == '1'){
    state = '0';
  }
  else{
    state = 'X';
  }

  Event* e = nullptr;
  if(m_current_state != state){
    m_current_state = state;
    uint64_t next = tiempo + m_delay;
    e = new Event{next, m_output, state};
  }
  return e;
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
  bool x = false;
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
			x = true;
		}
	}
  if(state != '1' && x){
    state = 'X';
  }
  if(state != m_current_state)
	{
    m_current_state = state;
		uint64_t next = current_time + m_delay;
		e = new Event {next,m_output,state};
         
	}
  return e;
}

Xor2Gate::Xor2Gate(Wire* in1, Wire* in2, Wire* out):Gate(2,out){
  wireInput(0, in1);
  wireInput(1, in2);
}

Event* Xor2Gate::update(uint64_t tiempo){
  char in1 = m_inputs[0]->getState();
  char in2 = m_inputs[1]->getState();
  char state;
  if(in1 == 'X' || in2 == 'X'){
    state = 'X';
  }
  else if(in1 != in2){
    state = '1';
  }
  else{
    state = '0';
  }
  Event* e = nullptr;
  if(state != m_current_state){
    m_current_state = state;
    uint64_t next = tiempo + m_delay;
    e = new Event{next, m_output, state};
  }
  return e;
}
