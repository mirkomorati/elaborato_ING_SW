//
// Created by Mirko Morati on 19/09/17.
//

#ifndef ELABORATO_ING_SW_DIALOGFACTORY_HPP
#define ELABORATO_ING_SW_DIALOGFACTORY_HPP

#include <map>
#include "../controller/Dialog.hpp"

namespace mm {
    namespace factory {
        class DialogFactory {
        public:
            typedef controller::Dialog *(*create_dialog_function)(void);

            ~DialogFactory();

            static DialogFactory *get_instance();

            void register_dialog(const std::string &dialog_name, create_dialog_function create);

            controller::Dialog *create_dialog(const std::string &dialog_name);

        private:
            DialogFactory();

            DialogFactory(const DialogFactory &) = delete;

            DialogFactory &operator=(const DialogFactory &) { return *this; }

            std::map factory_map;
        };
    }
}
/*
// Factory for creating instances of IAnimal
class AnimalFactory
{
private:
    AnimalFactory();
    AnimalFactory(const AnimalFactory &) { }
    AnimalFactory &operator=(const AnimalFactory &) { return *this; }

    typedef map FactoryMap;
    FactoryMap m_FactoryMap;
public:
    ~AnimalFactory() { m_FactoryMap.clear(); }

    static AnimalFactory *Get()
    {
        static AnimalFactory instance;
        return &instance;
    }

    void Register(const string &animalName, CreateAnimalFn pfnCreate);
    IAnimal *CreateAnimal(const string &animalName);
};
 */


#endif //ELABORATO_ING_SW_DIALOGFACTORY_HPP
