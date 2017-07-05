/**
 * Project Elaborato_ING_SW
 * @author Noè Murr, Mirko Morati
 */


#ifndef _PATIENT_H
#define _PATIENT_H

#include <vector>
#include <string>
#include "../Address.hpp"
#include "../time_utilities/Date.hpp"
#include "../interfaces/ISerializable.hpp"
#include "Prescription.hpp"

using namespace std;

namespace mm {
    class Patient : public ISerializable {
    public:

        Patient();

        ~Patient();

        map<string, Serialized> serialize() const override;

        void unserialize(map<string, Serialized> map) override;

        string get_table_name() const override;

        string get_primary_key() const override;

        const string &get_health_code() const;

        const string &get_first_name() const;

        const string &get_last_name() const;

        const string &get_birth_date() const;

        const string &get_birth_place() const;

        const string &get_address() const;

        const string &get_fiscal_code() const;

        string &get_risk_factors();

        vector<Prescription> &get_prescriptions();

    private:
        string health_code;
        string first_name;
        string last_name;
        string fiscal_code;
        string birth_date;
        string birth_place;
        string address;
        vector<string> risk_factors;
        vector<Prescription> prescriptions;

        void get_prescriptions_from_db();
    };
}

#endif //_PATIENT_H