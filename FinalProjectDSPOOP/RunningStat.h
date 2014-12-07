#ifndef RUNNING_STAT_H_
#define RUNNING_STAT_H_
#include "Arduino.h"

class RunningStat
{
    private:
          int m_n;
          double m_oldM, m_newM, m_oldS, m_newS;

    public:
        RunningStat();
        void Clear();
        void Push(double x);
        int NumDataValues() const;
        double Mean() const;
        double Variance() const;
        double StandardDeviation() const;

};

#endif
