/**
 * Project Elaborato_ING_SW
 * @author Noè Murr, Mirko Morati
 */


#ifndef _DOCTOR_H
#define _DOCTOR_H

#include <string>
#include <vector>

#include "../users/User.hpp"
#include "Prescription.hpp"
#include "Patient.hpp"
#include "Drug.hpp"

using namespace std;
namespace mm {
    class Doctor : public ISerializable {
    private:
        std::string first_name;
        std::string last_name;
        string birth_date;
        string birth_place;
        string fiscal_code;
        int regional_id;
        string specialization;
        vector<Patient> patients;

        void get_patients_from_db();

    public:
        vector<Prescription> get_prescriptions(Patient patient,
                                               Date start, Date end);

        vector<Prescription> get_prescriptions(Drug drug);

        vector<Drug> get_drugs(Date start, Date end);

        vector<Patient, allocator<Patient>> &get_patients();

        vector<Patient> get_patients(Drug drug);

        const string &getFirst_name() const;

        const string &getLast_name() const;

        const string &getBirth_date() const;

        const string &getBirth_place() const;

/*----------------------------------------------------------------------------*/
        map<string, mm::Serialized> serialize() const override;

        void unserialize(map<string, mm::Serialized> map) override;

        string get_table_name() const override;

        string get_primary_key() const override;

        const string &get_fiscal_code() const;

        const int &get_regional_id() const;

        const string &get_specialization() const;
    };
}

#endif //_DOCTOR_H