/**
 * Project Elaborato_ING_SW
 * @author Noè Murr, Mirko Morati
 */


#ifndef _PRESCRIPTION_H
#define _PRESCRIPTION_H

#include <vector>
#include <string>
#include <map>
#include "../time_utilities/Date.hpp"
#include "../interfaces/ISerializable.hpp"

using namespace std;

namespace mm {
    class Prescription : public ISerializable {
    public:
        map<string, Serialized> serialize() const override;

        void unserialize(map<string, Serialized> map) override;

        string get_table_name() const override;

        string get_primary_key() const override;

        int get_patient_id() const;

        int get_prescription_id() const;

        const string &get_issue_date() const;

        const string &get_expire_date() const;

        string &get_drug_ids();

        string &get_negative_interactions();

        bool is_used() const;

        int get_bill_id() const;

    private:
        int patient_id;
        int prescription_id;
        string issue_date;
        string expire_date;
        vector<string> drug_ids;
        map<string, string> negative_interactions;
        bool used;
        int bill_id; // ?
    };
}

#endif //_PRESCRIPTION_H