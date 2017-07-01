/**
 * Project Elaborato_ING_SW
 * @author Noè Murr, Mirko Morati
 */


#ifndef _DOCTOR_H
#define _DOCTOR_H

#include <string>
#include <vector>

#include "User.hpp"
#include "../Prescription.hpp"
#include "../Patient.hpp"
#include "../Drug.hpp"

using namespace std;
namespace mm {
    class Doctor : public User {
    private:
        string fiscal_code;
        string regional_id;
        string specialization;
        vector<int> prescriptions_id;

    public:
        vector<Prescription> get_prescriptions(Patient patient,
                                               Date start, Date end);

        vector<Prescription> get_prescriptions(Drug drug);

        vector<Drug> get_drugs(Date start, Date end);

        vector<Patient> get_patients();

        vector<Patient> get_patients(Drug drug);

/*----------------------------------------------------------------------------*/
        map<string, mm::Serialized> serialize() const override;

        void unserialize(map<string, mm::Serialized> map1) override;

        string get_table_name() const override;

        string get_primary_key() const override;
    };
}

#endif //_DOCTOR_H