
#include "MasterMind.h"

void MasterMind::setColorCode()
{
    int colorCodeLength = std::end(colorCode) - std::begin(colorCode);

    for (int i = 0; i < colorCodeLength; i++) {
        colorCode[i] = colorList[RandomNumberGenerator::generateRandomNumber(0, 5)];
    }


}
void MasterMind::printColorCode(){
    std::cout << "____________________________________________________" << std::endl;
    std::cout << "set color code: " << std::endl;
    for (auto &color: colorCode) {
        std::cout << "\t" << color;
    }
    std::cout << std::endl;
    std::cout << "____________________________________________________" << std::endl;
}


MasterMind::MasterMind()
{
    this->setColorCode();
    this->printColorCode();
}
