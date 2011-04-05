#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "base64.h"

// step 1. generate test data

template <int N>
char* getRandomString(char (&output)[N], size_t size)
{
    char chars[] = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
    size_t numChars = _countof(chars) - 1;

    for (size_t i = 0; i < size; ++i)
    {
        output[i] = chars[(rand() % numChars)];
    }

    return output;
}

void gen_test_data()
{
    srand((unsigned int)time(NULL));

    for (int i = 1; i <= 32; i++)
    {
        char random_string[32+1] = "";

        printf_s("%s\n", getRandomString(random_string, i));
    }
}

// step 2. get encoded chars using python

/** ---------------------------------------------------------------------------
 *  #!/usr/bin/python
 *  
 *  s="""
 *  <put your data in here!>
 *  """
 *  for x in s.split('\n'):
 *      print x,' ' * (32-len(x)), len(x), x.encode('base64')
 *  ---------------------------------------------------------------------------
 */

// step 3. verify data

char* decoded[] = {

      "O"
    , "Tk"
    , "eF("
    , "c[.5"
    , "Moz2-"
    , "Er:'\"w"
    , ":cbe'-i"
    , "]5 \\$fC0"
    , "&_tc\"%*|"
    , "w%+]l`,=)"
    , "kUY7/^}-?U!"
    , "?r$}R&?B#uM-"
    , "+%({!%@#7Rj"
    , "91*.k,.fQ(ID-6"
    , "^Nyu[g}{ppEwaoR"
    , "uZ/pa#h(OU W:,2_"
    , "l]O\\~)bY`37${.?`u"
    , "ZM:5Qe^G}VJ\"MecHhL"
    , "G.!#c^K~&9N65@zm@4\\"
    , "Lu<o/TH5dCTF/#oHr\"|`"
    , "+r8h>y]A5kgke6vSS<s+w"
    , "&V@@6giW>C;hoA%?5VX/!v"
    , "fY'\\0K*,X'tW~ej?i[>[D|G"
    , "\\,/Q'ClIWo18.~e[dZT?'He"
    , ">s&,lbP!QfhQ8Uw3(c/=PVt7h"
    , "V;PUdPqnm>/}^ke(:BA1JU}zU\""
    , "qmp5g;7//c<FUUm/w U{)qSIdO"
    , "d4HR/7VcJ}[n`Z/xqX|S:5Co6+;3"
    , "E/;,-Z%>5UxZaqDUwB@Y$knm'GSw"
    , "}gG`]|(wFX4X5p6N[E`vOD{g@j:onk"
    , "V95U*zqlj1jgd~Q&M4_KL*|Qbt _'r"
    , "9}W(MG-N _NHWGjX>P_rgm^Qt+rhWE>|"
};

char* encoded[] = {

    "Tw=="
    , "VGs="
    , "ZUYo"
    , "Y1suNQ=="
    , "TW96Mi0="
    , "RXI6JyJ3"
    , "OmNiZSctaQ=="
    , "XTUgXCRmQzA="
    , "Jl90Y38iJSp8"
    , "dyUrXWxgLD1/KQ=="
    , "a1VZNy9efS0/VSE="
    , "P3IkfVImP0IjdU0t"
    , "KyUoeyF/JX9AIzdSag=="
    , "OTEqLmssLmZRKElELTY="
    , "Xk55dVtnfXtwcEV3YW9S"
    , "dVovcGEjaChPVSBXOiwyXw=="
    , "bF1PXH4pYllgMzckey4/YHU="
    , "Wk06NVFlXkd9VkoiTWVjSGhM"
    , "Ry4hI2NeS34mOU42NUB6bUA0XA=="
    , "THU8by9USDVkQ1RGLyNvSHIifGA="
    , "K3I4aD55XUE1a2drZTZ2U1M8cyt3"
    , "JlZAQDZnaVc+Qztob0ElPzVWWC8hdg=="
    , "ZlknXDBLKixYJ3RXfmVqP2lbPltEfEc="
    , "XCx/L1EnQ2xJV28xOC5+ZVtkWlQ/J0hl"
    , "PnMmLGxiUCFRZmhROFV3MyhjLz1QVnQ3aA=="
    , "VjtQVWRQcW5tPi99XmtlKDpCQTFKVX16VSI="
    , "cW1wNWc7Ny8vYzxGVVV/bS93IFV7KXFTSWRP"
    , "ZDRIUi83VmNKfVtuYFoveHFYfFM6NUNvNis7Mw=="
    , "RS87LC1/WiU+NVV4WmFxRFV3QkBZJGtubSdHU3c="
    , "fWdHYF18KHdGWDRYNXA2TltFYHZPRHtnQGo6b25r"
    , "Vn85NVUqenFsajFqZ2R+USZNNF9LTCp8UWJ0IF8ncg=="
    , "OX1XKE1HLU4gX05IV0dqWD5QX3JnbV5RdCtyaFdFPnw="
};

int verify_encode_decode()
{
    for (int i = 0; i < _countof(decoded); ++i)
    {
        char result[64];
        if (base64::encode(decoded[i], strlen(decoded[i]), result, _countof(result)) == 0)
        {
            printf_s("base64::encode error!\n");
            return -1;
        }

        if (strcmp(result, encoded[i]) != 0)
        {
            printf_s("%02d|%-34s|%d|%s\n", strlen(decoded[i]), decoded[i], strcmp(result, encoded[i]), result);
        }
    }

    for (int i = 0; i < _countof(encoded); ++i)
    {
        char result[64]="";
        if (base64::decode(encoded[i], strlen(encoded[i]), result, _countof(result)) == 0)
        {
            printf_s("base64::decode error!\n");
            return -1;
        }

        if (strcmp(result, decoded[i]) != 0)
        {
            printf_s("%02d|%-50s|%d|%s\n", strlen(encoded[i]), encoded[i], strcmp(result, decoded[i]), result);
        }
    }

    return 0;
}

//////////////////////////////////////////////////////////////////////////

int _tmain(int argc, _TCHAR* argv[])
{
    verify_encode_decode();

    return 0;
}
