//
// Created by doug on 12/19/24.
//
#include <netdb.h>
#include <iostream>
#include "vpa.h"

#define DEBUG_VPA

vpa::vpa()
{
        struct servent * pServent = getservbyname("vpa","tcp");
        m_vpa_port = htons(pServent->s_port);
#ifdef DEBUG_VPA
        std::cout << "vpa port is " << m_vpa_port << std::endl;
#endif // DEBUG_VPA
}

int vpa::get_vpa_port()
{
    return m_vpa_port;
}

vpa::~vpa()
{

}