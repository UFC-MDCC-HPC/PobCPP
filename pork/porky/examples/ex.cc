struct PRLock { int taken; };
PRLock* PR_NewLock() { return 0; }
void PR_DestroyLock(PRLock* lock) { }
void PR_Lock(PRLock* lock) { }
void PR_Unlock(PRLock* lock) { }

struct PRMonitor { int taken; };
PRMonitor* PR_NewMonitor() { return 0; }
void PR_DestroyMonitor(PRMonitor* lock) { }
void PR_EnterMonitor(PRMonitor* lock) { }
void PR_ExitMonitor(PRMonitor* lock) { }
void PR_Wait(PRMonitor* lock, int time) { }
void PR_Notify(PRMonitor* lock) { }
void PR_NotifyAll(PRMonitor* lock) { }

struct PRCondVar { int taken; };
PRCondVar* PR_NewCondVar(PRLock* lock) { return 0; }
void PR_DestroyCondVar(PRCondVar* lock) { }
void PR_WaitCondVar(PRCondVar* lock, int time) { }
void PR_NotifyCondVar(PRCondVar* lock) { }
void PR_NotifyAllCondVar(PRCondVar* lock) { }

namespace mozilla {
class Mutex {
public:
    void Lock() { }
    void Unlock() { }
    PRLock* lock;
};
class Monitor {
public:
    void Enter() { }
    void Exit() { }
    void Wait(int time) { }
    void Notify() { }
    void NotifyAll() { }
    PRLock* lock;
    PRCondVar* cv;
};
class CondVar {
public:
    void Wait(int time) { }
    void Notify() { }
    void NotifyAll() { }
    PRLock* lock;
    PRCondVar* cv;
};
}

void foo(PRLock* lock) {
    return;
}

int main(int argc, char** argv) {
    PRLock* lock = PR_NewLock();
    PR_Lock(lock);
    PR_Unlock(lock);
    PR_DestroyLock(lock);

    PRMonitor* mon = PR_NewMonitor();
    PR_EnterMonitor(mon);
    PR_ExitMonitor(mon);
    PR_Wait(mon, -1);
    PR_Notify(mon);
    PR_NotifyAll(mon);
    PR_DestroyMonitor(mon);

    PRCondVar* cv = PR_NewCondVar(lock);
    PR_WaitCondVar(cv, -1);
    PR_NotifyCondVar(cv);
    PR_NotifyAllCondVar(cv);
    PR_DestroyCondVar(cv);

    PRLock** plock = &lock;

    return 0;
}
