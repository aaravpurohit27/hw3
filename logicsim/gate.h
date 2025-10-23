#ifndef GATE_H
#define GATE_H
#include <vector>
#include <queue>
#include <tuple>
#include "event.h"
#include "wire.h"

class Gate 
{
    public:
        Gate(int, Wire*);
        virtual ~Gate();
        virtual Event* update(uint64_t) =0;
        void wireInput(unsigned int,Wire*);
        
    protected:
      Wire* m_output;
      std::vector<Wire*> m_inputs;
			uint32_t m_delay;
			char m_current_state;
};

class NotGate : public Gate{
public:
  NotGate(Wire* in, Wire* out);
  Event* update(uint64_t tiempo);
};
class And2Gate : public Gate
{
  public:
      And2Gate(Wire* in1, Wire* in2, Wire* out);
      Event* update(uint64_t);  
};

class Or2Gate : public Gate
{
  public:
      Or2Gate(Wire* in1, Wire* in2, Wire* out);
      Event* update(uint64_t);
};

class Xor2Gate : public Gate{
public:
  Xor2Gate(Wire* in1, Wire* in2, Wire* out);
  Event* update(uint64_t tiempo);
};

#endif