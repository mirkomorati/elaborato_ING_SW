//
// Created by Noè Murr on 03/06/2017.
//

#ifndef ELABORATO_ING_SW_DBMASTER_HPP
#define ELABORATO_ING_SW_DBMASTER_HPP

#include <sqlite3.h>
#include <string>
#include <stdexcept>
#include <vector>
#include "interfaces/ISerializable.hpp"

using namespace std;
namespace mm {

    /**
     * @brief Singleton che rappresenta il database, contiene tutte le funzioni
     *        necessarie per scrivere un oggetto di tipo derivato da ISerializable
     *        e per leggerlo. Nasconde le chiamate alle API C di sqlite3
     *
     *  È un singleton di tipo lazy. Prima di chiamare get_instance è sempre necessario
     *  informare la classe del path del database chiamando set_db_name
     */
    class DBMaster {
    private:
        sqlite3 *db;
        static string db_file_name;
        static DBMaster *instance;

    private:
        DBMaster() noexcept(false);

        ~DBMaster();

    public:
        // disallow default constructor and assign operator
        DBMaster(const DBMaster &old) = delete;

        const DBMaster &operator=(const DBMaster &old) = delete;

        static const string &get_db_file_name();

        /**
         * @brief imposta il path nel quale trovare il database
         *
         * Questa funzione deve sempre essere chiamata prima di una qualsiasi chiamata a get_instance
         * @param[in] db_file_name
         */
        static void set_db_file_name(const string &db_file_name);

        /**
         * @brief restituisce una reference (non costante) all'oggetto db
         *
         * Siccome il distruttore è privato non è possibile che quella reference venga distrutta al di fuori della
         * classe
         *
         * @return reference ad un oggetto DBMaster
         */
        static DBMaster &get_instance() noexcept(false);

        /**
         * @brief aggiunge un oggetto serializzabile ad database
         *
         * Questo metodo può eseguire o un UPDATE o un INSERT a seconda che l'oggetto sia già presente o meno nel db.
         * Può lanciare eccezioni del tipo std::runtime error in caso di errore
         *
         * @param[in] obj un oggetto serializzabile (che estende la classe ISerializable)
         */
        void add_to_db(const ISerializable &obj);

        /**
         * @brief rimuove un oggetto serializzabile dal database
         *
         * Può lanciare eccezioni di tipo std::runtime_error in caso di errore di comunicazione col database
         *
         * N.B. sia che l'operazione vada a buon fine o meno l'oggetto non viene modificato
         *
         * @param[in] obj un oggetto serializzabile (che estende la classe ISerializable)
         */
        void remove_from_db(const ISerializable &obj);

        /**
         * @brief estrae un oggetto serializzabile dal database
         *
         * Può lanciare eccezioni di tipo std::runtime_error in caso di errore di comunicazione col database
         * oppure può lanciare eccezioni del tipo record_no_found_error nel caso in cui l'oggetto con gli id
         * specificati non sia presente nel db
         *
         * N.B. l'oggetto passato in obj viene modificato e qualsiasi dato in esso contenuto viene sovrascritto
         *
         * @param[out] obj un oggetto serializzabile (che estende la classe ISerializable) in cui salvare i dati del db
         * @param[in] ids lista di oggetti di tipo Serialized che servono da primary key nel database
         */
        void extract_from_db(ISerializable &obj, initializer_list<Serialized> ids);

        /**
         * @brief shortcut per la versione che accetta un initializer_list per poterla chiamare con un solo id in
         * modo semplice
         */
        void extract_from_db(ISerializable &obj, const Serialized &id);

        /**
         * @brief estrae un insieme di righe da una tabella
         *
         * Se non vengono passati i parametri id_name e id il metodo ritorna tutte le righe della tabella altrimenti
         * ritorna solo le righe che hanno quell'id e quell'id_name
         *
         * @param[in] table_name  Parametro obbligatorio che contiene il nome della tabella dal quale estrarre le righe
         * @param[in] id_name     Parametro opzionale che contiene il nome della colonna presa come id
         * @param[in] id          Parametro opzionale che contiene il valore che deve essere contenuto nella colonna
         *                        id_name
         *
         * @return  Un vettore di mappe di stringe e serialized ogni mappa rappresenta una riga dove una colonna è
         *          identificata dalla stringa ed il contenuto dall'oggetto serialized
         */
        vector<map<string, Serialized>> get_rows(string table_name, string id_name = "", Serialized id = "");

    };

    /**
     * @brief eccezione che indica che un oggetto non è presente nel database
     */
    class record_not_found_error : std::runtime_error {
    public:
        explicit record_not_found_error(const std::string &msg);

        explicit record_not_found_error(const char *msg);

    private:
        const char *what() const noexcept override;

    };
}

#endif //ELABORATO_ING_SW_DBMASTER_HPP
