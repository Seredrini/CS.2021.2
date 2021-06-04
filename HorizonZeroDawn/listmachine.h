#ifndef LISTMACHINE_H
#define LISTMACHINE_H

#include <vector>
#include <QDebug>
#include <machine.h>

using namespace std;

class machinelist
{
public:
    machinelist();
    machinelist(QVariantMap json_map);
    machinelist(const machinelist &base);

   vector<machine> getList();

private:
   vector<machine> list;
   int page;
};

#endif // LISTMACHINE_H
