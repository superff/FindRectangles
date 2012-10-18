//
//  main.cpp
//  ProjectC
//
//  Created by Fei Feng on 12-9-28.
//  Copyright (c) 2012年 Fei Feng. All rights reserved.
//

#include <iostream>
#include "RecBox.h"
#include <errno.h>

using namespace std;

int main(int argc, const char * argv[])
{
    
    // insert code here...
    RecBox *r = new RecBox();
    vector<int>  v =  r->find(-1, -2);
    for (vector<int>::iterator it= v.begin(); it< v.end(); it++)
        cout << " " << *it;
    cout << endl;
    
    r -> add(0, 2, 3, 4); //1
    r -> add(-3, -4, 4, 8);//2
    
    
    r -> add(-2, -2, 4, 1);//3
    r -> add(-2, -2, 1, 1);//4
    
    v =  r->find(-1, -2);
    
    for (vector<int>::iterator it= v.begin(); it< v.end(); it++)
        cout << " " << *it;
    cout << endl;
    
    r -> add(-1, -2, 4, 7);//5
    r -> add(-2, -3, 1, 1);//6
    r -> add(-2, -2, 4, 7);//7
    r -> add(-2, -2, 4, 7);//8
    r -> add(-1, -2, 4, 7);//9
    
    v =  r->find(-1, -2);
    
    for (vector<int>::iterator it= v.begin(); it< v.end(); it++)
        cout << " " << *it;
    cout << endl;
    
    r -> add(-2, -3, 4, 7);
    r -> add(1,0,5,7);
    r -> add(8, -2, 4, 7);
    r -> add(8, -2, 4, 7);
    r -> add(8, -2, 4, 7);
    r -> add(8, -2, 4, 7);
    r -> add(8, -2, 4, 7);
    r -> add(8, -2, 4, 7);
    r -> add(8, -2, 4, 7);
    r -> add(8, -2, 4, 7);
    r -> add(-5, -2, 4, 7);
    r -> remove(2);
    r -> remove(9);
    
    
    v =  r->find(-1, -2);
    
    for (vector<int>::iterator it= v.begin(); it< v.end(); it++)
        cout << " " << *it;
    cout << endl;
    
    delete(r);
    
    return 0;
}

