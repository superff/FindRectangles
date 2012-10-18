//
//  RecBox.h
//  ProjectC
//
//  Created by Fei Feng on 12-9-28.
//  Copyright (c) 2012年 Fei Feng. All rights reserved.
//

#ifndef ProjectC_RecBox_h
#define ProjectC_RecBox_h

#include "Point.h"
#include "Rectangle.h"
#include <unordered_map>
#include <vector>
#include <pthread.h>
#include <assert.h>
#include <map>
#include <set>
#include <iostream>

using namespace std;


class RecBox{
private:
    /*
     stroe the the rectangle by their borders. 4 tree map  ordered by left , down, right, up borders
     */
    map<int,map<int,map<int,map<int,set<int>>>>> quadTree;
    
    //the hashmap to store the info of the rectangle
    unordered_map<int,Rectangle > Recs;
    
    //the mutext lock for rc
    pthread_mutex_t m_mutex;
    
    //the mutect lock to change the recs map and quadTree
    pthread_mutex_t re_mutex;
    
    //the numbers of thread reading at the same time
    int rc;

public:
    RecBox():rc(0)
    {
        pthread_mutex_init(&m_mutex, NULL);
        pthread_mutex_init(&re_mutex, NULL);
    }
    ~RecBox()
    {
        pthread_mutex_destroy(&m_mutex);
        pthread_mutex_destroy(&re_mutex);
    }
    
    // the inputs are any point 's position: x, y and two vectors connecting to it
    // ho, ve need to greater and equal to 0;
    void add(int x,int y, int ho, int ve);
    
    // input is the id of rectange
    void remove(int rid);
    
    // inputs are positon of a point
    vector<int> find(int x, int y);
};

#endif
