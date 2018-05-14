//
// Created by Noè Murr on 20/02/2018.
//
#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include "../code/model/Authentication.hpp"
#include "../code/model/Patient.hpp"

TEST_CASE("mm::DBMaster", "[doctor]") {
    mm::DBMaster::set_db_file_name("../database/db.sqlite3");
    using namespace mm::model;
    Patient testPatient;

    REQUIRE(not testPatient.is_valid());

    testPatient.set_first_name("Marco");
    testPatient.set_last_name("Rossi");
    testPatient.set_address("Via via 12, 37100, VR");
    testPatient.set_fiscal_code("RSSMRC80A01L781M");
    testPatient.set_birth_date("01/01/1980");
    testPatient.set_birth_place("Via via 12, 37100, VR");
    testPatient.set_doctor_id(111);

    REQUIRE(testPatient.is_valid());

    mm::DBMaster::get_instance().add_to_db(testPatient);

    REQUIRE(mm::DBMaster::get_instance().exists(
            testPatient.get_table_name(), testPatient.get_primary_key()[0], testPatient.get_fiscal_code()));

    mm::DBMaster::get_instance().remove_from_db(testPatient);

    REQUIRE(not mm::DBMaster::get_instance().exists(
            testPatient.get_table_name(), testPatient.get_primary_key()[0], testPatient.get_fiscal_code()));
}

TEST_CASE("model::Authentication", "[authentication]") {
    using namespace mm::model::authentication;
    REQUIRE(not check_login("mario", "rossi"));
    REQUIRE(not Login::get_instance().isLog());

    REQUIRE(check_login("Noe", "0000"));
    REQUIRE(Login::get_instance().isLog());
    REQUIRE(Login::get_instance().regional_id == 111);
    REQUIRE(Login::get_instance().user_name == "Noe");
    REQUIRE(Login::get_instance().password == "0000");

    REQUIRE(check_login("Mirko", "0000"));
    REQUIRE(Login::get_instance().isLog());
    REQUIRE(Login::get_instance().regional_id == 222);
    REQUIRE(Login::get_instance().user_name == "Mirko");
    REQUIRE(Login::get_instance().password == "0000");

    Login::get_instance().logout();
    REQUIRE(not Login::get_instance().isLog());
}