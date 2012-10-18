//
//  Point.h
//  ProjectC
//
//  Created by Fei Feng on 12-9-28.
//  Copyright (c) 2012年 Fei Feng. All rights reserved.
//

#ifndef ProjectC_Point_h
#define ProjectC_Point_h

class Point
{
private:
    //the postions of point
    int x, y;
public:
    Point(){}
    Point(int x_, int y_): x(x_), y(y_) {};
    int getX();
    int getY();
};

#endif
