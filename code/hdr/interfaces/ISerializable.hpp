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
  };

  class ISerializable {
  public:

    virtual std::map<std::string, Serialized>
    serialize() = 0;

    virtual void
    unserialize(std::map<std::string, Serialized>) = 0;

  };
}
#endif //_ISERIALIZABLE_H