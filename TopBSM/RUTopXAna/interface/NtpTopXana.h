#ifndef GUARD_NtpRUTopXAna_h
#define GUARD_NtpRUTopXAna_h

#include "TopBSM/RUTopXAna/interface/NtpReader.h"

#include <iostream>

class NtpTopXana : public NtpReader
{
  public:
    NtpTopXana (std::vector<TString>&, bool const);
    ~NtpTopXana ();

    void Loop ();

};


















#endif
