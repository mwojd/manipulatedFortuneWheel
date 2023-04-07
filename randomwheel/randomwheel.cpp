//made by M.W
/*
  __  __ _ _         __          __   _
 |  \/  (_) |        \ \        / /  (_)
 | \  / |_| | __      \ \  /\  / /__  _
 | |\/| | | |/ /       \ \/  \/ / _ \| |
 | |  | | |   <   _     \  /\  / (_) | |
 |_|  |_|_|_|\_\ (_)     \/  \/ \___/| |
                                    _/ |
                                   |__/
*/
#include "./includes.h"
//gets a random vector index based on probabilities
template<typename T>
int getRandomIndex(const std::vector<T>& vec1, const std::vector<int>& vec2) {
    int totalWeight = 0;
    for (int weight : vec2) {
        totalWeight += weight;
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, totalWeight - 1);
    int randomNumber = dis(gen);
    int sum = 0;
    for (int i = 0; i < vec2.size(); i++) {
        sum += vec2[i];
        if (randomNumber < sum) {
            return i;
        }
    }
    return -1;
}
template<typename T>
void lotteryAnim(const std::vector<T>& vec1, const std::vector<int>& vec2,int result) {
    std::string top{vec1[getRandomIndex(vec1,vec2)]};
    std::string middle{vec1[getRandomIndex(vec1,vec2)]};
    std::string bottom{vec1[getRandomIndex(vec1,vec2)]};
    for (int i = 0; i < 4; i++) {
        std::cout << "    |" << top << "|" << std::endl;
        mySleep(200);
        std::cout << "  > |" << middle << "|" << std::endl;
        mySleep(200);
        std::cout << "    |" << bottom << "|" << std::endl;
        mySleep(600);
        if(i < 3)
            clear_scr();
        if (i <3)
            top = vec1[result];
        bottom = middle;
        middle = top;
        top = vec1[getRandomIndex(vec1, vec2)];
    }
}
int main() {
    int tmpInt{ 0 };
    int result{ 0 };
    std::string tmpStr{ ' ' };
    for (; ;) {
        loadWheels();
        std::cout << "[1]spin\n";
        std::cout << "[2]create\n";
        std::cout << "[3]remove\n";
        std::cout << "\n\n{0}exit" << std::endl;
        std::cin >> tmpInt;
        switch (tmpInt)
        {
        case 1:
            displayWheels();
            std::cout << "input the wheel you want to spin" << std::endl;
            std::cin >> tmpStr;
            for (const auto& wheel : wheels) {
                if (wheel.name == tmpStr) {
                    result = getRandomIndex(wheel.values, wheel.probabilities);
                    lotteryAnim(wheel.values, wheel.probabilities, result);
                    std::cout << "your result is:   |" << wheel.values[result] << "|" << std::endl;
                    break;
                }
            }
            break;
        case 2:
            createWheel();
            break;
        case 3:
            std::cout << "enter the name of the wheel you want to remove:   ";
            std::cin >> tmpStr;
            std::cout << std::endl;
            removeWheel(tmpStr);
            break;
        case 0:
            return 0;
            break;
        default:
            std::cout << "an error ocured" << std::endl;
            break;
        }
    }
}