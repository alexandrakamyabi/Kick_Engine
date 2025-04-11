//#include <../Kick_Engine/Inc/Kick_Engine.h>
//
//using namespace Kick_Engine;
//using namespace Kick_Engine::Core;
//
//class Student
//{
//public:
//    Student(const std::string& name)
//        :mName(name)
//        , mGrade(0)
//    {
//
//    }
//
//    void SetGrade(int grade)
//    {
//        mGrade = grade;
//    }
//
//private:
//    std::string mName;
//    int mGrade;
//};
//
//class Leaderboard
//{
//public:
//    Leaderboard(const std::string& name)
//        :mPlayerName(name)
//        , mScore(0)
//    {
//
//    }
//
//    void SetGrade(int score)
//    {
//        mScore = score;
//    }
//
//private:
//    std::string mPlayerName;
//    int mScore;
//};
//
//class Country
//{
//public:
//    Country(const std::string& name)
//        :mCountryName(name)
//        , mCities(10)
//    {
//
//    }
//
//    void SetCity(int cities)
//    {
//        mCities = cities;
//    }
//
//private:
//    std::string mCountryName;
//    int mCities;
//};
//
//
//int WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
//{
//    //TEST 1
//    TypedAllocator studentPool = TypedAllocator<Student>("StudentPool", 200);
//
//    std::vector<Student*> students;
//    for (uint32_t i = 0; i < 100; ++i)
//    {
//        std::string name = "Student" + std::to_string(i);
//        students.push_back(studentPool.New(name));
//    }
//
//    // testing delete
//    for (uint32_t i = 0; i < 20; ++i)
//    {
//        auto student = students.back();
//        students.pop_back();
//        studentPool.Delete(student);
//    }
//
//    // testing reuse
//    for (uint32_t i = 0; i < 50; ++i)
//    {
//        std::string name = "Student_new" + std::to_string(i);
//        students.push_back(studentPool.New(name));
//    }
//
//    // clear all
//    for (auto student : students)
//    {
//        studentPool.Delete(student);
//    }
//    
//    //TEST 2
//    TypedAllocator scorePool = TypedAllocator<Leaderboard>("Game Leaderboard", 200);
//
//    std::vector<Leaderboard*> gamerScore;
//    for (uint32_t i = 0; i < 100; ++i)
//    {
//        std::string name = "Gamer ID: " + std::to_string(i);
//        gamerScore.push_back(scorePool.New(name));
//    }
//
//    // testing delete
//    for (uint32_t i = 0; i < 30; ++i)
//    {
//        auto gamers = gamerScore.back();
//        gamerScore.pop_back();
//        scorePool.Delete(gamers);
//    }
//
//    // testing reuse
//    for (uint32_t i = 0; i < 15; ++i)
//    {
//        std::string name = "New_gamer" + std::to_string(i);
//        gamerScore.push_back(scorePool.New(name));
//    }
//
//    // clear all
//    for (auto gamers : gamerScore)
//    {
//        scorePool.Delete(gamers);
//    }
//
//    //TEST 3
//    TypedAllocator countryPool = TypedAllocator<Country>("Countries", 200);
//
//    std::vector<Country*> country;
//    for (uint32_t i = 0; i < 100; ++i)
//    {
//        std::string name = "Gamer ID: " + std::to_string(i);
//        country.push_back(countryPool.New(name));
//    }
//
//    // testing delete
//    for (uint32_t i = 0; i < 30; ++i)
//    {
//        auto countries = country.back();
//        country.pop_back();
//        countryPool.Delete(countries);
//    }
//
//    // testing reuse
//    for (uint32_t i = 0; i < 15; ++i)
//    {
//        std::string name = "New_country" + std::to_string(i);
//        int score = i + 10;
//        country.push_back(countryPool.New(name));
//    }
//
//    // clear all
//    for (auto countries : country)
//    {
//        countryPool.Delete(countries);
//    }                                                         
//
//    return(0);
//
//}