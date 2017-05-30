/**
 * Project Elaborato_ING_SW
 * @author Noè Murr, Mirko Morati
 */


#ifndef _TIME_H
#define _TIME_H

struct Time {
    void get_time();
    
    void set_time();
private: 
    int seconds;
    int minutes;
    int hours;
};

#endif //_TIME_H