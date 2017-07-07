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

        string &get_risk_factors() const;

        int get_doctor_id() const;

        void set_health_code(const string &health_code);

        void set_first_name(const string &first_name);

        void set_last_name(const string &last_name);

        void set_fiscal_code(const string &fiscal_code);

        void set_birth_date(const string &birth_date);

        void set_birth_place(const string &birth_place);

        void set_address(const string &address);

        void set_doctor_id(int doctor_id);

        vector<Prescription> &get_prescriptions();

    private:
        string health_code;
        string first_name;
        string last_name;
        string fiscal_code;
        string birth_date;
        string birth_place;
        string address;
        int doctor_id;
        vector<string> risk_factors;
        vector<Prescription> prescriptions;

        void get_prescriptions_from_db();
    };
}

#endif //_PATIENT_H