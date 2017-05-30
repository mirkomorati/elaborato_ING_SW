/**
 * Project Elaborato_ING_SW
 * @author Noè Murr, Mirko Morati
 */


#ifndef _DATE_H
#define _DATE_H

class Date {
public: 
    
    void get_date();
    
    void set_date();
private: 
    int day;
    int month;
    int year;
};

#endif //_DATE_H