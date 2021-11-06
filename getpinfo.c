#include "types.h"
#include "stat.h"
#include "user.h"
#include "pstat.h"
#include <stddef.h>
#define check(exp, msg) if(exp) {} else {\
   printf(1, "%s:%d check (" #exp ") failed: %s\n", __FILE__, __LINE__, msg);\
   exit();}

int
main(int argc, char *argv[])
{
   struct pstat st;

   check(getpinfo(&st) == 0, "getpinfo");
   check(getpinfo(0) == -1, "getpinfo with bad pointer");
   check(getpinfo((struct pstat *)1000000) == -1, "getpinfo with bad pointer"); 
   printf(1, "Should print 1 then 2. pid: %d, tickets: %d, ticks:%d ",st.pid[0], st.tickets[0],st.ticks[0]);
   exit();
}
