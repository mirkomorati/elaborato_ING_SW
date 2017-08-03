/**
 * Project Elaborato_ING_SW
 * @author Noè Murr, Mirko Morati
 */


#ifndef _ISERIALIZABLE_H
#define _ISERIALIZABLE_H

#include <string>
#include <map>

namespace mm {
    /**
     * @brief Enumerazione dei tipi che utilizati di SQLite3
     *
     * È un enumerazione che contiene i tipi di dato che vengono utilizzati
     * nel database. La mappatura è la seguente:
     *    1. INTEGER --> int;
     *    2. REAL --> double;
     *    3. TEXT --> char * (c string);
     *
     */
    enum StoredTypes {
        INTEGER,  // mapped to an int
        REAL,     // mapped to a double
        TEXT      // mapped to a std::string
    };

    /**
     * @brief Union che permette di stivare i tre diversi tipi di dati della
     *        enum StoredTypes.
     */
    union SerializedUnion {
        char *text;
        int integer;
        double real;
    };

    /**
     * @brief Rappresenta un dato da scrivere o estratto dal database.
     *
     * Questa Classe contiene tutti i metodi e le operazioni necessarie a gestire
     * i dati salvati su database, distingue tra i vari tipi e maschera al
     * programmatore la gestione della memoria relativa alla gestione della union
     * SerializedUnion che contiene.
     */
    struct Serialized {
        friend std::ostream &operator<<(std::ostream &os, const Serialized &data);

    private:
        SerializedUnion data;
        StoredTypes type;
    public:
        StoredTypes getType() const noexcept;

        bool isType(StoredTypes type) const noexcept;

        const std::string get_str() const noexcept(false);

        int get_int() const noexcept(false);

        double get_real() const noexcept(false);

        Serialized(std::string data) noexcept;

        Serialized(const char *c_str) noexcept;

        Serialized(int data) noexcept;

        Serialized(double data) noexcept;

        Serialized(float data) noexcept;

        Serialized(const Serialized &old) noexcept;

        const Serialized &operator=(const Serialized &old);

        operator int() const noexcept(false);

        operator std::string() const noexcept(false);

        operator double() const noexcept(false);

        ~Serialized() noexcept;

        Serialized() noexcept;
    };

    std::ostream &operator<<(std::ostream &os, const Serialized &data);

    /**
     * @brief Funziona come un interfaccia, qualunque classe che erediti da questa
     *        potrà essere letta o scritta nel database dal singleton DBMaster.
     */
    class ISerializable {
    public:
        // return the data ostream the row that should be inserted in database
        virtual std::map<std::string, Serialized>
        serialize() const = 0;

        // build the object from the row ostream the database where the data are stored
        virtual void
        unserialize(std::map<std::string, Serialized>) = 0;

        // return the table name where to save the data ostream the class
        virtual std::string get_table_name() const = 0;

        // return the primary key column name.
        virtual std::string get_primary_key() const = 0;
    };
}
#endif //_ISERIALIZABLE_H