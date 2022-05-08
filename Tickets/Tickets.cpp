#include <iostream>
#include <fstream>
#include "Date.h"
#include "Hall.h"
#include "Event.h"
#include "TicketCenter.h"

int main()
{
    /*Date date(1,2,2022);
    std::cout << date << std::endl;
    std::cin >> date;
    std::cout << date << std::endl;*/

    /*std::fstream file("halls.txt", std::ios::ate | std::ios::in | std::ios::out);
    file.seekg(0, std::ios::beg);
    file.clear();
    char line[1024];
    file.getline(line, 1023);
    std::cout << line;
    Hall h(1, 3, 6);
    file >> h;
    std::cout << h;*/

    TicketCenter t("halls.txt");
    t.newEvent();
    t.reserveTicket();
    t.reserveTicket();
    /*Event event;
    std::cin >> event;
    std::cout << event;*/
}