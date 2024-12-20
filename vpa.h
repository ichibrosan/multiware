//
// Created by doug on 12/19/24.
//

#ifndef MULTIWARE_VPA_H
#define MULTIWARE_VPA_H


class vpa {
    int              m_vpa_port;
    struct servent * m_pServent;
public:
    vpa();
    int get_vpa_port();
    ~vpa();
};


#endif //MULTIWARE_VPA_H
