#include <nlohmann/json.hpp>

using namespace nlohmann;
#include <iostream>
#include <map>
#include <vector>
std::string func1()
{
    json js;
    js["msg_type"] = 2;
    js["from"] = "zhang san";
    js["to"] = "li si";
    js["msg"] = "hello";
    std::cout << js << std::endl;
    return js.dump();
    // std::cout << js.dump() << std::endl;
}
std::string func2()
{
    json js;
    js["id"] = {1, 2, 3, 4, 5};
    js["name"] = "zhang san";
    js["msg"]["zhang san"] = "hello";
    js["msg"]["li si"] = "hello";
    // js["msg"]={{"zhang san","hello"},{"li si","hello"}};
    std::cout << js << std::endl;
    return js.dump();
}
std::string func3()
{
    json js;
    std::vector<int> vec{1, 2, 5};
    js["list"] = vec;
    std::map<int, std::string> m;
    m[1] = "一";
    m[2] = "二";
    m[3] = "三";
    js["nums"] = m;
    std::cout << js << std::endl;
    return js.dump();
}
int main()
{

    auto buf1 = func1();
    auto jsbuf1 = json::parse(buf1);
    std::cout << jsbuf1["msg_type"] << std::endl;
    auto buf2 = func2();
    auto jsbuf2 = json::parse(buf2);
    std::cout << jsbuf2["msg"]["zhang san"] << std::endl;
    auto buf3 = func3();
    auto jsbuf3 = json::parse(buf3);
    auto m = jsbuf3["nums"].get<std::map<int,std::string>>();
        // auto m = jsbuf3["nums"].template get<std::map<int,std::string>>();//c++11

    for (auto &[key, value] : m)
    {
        std::cout << key << ":" << value << std::endl;
    }
}
