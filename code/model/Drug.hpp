/**
 * Project Elaborato_ING_SW
 * @author Noè Murr, Mirko Morati
 */


#ifndef _MEDICINE_H
#define _MEDICINE_H

#include <string>
#include <vector>
#include <map>
#include <gtkmm/treemodelcolumn.h>
#include "../interfaces/ISerializable.hpp"

using namespace std;
namespace mm {
    namespace model {
        class Drug : public ISerializable {
        public:
            struct TreeModel : Gtk::TreeModelColumnRecord {
                TreeModel() noexcept;

                Gtk::TreeModelColumn<Glib::ustring> name;
                Gtk::TreeModelColumn<Glib::ustring> pharmaceutical_form;
                Gtk::TreeModelColumn<Glib::ustring> ATC_classification;
                Gtk::TreeModelColumn<Glib::ustring> contraindications;
                Gtk::TreeModelColumn<Glib::ustring> active_principles;
                Gtk::TreeModelColumn<Glib::ustring> price;

            };

            static TreeModel drugTreeModel;

        public:
            Drug(const string &name, float price);

            Drug() = default;

            map<string, Serialized> serialize() const override;

            void unserialize(map<string, Serialized> map) override;

            string get_table_name() const override;

            vector<string> get_primary_key() const override;

            const string &get_name() const;

            float get_price() const;

            const string &get_pharmaceutical_form() const;

            const vector<string> &get_contraindications() const;

            const string get_contraindications_as_string() const;

            const string get_ATC_classification() const;

            const vector<pair<string, string>> &get_active_principles() const;

            const string get_active_principles_as_string() const;

            const string get_price_as_string() const;

            bool operator==(const Drug &rhs) const;

            bool operator!=(const Drug &rhs) const;

        private:
            string name;
            float price;
            string pharmaceutical_form;
            vector<string> contraindications;
            string ATC_classification;
            vector<pair<string, string>> active_principles;
        };
    }
}

#endif //_MEDICINE_H