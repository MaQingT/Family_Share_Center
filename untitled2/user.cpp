#include "user.h"


bool judge(User a,User b){
    if(a.getId()!= b.getId()) return false;
    if(a.getName()!= b.getName()) return false;
    if(a.getPsw()!=b.getPsw()) return false;
    if(a.getSpecial()!=b.getSpecial()) return false;
    if(a.getFamilyId()!=b.getFamilyId())return false;
    return true;
}
