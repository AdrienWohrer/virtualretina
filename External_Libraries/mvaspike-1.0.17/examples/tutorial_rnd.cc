#include <iostream>
using namespace std;

// the main API header file
#include <mvaspike.h>

int main()
{
  Root root;
  Coupled c;
  Lif n1,n2;
  int id1,id2;
  RNG_GSL_mt rng;
  rng.srand(time(NULL));
  // the neurons have on input port each
  n1.set_nb_inport(1);
  n2.set_nb_inport(1);
  // these port are internally associated with synaptic weights,
  // that we want to specify now :
  n1.set_w(0,rng.rnd(0.2));
  n2.set_w(0,rng.rnd(0.2));
  
  // making the first neuron ready to fire
  n1.set_V(1.0);

  // the network : here, 2 neurons
  id1=c.add_component(n1);
  id2=c.add_component(n2);
  // connecting the output of the 
  // first neuron to the input port of the second neuron
  c.connect(id1,0,id2,0);
  root.set_system(c);

  // validate / initialize everything
  root.init();
  // do a single iteration
  root.iter();
  // we can check the current simulation time now
  // (should be t=0.0)
  cout << "Time ="<< root.get_t() << endl;
  // we now check that the second neuron has received the spike
  // (V2 should be <= 0.2)
  cout << "V2   ="<< n2.get_V() << endl;
  // a second iteration now :
  root.iter();
  // the second neuron will fire earlier that its spontaneous period
  // due to the excitatory contribution at t=0
  // (time should be < 1.0)
  cout << "Time ="<< root.get_t() << endl;
  return 0;
}
