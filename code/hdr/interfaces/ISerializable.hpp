/**
 * Project Elaborato_ING_SW
 * @author Noè Murr, Mirko Morati
 */


#ifndef _ISERIALIZABLE_H
#define _ISERIALIZABLE_H

#include <string>
#include <map>

namespace mm {
  enum StoredTypes{
    INTEGER,  // mapped to an int
    REAL,     // mapped to a double
    TEXT      // mapped to a std::string
  };

  union SerializedUnion{
    std::string text;
    int integer;
    double real;
  };

  struct Serialized{
  private:
    SerializedUnion data;
    StoredTypes type;
  public:
    StoredTypes getType() const noexcept;
    bool isType(StoredTypes type) const noexcept;
    const SerializedUnion &get() const noexcept;

    Serialized(StoredTypes t, SerializedUnion data) noexcept;
    ~Serialized() noexcept;

    friend std::ostream &operator<<(std::ostream &os, const Serialized &data);
  };

  std::ostream &operator<<(std::ostream &os, const Serialized &data);

  class ISerializable {
  public:
    // return the data of the row that should be inserted in database
    virtual std::map<std::string, Serialized>
    serialize() const = 0;

    // build the object from the row of the database where the data are stored
    virtual void
    unserialize(std::map<std::string, Serialized>) = 0;

    // return the table name where to save the data of the class
    virtual std::string get_table_name() const = 0;

    // return the primary key column name.
    virtual std::string get_primary_key() const = 0;
  };
}
#endif //_ISERIALIZABLE_H