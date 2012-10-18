//
//  RecBox.cpp
//  ProjectC
//
//  Created by Fei Feng on 12-9-28.
//  Copyright (c) 2012年 Fei Feng. All rights reserved.
//

#include "RecBox.h"

static int id = 1;

void RecBox::add(int x,int y, int ho, int ve){
    
    if(ho < 0 || ve < 0)
    {
        std::cout<< " the vectors should be positive"<< std::endl;
        return;
    }
    
    Rectangle rec(Point(x, y),ho,ve,id++);
    
    // lock the mutex
    pthread_mutex_lock(&re_mutex);
    Recs[rec.getId()] = rec;
    //add the rectangle info to the quadtree
    quadTree[rec.getleft()][rec.getDown()][rec.getright()][rec.getUp()].insert(rec.getId());
    //unlock mutex
    pthread_mutex_unlock(&re_mutex);
    
}

void RecBox::remove(int rid)
{
    //lock the mutex
    pthread_mutex_lock(&re_mutex);
    if(Recs.count(rid) != 0)
    {
        //get the rectangle info by its id
        Rectangle r = Recs.find(rid)->second;
        //erase the rectangle id in the map
        quadTree[r.getleft()][r.getDown()][r.getright()][r.getUp()].erase(r.getId());
        //erase 
        Recs.erase(rid);
    }
    //lock the mutex
    pthread_mutex_unlock(&re_mutex);
}

vector<int> RecBox::find(int x, int y)
{
    map<int,map<int,map<int,map<int,set<int>>>>>::iterator itleft,itFirst;
    map<int,map<int,map<int,set<int>>>>::iterator itlow, itSecond;
    map<int,map<int,set<int>>>::iterator itright,itThird;
    map<int,set<int>>::iterator itup,itFourth;
    set<int>::iterator setIt;
    
    vector<int> list;
    
    //mutiple reader allowed
    pthread_mutex_lock(&m_mutex);
    rc += 1;
    //if only on reader, lock the mutex to prevent writing
    if(rc == 1)
        pthread_mutex_lock(&re_mutex);
    pthread_mutex_unlock(&m_mutex);
    
    /*
     compare the input node with the  4 borders of the rectangle
     find the rectangles including the input node by comparing their borders with the x,y of node
     */
    
    //rec short for rectangles
    // L short for left border
    // D short for Down border
    
    //find the all recs' whose L lefter than input x
    itleft = quadTree.upper_bound(x);
    
    //Go throught all the Recs L lefter than x
    for(itFirst= quadTree.begin(); itFirst != itleft; itFirst++)
    {
        //find all the the Recs whose D lower than y
        itlow = quadTree[itFirst->first].upper_bound(y);
        
        //go through all the rectangle  D lower than y
        for(itSecond = quadTree[itFirst->first].begin(); itSecond != itlow ; itSecond ++ )
        {
            //find all the Recs whose R righter and equal to x
            itright = quadTree[itFirst->first][itSecond->first].lower_bound(x);
            
            //go through all the rectangles R righter and equal to x
            for(itThird = itright; itThird != quadTree[itFirst->first][itSecond->first].end(); itThird++)
            {
                //find all the Recs whose U upper and equal to y
                itup = quadTree[itFirst->first][itSecond->first][itThird->first].lower_bound(y);
                
                //go all the rectangles U upper and equal to y
                for(itFourth = itup; itFourth != quadTree[itFirst->first][itSecond->first][itThird->first].end(); itFourth++)
                {
                    // find all the ids in the set and add to the vector
                    for(setIt = quadTree[itFirst->first][itSecond->first][itThird->first][itFourth->first].begin(); setIt != quadTree[itFirst->first][itSecond->first][itThird->first][itFourth->first].end(); setIt++)
                    {
                        list.push_back(*setIt);
                    }
                }
            }
        }
    }
    
    pthread_mutex_lock(&m_mutex);
    rc -= 1;
    if(rc == 0)//no reader, unlock the mutex
        pthread_mutex_unlock(&re_mutex);
    pthread_mutex_unlock(&m_mutex);
    
    return list;
}