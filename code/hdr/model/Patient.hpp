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

using namespace std;

namespace mm {
    class Patient : ISerializable {
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

        const Date &get_birth_date() const;

        const Address &get_birth_place() const;

        const Address &get_address() const;

        const string &get_fiscal_code() const;

        const vector<string> &get_risk_factors() const;

    private:
        string health_code;
        string first_name;
        string last_name;
        string fiscal_code;
        Date birth_date;
        Address birth_place;
        Address address;
        vector<string> risk_factors;
    };
}

#endif //_PATIENT_H