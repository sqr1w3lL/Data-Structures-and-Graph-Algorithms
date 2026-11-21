#pragma once
#include <string>

public value struct ManagedTaxPayer {
    int regNumber;
    System::String^ surname;
    System::String^ name;
    System::String^ fathername;
};

public value struct ManagedStudent {
    int code;
    System::String^ surname;
    System::String^ initials;
    System::String^ group;
    double avgMark;
};
