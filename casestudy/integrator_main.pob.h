#ifndef __INTEGRATOR_MAIN_H__
#define __INTEGRATOR_MAIN_H__

#include "unit_type.h"
#include "unit.h"
class IntegratorMain {

  public: int main();

  unit Root {
    int main(int);
  };

  unit Peer [j:n] {
    int main(int,int );
  };
};
#endif
