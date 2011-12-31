#ifndef __INTEGRATOR_MAIN_H__
#define __INTEGRATOR_MAIN_H__

class IntegratorMain {

  public: int main();

  unit Root {
    int main(int);
  };

  parallel unit Peer {
    int main(int,int );
  };
};
#endif
