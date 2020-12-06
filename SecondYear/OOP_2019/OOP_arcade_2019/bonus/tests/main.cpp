/*
** EPITECH PROJECT, 2020
** main.cpp
** File description:
** unit tests main
*/

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#define ARGV(name) const char * const name []

#include "MainWindow.hpp"

const char * const argv[] = {"../../arcade"};
MainWindow window(1, argv);

bool DLLoaderTest(const std::string & name)
{
    try {
        ArcadeDLLoader<IGameModule> arc(name);
        return true;
    } catch (const std::exception & e) {
        return false;
    }
}

TEST_CASE( "DLLoader Tests" ) {
    REQUIRE( DLLoaderTest("games/lib_arcade_pacman.so"));
    REQUIRE( DLLoaderTest("games/lib_arcade_nibbler.so"));
    REQUIRE( DLLoaderTest("games/lib_arcade_space_invader.so"));
    REQUIRE( DLLoaderTest("games/lib_arcadePrior_mainmenu.so"));
    REQUIRE( DLLoaderTest("games/lib_arcade_qix.so"));
    REQUIRE( !DLLoaderTest("games/lib_arcade_oeuf.so"));
    REQUIRE( !DLLoaderTest("games/lidzqdzqdqzjiso"));
    REQUIRE( !DLLoaderTest("XDDDDDD"));
    REQUIRE( DLLoaderTest("lib/lib_arcade_sfml.so"));
    REQUIRE( DLLoaderTest("lib/lib_arcade_sdl.so"));
}

bool loadGameLibsTest(const std::string & libraryPath)
{
    if (window.changeGameLib("games/" + libraryPath) == EXIT_FAILURE)
        return false;
    return true;
}

TEST_CASE( "Game Libs loading" ) {
    REQUIRE( loadGameLibsTest("lib_arcade_pacman.so"));
    REQUIRE( !loadGameLibsTest("lib_arcade_wtf.so"));
    REQUIRE( !loadGameLibsTest("tu return false"));
    REQUIRE( !loadGameLibsTest(""));
    REQUIRE( loadGameLibsTest("lib_arcade_nibbler.so"));
}

TEST_CASE( "Arcade launching test" ) {
    ARGV(argv1) = {"oui"};
    MainWindow win1(1, argv1);
    REQUIRE( win1.exec(false) == EXIT_FAILURE );

    ARGV(argv2) = {""};
    MainWindow win2(1, argv2);
    REQUIRE( win2.exec(false) == EXIT_FAILURE );
}

TEST_CASE( "Shortkeys test" ) {
    ARGV(argv3) = {"./arcade"};
    MainWindow win3(1, argv3);
    REQUIRE( win3.exec(false) == EXIT_FAILURE );

    ARGV(argv4) = {"./arcade", "caca"};
    MainWindow win4(2, argv4);
    REQUIRE( win4.exec(false) == EXIT_SUCCESS );

    ARGV(argv5) = {"./arcade", "ncurses"};
    MainWindow win5(2, argv5);
    REQUIRE( win5.exec(false) == EXIT_SUCCESS );

    ARGV(argv6) = {"./arcade", "sdl"};
    MainWindow win6(2, argv6);
    REQUIRE( win6.exec(false) == EXIT_SUCCESS );
}

TEST_CASE( "Normal libraries name test" ) {
    ARGV(argv3) = {"./arcade"};
    MainWindow win3(1, argv3);
    REQUIRE( win3.exec(false) == EXIT_FAILURE );

    ARGV(argv4) = {"./arcade", "lib/lib_arcade_caca.so"};
    MainWindow win4(2, argv4);
    REQUIRE( win4.exec(false) == EXIT_SUCCESS );

    ARGV(argv5) = {"./arcade", "lib/lib_arcade_ncurses.so"};
    MainWindow win5(2, argv5);
    REQUIRE( win5.exec(false) == EXIT_SUCCESS );

    ARGV(argv6) = {"./arcade", "lib/lib_arcade_sdl.so"};
    MainWindow win6(2, argv6);
    REQUIRE( win6.exec(false) == EXIT_SUCCESS );
}