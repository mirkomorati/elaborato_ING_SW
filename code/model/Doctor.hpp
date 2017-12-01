/**
 * Project Elaborato_ING_SW
 * @author Noè Murr, Mirko Morati
 */


#ifndef _DOCTOR_H
#define _DOCTOR_H

#include <string>
#include <vector>

#include "Prescription.hpp"
#include "Patient.hpp"
#include "Drug.hpp"
#include "../utils/Date.hpp"
#include "../utils/Time.hpp"

using namespace std;
namespace mm {
    namespace model {
        class Doctor : public ISerializable {
        private:
            std::string first_name;
            std::string last_name;
            string birth_date;
            string birth_place;
            string fiscal_code;
            int regional_id;
            string specialization;
            vector<model::Patient> patients;

            void get_patients_from_db();

        public:
            vector<model::Prescription> get_prescriptions(Patient patient,
                                                          util::Date start, util::Date end);

            vector<model::Prescription> get_prescriptions(model::Drug drug);

            vector<model::Drug> get_drugs(util::Date start, util::Date end);

            vector<model::Patient> &get_patients();

            vector<model::Patient> get_patients(model::Drug drug);

            model::Patient get_patient_from_fiscal_code(std::string fiscal_code);

            void remove_patient(const Patient &patient);

            const string &get_first_name() const;

            const string &get_last_name() const;

            const string &get_birth_date() const;

            const string &get_birth_place() const;

/*----------------------------------------------------------------------------*/
            map<string, mm::Serialized> serialize() const override;

            void unserialize(map<string, mm::Serialized> map) override;

            string get_table_name() const override;

            vector<string> get_primary_key() const override;

            const string &get_fiscal_code() const;

            const int &get_regional_id() const;

            const string &get_specialization() const;
        };
    }
}

#endif //_DOCTOR_H