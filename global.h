//
// Created by doug on 12/11/24.
//

#ifndef MULTIWARE_GLOBAL_H
#define MULTIWARE_GLOBAL_H


class global {
public:
    global();
    ~global();
    html     * pHtml;
    shared   * pShared;
    termbind * pTerm;
};


#endif //MULTIWARE_GLOBAL_H
