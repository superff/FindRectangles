//
//  Rectangle.h
//  ProjectC
//
//  Created by Fei Feng on 12-9-28.
//  Copyright (c) 2012年 Fei Feng. All rights reserved.
//

#ifndef ProjectC_Rectangle_h
#define ProjectC_Rectangle_h
#include "Point.h"

class Rectangle
{
private:
    // left down node of the rectangle
	Point ldnode;
    
    //vertical vector connecting to the node
    //horizontal vector connecting to the node
	unsigned int vertical,horizontal;// both must be positive
    
    //id of the rectangle
    int id;
    
    //tht border of the rectangle
    int up,down,left,right;
public:
    Rectangle(){};
	Rectangle(Point const& ldnode_,unsigned int vertical_,unsigned int horizontal_,int id_): ldnode(ldnode_),vertical(vertical_),horizontal(horizontal_),id(id_){
        up = ldnode.getY() + vertical;
        down = ldnode.getY();
        left = ldnode.getX();
        right = ldnode.getX() + horizontal;
    };
    
    int getId();
    // the up border of rec
    int getUp();
    // the low border of rec
    int getDown();
    
    // the left border
    int getleft();
    
    // the right border
    int getright();
};

#endif
