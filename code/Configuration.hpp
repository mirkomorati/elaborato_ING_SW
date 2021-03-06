//
// Created by Noè Murr on 03/06/2017.
//

#ifndef ELABORATO_ING_SW_CONFIGURATION_HPP
#define ELABORATO_ING_SW_CONFIGURATION_HPP

#include <string>
#include <json.hpp>
#include <fstream>

using json = nlohmann::json;

namespace mm {
    /**
     * @brief Eccezione che indica che non è stata trovata una key nel file json
     */
    class key_not_found_error : std::runtime_error {
    public:
        key_not_found_error(const std::string &what);

        key_not_found_error(const char *what);

    private:
        const char *what() const noexcept override;

    };

    /**
     * @brief Singleton che mantiene le configurazioni dell'intera applicazione
     *
     * I parametri di configurazione dell'applicazione devono essere salvati in un file in formato json.
     * La classe si occupa sia di leggere che di fornire un'interfaccia semplice per ottenere un parametro dal file
     *
     */
    class Configuration {
    private:
        static std::string config_file_name;
        static Configuration *instance;

        json config;

    private:
        Configuration() noexcept(false);

        ~Configuration();

    public:
        // disallow default constructor and assign operator
        Configuration(const Configuration &old) = delete;

        const Configuration &operator=(const Configuration &old) = delete;

        /**
         * @brief Ritorna una reference ad un'istanza di tipo \c Configuration.
         *
         * Questa funzione non deve mai essere chiamata se prima non è stato chiamato (almeno una volta) il metodo
         * Configuration::set_config_file_name().
         *
         * N.B. Essendo il distruttore privato non è possibile cancellare l'oggetto al di fuori di questa classe
         *
         * @return Istanza di Configuration
         */
        static Configuration &get_instance() noexcept(false);

        /**
         * @brief Ritorna una stringa contente il path dove viene cercato cercato il file json
         *
         * @return Il path del file di configurazione
         */
        static const std::string &get_config_file_name();

        /**
         * @brief Serve per impostare il path dove trovare il file di configurazione
         *
         * N.B. Questa funzione __deve__ sempre essere chiamata prima di una qualsiasi chiamata a Configuration::get_instance
         *
         * @param[in] config_file_name Una stringa contenente il path dove trovare il file
         */
        static void set_config_file_name(const std::string &config_file_name);

        /**
         * @brief Cerca nel file json la chiave \c key, se questa non viene trovata lancia l'apposita eccezione
         *        altrimenti ritorna l'oggetto corrispondente a \c key nel file
         *
         * N.B. \c T deve essere corrispondente al tipo di dato nel json, altrimenti sarà lanciata un eccezione.
         *
         * @tparam T Tipo del dato di configurazione
         * @param key Chiave da cercare nel file
         * @return Oggetto di tipo \c T contenente i dati presenti nel file json alla chiave \c key
         */
        template<typename T>
        T get(const std::string &key) const noexcept(false) {
            if (config.find(key) == config.end()) {
                std::stringstream ss;
                ss << "cannot find key: " << key;
                throw key_not_found_error(ss.str());
            }
            return config[key].get<T>();
        }

    };
}


#endif //ELABORATO_ING_SW_CONFIGURATION_HPP
