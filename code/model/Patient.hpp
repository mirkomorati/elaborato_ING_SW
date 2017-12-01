/**
 * Project Elaborato_ING_SW
 * @author Noè Murr, Mirko Morati
 */

#ifndef _PATIENT_H
#define _PATIENT_H

#include <vector>
#include <string>
#include <gtkmm/treemodelcolumn.h>
#include "../interfaces/ISerializable.hpp"
#include "Prescription.hpp"

using namespace std;

namespace mm {
    namespace model {
        class Patient : public ISerializable {
        public:
            struct TreeModel : public Gtk::TreeModelColumnRecord {
                TreeModel();

                Gtk::TreeModelColumn<Glib::ustring> first_name;
                Gtk::TreeModelColumn<Glib::ustring> last_name;
                Gtk::TreeModelColumn<Glib::ustring> fiscal_code;
                Gtk::TreeModelColumn<Glib::ustring> health_code;
                Gtk::TreeModelColumn<Glib::ustring> birth_date;
                Gtk::TreeModelColumn<Glib::ustring> birth_place;
                Gtk::TreeModelColumn<Glib::ustring> address;
                Gtk::TreeModelColumn<Glib::ustring> risk_factors;
            };

            static TreeModel patientTreeModel;

        public:
            Patient();

            ~Patient();

            map<string, Serialized> serialize() const override;

            void unserialize(map<string, Serialized> map) override;

            string get_table_name() const override;

            vector<string> get_primary_key() const override;

            const string &get_health_code() const;

            const string &get_first_name() const;

            const string &get_last_name() const;

            const string &get_birth_date() const;

            const string &get_birth_place() const;

            const string &get_address() const;

            const string &get_fiscal_code() const;

            string get_risk_factors() const;

            int get_doctor_id() const;

            vector<Prescription> get_prescriptions();

            void set_health_code(const string &health_code);

            void set_first_name(const string &first_name);

            void set_last_name(const string &last_name);

            void set_fiscal_code(const string &fiscal_code);

            void set_birth_date(const string &birth_date);

            void set_birth_place(const string &birth_place);

            void set_address(const string &address);

            void set_doctor_id(int doctor_id);

            bool is_valid();

            bool operator==(const Patient &rhs) const;

            bool operator!=(const Patient &rhs) const;

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
        };
    }
}

#endif //_PATIENT_H