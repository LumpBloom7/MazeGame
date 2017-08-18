#include "core.hpp"
#include "player.hpp"

#include <fstream>
#include <sys/stat.h>
#include <algorithm>
#include <chrono>
#include <thread>
#include "cereal/types/vector.hpp"
#include "cereal/types/string.hpp"
#include "cereal/archives/json.hpp"

// Includes platform specific implementations
#if defined( _WIN32 ) || defined( _WIN64 )
#include "winCore.cpp"
#elif defined( __unix__ ) || defined( __unix )
#include "linuxCore.cpp"
#endif

namespace core {
  namespace filesystem {                           // Functions used to read and modify the file system of the user.
    bool fileExists( const std::string &fileName ) // Used to check if a certain file exists with a certain directory
    {
      struct stat buffer;
      return ( stat( fileName.c_str(), &buffer ) == 0 );
    }
  }

  template <typename Iter, typename RandomGenerator> Iter randomSelect( Iter start, Iter end, RandomGenerator &g ) {
    std::uniform_int_distribution<> dis( 0, std::distance( start, end ) - 1 );
    std::advance( start, dis( g ) );
    return start;
  }

  template <typename Iter> Iter randomSelect( Iter start, Iter end ) {
    static std::random_device rd;
    static std::mt19937 gen( rd() );
    return randomSelect( start, end, gen );
  }

  void pause() {
    std::cin.ignore();
    std::cin.ignore();
  }
  void sleep( std::chrono::seconds seconds ) { std::this_thread::sleep_for( seconds ); }
  void sleep( std::chrono::milliseconds milliseconds ) { std::this_thread::sleep_for( milliseconds ); }
  void sadisticInsult() {
    std::vector<std::string> insults{
        "It's that the best you've got? Little bitch!",
        "Well, I knew that you are an idiot, but being unable to use this softare correctly? you just reached a new "
        "level of stupidity!!",
        "Should I make a SUPER EASY BABY mode? Contact me at FUCKYOURSELF@outlook.com.",
        "Sighhhh....",
        "Let's face it, you're not up for it.. Just quit while you're still can!",
        "You want to know why I do not have any sort of metrics system in this? It's because my server hosting plan "
        "can't handle the amount of bullshit you send through!"};
    std::string selection = *randomSelect( insults.begin(), insults.end() );
    std::cout << selection << std::endl;
  }
  void save() // Serialize namespace player, you can change this to another namespace or object
  {
    std::string password;
    std::ofstream os( ( "saveData/" + player::userName + ".json" ) );
    cereal::JSONOutputArchive archive( os );

    archive( CEREAL_NVP( player::userName ), CEREAL_NVP( player::password ),
             CEREAL_NVP( player::experience ) ); // Names the output the same as the variable name
  }
  int load() // Deserialize namespace player, you can change this to another namespace or object
  {
    std::string userName{};
    std::cout << "Please enter your userName: " << std::flush;
    std::cin >> userName;
    if ( core::filesystem::fileExists( "saveData/" + userName + ".json" ) ) {
      std::string password;
      std::ifstream is( "saveData/" + userName + ".json" );
      cereal::JSONInputArchive archive( is );
      archive( player::userName, player::password, player::experience );
      std::cout << player::password << std::endl;
      if ( player::password != "" ) {
        std::string tempPassword = core::console::getPassword( "Please input your password for your save file: " );
        std::cout << tempPassword << std::endl;
        if ( tempPassword != player::password ) {
          std::cout << termcolor::red << "The inputted password seems to be incorrect, please try again."
                    << termcolor::reset << std::endl;
          return -1;
        }
      }
    } else {
      std::cout << termcolor::red << "It seems like there is no save files for that userName.." << termcolor::reset
                << std::endl;
      return -1;
    }
  }
}
