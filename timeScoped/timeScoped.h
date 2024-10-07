
#ifndef __TIME_SCOPED_H__
#define __TIME_SCOPED_H__

#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <sstream>

/**
 * get time consumption of the sampled code snippet
 * ===Example:===
 * timeScoped<50> xxc("data.csv");
 * xxc.start();
 * code snippet;
 * xxc.end();
 * ==============
*/
template<uint32_t numbers>
class timeScoped {
public:
    using clockType = std::chrono::high_resolution_clock;
    static_assert(numbers > 0, "numbers must be greter than zero");
    timeScoped(std::string savePath = "default.csv")
         : mNumber{numbers * 2}, mSavePath{savePath}, mFinished{false} {}
    void start()
    {
        if (mFinished)
            return;
        mSampleData.push_back(clockType::now());
    }
    void end()
    {
        if (mFinished)
            return;
        mSampleData.push_back(clockType::now());

        if (mNumber -= 2, 0 == mNumber) {
            saveData();
            mFinished = true;
        }
    }
private:
    void saveData()
    {
        if (0 != mSampleData.size() % 2) {
            std::cerr << "Error: mSampleData size is not even." << std::endl;
            return;
        }
        for (size_t i = 0; i < mSampleData.size(); i += 2) {
            mElapseTime.push_back(std::chrono::duration_cast<std::chrono::milliseconds>\
                (mSampleData[i + 1] - mSampleData[i]).count());
        }
        std::ofstream csvFile(mSavePath);
        if (!csvFile.is_open()) {
            std::cerr << "failed to open file " << mSavePath << std::endl;
            return;
        }
        csvFile << "elapsedTime(ms)" << std::endl;    
        for (const auto& entry : mElapseTime) {
            csvFile << entry << std::endl;
        }
        size_t size = mElapseTime.size();
        std::sort(mElapseTime.begin(), mElapseTime.end());  
        mMaximum = mElapseTime.back();  
        mMinimum = mElapseTime.front();  
        mAverage = std::accumulate(mElapseTime.begin(), mElapseTime.end(), 0.0) / mElapseTime.size();
        if (size % 2 == 0) {
            mMedian = (mElapseTime[size/ 2 - 1] + mElapseTime[size / 2]) / 2.0;
        } else {
            mMedian = mElapseTime[size / 2];
        }
        csvFile << "Max:" << mMaximum << ", Min:" << mMinimum << ", Aver:" << 
            mAverage << ", Medi:" << mMedian << std::endl;
        csvFile.close();
    }
    size_t mNumber{0};
    std::string mSavePath{};
    bool mFinished{true};
    double mAverage{0};
    double mMedian{0};
    double mMaximum{0};
    double mMinimum{0};
    std::vector<std::chrono::high_resolution_clock::time_point> mSampleData;
    std::vector<double> mElapseTime;
};

#endif /* __TIME_SCOPED_H__ */