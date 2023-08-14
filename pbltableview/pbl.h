#ifndef PBL_H
#define PBL_H

class pbl
{
public:

    enum SOME_FIELDS_VAL
    {
        UNDEFINED = -1 ,
        COL_UNDEFINED = UNDEFINED,
        ROW_UNDEFINED = UNDEFINED,
        INT_UNDEFINED = UNDEFINED,
        REL_UNDEFINED = 0,
        REL_EMPTY_ID  = REL_UNDEFINED,
        EMPTY_ID      = REL_UNDEFINED,
    };

    pbl();
};

#endif // PBL_H
