/**
 * Project Elaborato_ING_SW
 * @author Noè Murr, Mirko Morati
 */


#ifndef _PRESCRIPTION_H
#define _PRESCRIPTION_H

#include <vector>
#include <string>
#include <map>
#include <gtkmm/treemodelcolumn.h>
#include "../interfaces/ISerializable.hpp"
#include "Drug.hpp"

using namespace std;

namespace mm {
    namespace model {
        class Prescription : public ISerializable {
        public:
            struct TreeModel : Gtk::TreeModelColumnRecord {
                TreeModel() noexcept;

                Gtk::TreeModelColumn<Glib::ustring> patient_id;
                Gtk::TreeModelColumn<Glib::ustring> issue_date;
                Gtk::TreeModelColumn<Glib::ustring> expire_date;
                Gtk::TreeModelColumn<Glib::ustring> drug_ids;
                Gtk::TreeModelColumn<Glib::ustring> prescription_id;
                Gtk::TreeModelColumn<Glib::ustring> negative_interactions;
                Gtk::TreeModelColumn<Glib::ustring> used;
                Gtk::TreeModelColumn<Glib::ustring> bill_id;

            };

            static TreeModel prescriptionTreeModel;

            static unsigned int generateID();

        public:
            map<string, Serialized> serialize() const override;

            void unserialize(map<string, Serialized> map) override;

            string get_table_name() const override;

            vector<string> get_primary_key() const override;

            string get_patient_id() const;

            int get_prescription_id() const;

            const string &get_issue_date() const;

            const string &get_expire_date() const;

            string get_drug_ids_as_string();

            const vector<Drug> get_drugs() const;

            string get_negative_interactions() const;

            bool is_used() const;

        private:
            string patient_id;
            int prescription_id;
            string issue_date;
            string expire_date;
            vector<pair<string, string>> drug_ids;
            map<string, string> negative_interactions;
            bool used;
        };
    }
}

#endif //_PRESCRIPTION_H